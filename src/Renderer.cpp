#include <cstdio>
#include <cstring>
#include <cassert>

#include <imgui.h>

#include <Renderer.hpp>
#include <Object.hpp>

Renderer::Renderer(const uint p_width, const uint p_height)
    : fb(p_width, p_height)
    , viewport(0, 0, p_width, p_height)
    , cam(p_width, p_height)
{
    modelMatrix = Mat4::Identity();
    viewMatrix = Mat4::Identity();
    projectionMatrix = Mat4::Identity();
}

void Renderer::DrawTriangles(rdrVertex* p_vertices, const int p_count,  std::vector<Light> &lights, const Vec3& positionCam, const float alpha, Vec3 &RGB)
{
    for (int i = 0; i < p_count; i += 3)
        DrawTriangle(&p_vertices[i], lights, positionCam, alpha, RGB);
}

Vec3 Renderer::ndcToScreenCoords(Vec3& ndc, const Viewport& viewport)
{
    ndc.x = (ndc.x + 1) * viewport.width  / 2;
    ndc.y = (ndc.y + 1) * viewport.height / 2;
    return ndc;
}

bool Renderer::BackFace(Vec3 positionTriangle, Vec3 normalPos[3])
{
    Vec3 normal = (normalPos[0] + normalPos[1] + normalPos[2]) / 3;
    if(normal.DotProduct(positionTriangle - cam.GetPosition()) >= 0.f)
        return false;
    return true;
}

void Renderer::DrawTriangle(rdrVertex* vertices, std::vector<Light> &lights, const Vec3& positionCam, const float alpha, Vec3 &RGB)
{
    // Store triangle vertices positions
    Vec3 localCoords[3] = {
        { vertices[0].x, vertices[0].y, vertices[0].z },
        { vertices[1].x, vertices[1].y, vertices[1].z },
        { vertices[2].x, vertices[2].y, vertices[2].z },
    };

    // Normal Array
    Vec3 localCoordsNormal[3] = {
        { vertices[0].nx, vertices[0].ny, vertices[0].nz },
        { vertices[1].nx, vertices[1].ny, vertices[1].nz },
        { vertices[2].nx, vertices[2].ny, vertices[2].nz },
    };

    // Local space (v3) -> World space (v4)
    Vec4 worldSpace[3];
    // Normal Array
    Vec4 worldSpaceNormal[3];

    for(int i = 0; i < 3; i++)
    { 
        worldSpace[i]       = modelMatrix * Vec4{localCoords[i], 1.f};
        worldSpaceNormal[i] = modelMatrix * Vec4{localCoordsNormal[i], 0.f};
    }

    LightCalc lightCalc = {
        lights,
        {worldSpace[0].toVec3(), worldSpace[1].toVec3(), worldSpace[2].toVec3()},
        {worldSpaceNormal[0].toVec3(), worldSpaceNormal[1].toVec3(), worldSpaceNormal[2].toVec3()},
        positionCam,
        2.f,
    };

    if(!BackFace((Vec3){modelMatrix.mat[0][3], modelMatrix.mat[1][3], modelMatrix.mat[2][3]}, lightCalc.normalWorld))
        return;

    // World space (v4) -> View space (v4)
    Vec4 viewSpace[3];

    for(int i = 0; i < 3; i++)
        viewSpace[i] = viewMatrix * worldSpace[i];
    
    // View space (v4) -> clip space (v4)
    Vec4 clipSpace[3];

    for(int i = 0; i < 3; i++)
    {
        clipSpace[i] = projectionMatrix * viewSpace[i];
        clipSpace[i].Homogenize();
    }

    // Clip space (v4) to NDC (v3)
    Vec3 ndcCoords[3] = {
        { clipSpace[0].x, clipSpace[0].y, clipSpace[0].z },
        { clipSpace[1].x, clipSpace[1].y, clipSpace[1].z },
        { clipSpace[2].x, clipSpace[2].y, clipSpace[2].z },
    };

    // NDC (v3) to screen coords (v2)
    Vec3 screenCoords[3] = {
        { ndcToScreenCoords(ndcCoords[0], viewport) },
        { ndcToScreenCoords(ndcCoords[1], viewport) },
        { ndcToScreenCoords(ndcCoords[2], viewport) },
    };

    if (isWireframe)
    {
        DrawLine(screenCoords[0], screenCoords[1], lineColor);
        DrawLine(screenCoords[1], screenCoords[2], lineColor);
        DrawLine(screenCoords[2], screenCoords[0], lineColor);
    }
    else
        DrawTriangleFilled(vertices, screenCoords, lightCalc, alpha, viewSpace, RGB);
}

float Renderer::EdgeFunction(const Vec2 &a, const Vec2 &b, const Vec2 &c) 
{
    return (a.x - b.x) * (c.y - a.y) - (a.y - b.y) * (c.x - a.x);
}

void Renderer::GetOpacity(Vec4 &color,int width, int x, int y)
{
    if(color.w<1.f)
    {
        Vec4* colorBuffer = reinterpret_cast<Vec4*>(fb.GetColorBuffer());
        Vec4 oldColor = colorBuffer[y*width+x];
        color.x =  (color.x*color.w + oldColor.x *color.w*(1 - color.w))/color.w+oldColor.w*(1-color.w);
        color.y =  (color.y*color.w + oldColor.y *color.w*(1 - color.w))/color.w+oldColor.w*(1-color.w);
        color.z =  (color.z*color.w + oldColor.z *color.w*(1 - color.w))/color.w+oldColor.w*(1-color.w);
        color.w = color.w+oldColor.w*(1-color.w);
    }
}

void Renderer::GetBoundaries(int& xMin, int& xMax, int& yMin, int& yMax, const Vec3& c0, const Vec3& c1, const Vec3& c2, const int width, const int height)
{
    xMin = fminf(c0.x, fminf(c1.x, c2.x)); xMin = xMin < 0 ? 0 : xMin;
    yMin = fminf(c0.y, fminf(c1.y, c2.y)); yMin = yMin < 0 ? 0 : yMin;
    xMax = fmaxf(c0.x, fmaxf(c1.x, c2.x)); xMax = xMax > width ? width : xMax;
    yMax = fmaxf(c0.y, fmaxf(c1.y, c2.y)); yMax = yMax > height ? height : yMax;
}

void Renderer::DrawTriangleFilled(rdrVertex*vertices, Vec3 coords[3], LightCalc& lightCalc, float alpha, Vec4 viewSpaceCoords[3], Vec3 &RGB)
{
    float area = EdgeFunction({coords[0].x, coords[0].y}, {coords[1].x, coords[1].y}, {coords[2].x, coords[2].y});
    int width = fb.GetWidth(), height = fb.GetHeight(), xMin, xMax, yMin, yMax;

    GetBoundaries(xMin, xMax, yMin, yMax, coords[0], coords[1], coords[2], width, height);

    float* depthBuffer = fb.GetDepthBuffer();

    for (int y = yMin; y <= yMax; y++)
    {
        for (int x = xMin; x <= xMax; x++)
        {          
            Vec2 sample = { x + 0.5f, y + 0.5f};

            float w0 = EdgeFunction({coords[1].x, coords[1].y}, {coords[2].x, coords[2].y}, sample) / area; 
            float w1 = EdgeFunction({coords[2].x, coords[2].y}, {coords[0].x, coords[0].y}, sample) / area; 
            float w2 = EdgeFunction({coords[0].x, coords[0].y}, {coords[1].x, coords[1].y}, sample) / area;

            if (w0 < 0 || w1 < 0 || w2 < 0) 
                continue;
            
            //Get color and check opacity
            Vec4 color (RGB.x, RGB.y, RGB.z, alpha );
            GetOpacity(color, width, x, y);

            // If the triangle needs to get a color linear interpolation
            if (RGB.x == 1.f && RGB.y == 1.f && RGB.z == 1.f)
            {
                color.x *= w0;
                color.y *= w1;
                color.z *= w2;
            }

            float z = viewSpaceCoords[0].z * w0 + viewSpaceCoords[1].z * w1 + viewSpaceCoords[2].z * w2;
            
            if(z > depthBuffer[x + y * width] || z > cam.GetFar() || z < cam.GetNear())
                continue;
            
            depthBuffer[x + y * width] = z;

            // Check if texture and draw it
            if(texture)
                color = texture->GetBilinearFilteredPixelColor((Vec2){vertices[0].u * w0 + vertices[1].u * w1 + vertices[2].u * w2 , vertices[0].v * w0 + vertices[1].v * w1 + vertices[2].v * w2});

            // Find the right light intensity
            color *= lightCalc.lights[0].CalcLightIntensity(
                lightCalc.posWorld[0] * w0 + lightCalc.posWorld[1] * w1 + lightCalc.posWorld[2] * w2,
                lightCalc.normalWorld[0] * w0 + lightCalc.normalWorld[1] * w1 + lightCalc.normalWorld[2] * w2,
                cam.GetPosition(), lightCalc.shininess);

            DrawPixel(reinterpret_cast<Vec4*>(fb.GetColorBuffer()), fb.GetWidth(), fb.GetHeight(), x, y, color);
        }
    }
}

void Renderer::DrawLine(const Vec3& p0, const Vec3& p1, const Vec4& pcolor)
{
    int x0 = p0.x, y0 = p0.y, x1 = p1.x, y1 = p1.y;
    int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int err = dx+dy, e2;

    while (!(x0==x1 && y0==y1))
    {
        DrawPixel(reinterpret_cast<Vec4*>(fb.GetColorBuffer()), fb.GetWidth(), fb.GetHeight(), x0, y0, pcolor);

        e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }

        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void Renderer::DrawPixel(Vec4* p_colorBuffer, uint p_width, uint p_height, uint p_x, uint p_y, const Vec4& p_color)
{
    if (p_x >= 0 && p_x < p_width && p_y >= 0 && p_y < p_height)    
        p_colorBuffer[p_x + p_width * p_y] = p_color;
}

void Renderer::ShowImGuiControls()
{
    ImGui::ColorEdit4("lineColor", &lineColor.x);
}