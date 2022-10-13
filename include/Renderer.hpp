#pragma once

#include <Camera.hpp>
#include <Framebuffer.hpp>
#include <myMath.hpp>
#include <Light.hpp>
#include <Texture.hpp>

struct Viewport
{
    Viewport(const int p_x, const int p_y, uint p_width, uint p_height):
    x(p_x),y(p_y),width(p_width),height(p_height){}
    
    const int x;
    const int y;
    uint width; 
    uint height;
};

struct LightCalc
{
    std::vector<Light> lights;
    Vec3 posWorld[3];
    Vec3 normalWorld[3];
    Vec3 posCam;
    float shininess;
};

// Vertex format (only one supported for now)
struct rdrVertex
{
    float x, y, z;    // Pos
    float nx, ny, nz; // Normal
    float r, g, b, a; // Color
    float u, v;       // Texture coordinates
};


class Renderer
{
private:
    Framebuffer fb;
    Viewport viewport;
    Camera cam;
    bool isWireframe = false;

    Mat4 modelMatrix;
    Mat4 viewMatrix;
    Mat4 projectionMatrix;

    Vec4 lineColor = { 1.f, 1.f, 1.f, 1.f };

    Texture* texture;

public:

// Color and depth buffer have to be valid until the shutdown of the renderer
// Color buffer is RGBA, each component is a 32 bits float
// Depth buffer is a buffer of 32bits floats
    Renderer(uint p_width, uint p_height);
    ~Renderer(){};

    void SetProjection(const Mat4& p_projectionMatrix){projectionMatrix = p_projectionMatrix;};
    void SetView(const Mat4& p_viewMatrix){viewMatrix = p_viewMatrix;};
    void SetModel(const Mat4& p_modelMatrix){modelMatrix = p_modelMatrix;};
    
    void DrawTriangles(rdrVertex* p_vertices, const int p_count, std::vector<Light> &lights, const Vec3& positionCam, const float alpha, Vec3 &RGB);
    
    Framebuffer* getFrameBuffer()   {return &fb;};
    Camera* GetCamera()             {return &cam;};
    bool GetWireFrame()             {return isWireframe;};

    void SetTexture(Texture* p_texture)     {texture = p_texture;};
    void SetWireFrame(bool p_isWireframe)   {isWireframe = p_isWireframe;};

private:
    Vec3 ndcToScreenCoords(Vec3& ndc, const Viewport& viewport);
    bool BackFace(Vec3 positionTriangle, Vec3 normalPos[3]);

    void DrawTriangle(rdrVertex* p_vertices, std::vector<Light> &lights, const Vec3& positionCam, const float alpha,Vec3 &RGB);
    
    float EdgeFunction(const Vec2 &a, const Vec2 &b, const Vec2 &c);
    void GetOpacity(Vec4 &color,int width, int x, int y);
    
    void GetBoundaries(int& xMin, int& xMax, int& yMin, int& yMax, const Vec3& c0, const Vec3& c1, const Vec3& c2, const int width, const int height);

    void DrawTriangleFilled(rdrVertex*vertices, Vec3 coords[3], LightCalc& lightCalc, const float alpha, Vec4 viewSpaceCoords[3],Vec3 &RGB);
    void DrawLine(const Vec3& p_0, const Vec3& p_1, const Vec4& p_color);
    void DrawPixel(Vec4* p_colorBuffer, uint p_width, uint p_height, uint p_x, uint p_y, const Vec4& p_color);
    
    void ShowImGuiControls();
};