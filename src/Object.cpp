#include <Object.hpp>

Object::Object()
{
    vertices.clear();
    // indices.clear();
    transformModel = Mat4::Identity();
    texture = nullptr;
    alpha = 1.f;
}

Object::Object(const std::vector<rdrVertex>& vertices, const Mat4& p_transformModel)
    : vertices(vertices)
{
    transformModel = p_transformModel;
}

Object::~Object()
{
}

Object Object::Triangle()
{
    Object triangle;
    triangle.vertices = (std::vector<rdrVertex>){
        (rdrVertex){-0.5f,-0.5f, 0.0f,      -.5f, -.5f, -1.f,      1.0f, 0.0f, 0.0f, 1.f,     0.0f, 0.0f },
        (rdrVertex){ 0.5f,-0.5f, 0.0f,      +.5f, -.5f, -1.f,      0.0f, 1.0f, 0.0f, 1.f,     1.0f, 0.0f },
        (rdrVertex){ 0.0f, 0.5f, 0.0f,       0.f,  0.f, -1.f,      0.0f, 0.0f, 1.0f, 1.f,     0.5f, 1.0f },};

    triangle.transformModel = Mat4::CreateTransformationMatrix({0.f, 0.f, 2.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 180.f});
    return triangle;
}

Object Object::Cube()
{
    Object cube;
    cube.vertices = (std::vector<rdrVertex>){
        // Front   
        (rdrVertex){-0.5f, -0.5f, .5f, -.5f, -.5f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f},
        (rdrVertex){+0.5f, -0.5f, .5f, +.5f, -.5f, 1.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f},
        (rdrVertex){-0.5f, +0.5f, .5f, -.5f, +.5f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f},

        (rdrVertex){-0.5f, +0.5f, .5f, -0.5f, +0.5f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f},
        (rdrVertex){+0.5f, -0.5f, .5f, +0.5f, -0.5f, 1.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f},
        (rdrVertex){+0.5f, +0.5f, .5f, +0.5f, +0.5f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f},

        // Back
        (rdrVertex){-0.5f, -0.5f, -.5f, -0.5f, -0.5f, -1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f},
        (rdrVertex){+0.5f, -0.5f, -.5f, +0.5f, -0.5f, -1.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f},
        (rdrVertex){-0.5f, +0.5f, -.5f, -0.5f, +0.5f, -1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f},

        (rdrVertex){-0.5f, +0.5f, -.5f, -0.5f, +0.5f, -1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f},
        (rdrVertex){+0.5f, -0.5f, -.5f, +0.5f, -0.5f, -1.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f},
        (rdrVertex){+0.5f, +0.5f, -.5f, +0.5f, +0.5f, -1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f},

        // Left
        (rdrVertex){-0.5f, -0.5f, -.5f, -1.f, -0.5f, -.5f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f},
        (rdrVertex){-0.5f, -0.5f, +.5f, -1.f, -0.5f, +.5f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f},
        (rdrVertex){-0.5f, +0.5f, -.5f, -1.f, +0.5f, -.5f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f},

        (rdrVertex){-0.5f, +0.5f, -.5f, -1.f, +0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f},
        (rdrVertex){-0.5f, -0.5f, +.5f, -1.f, -0.5f, +0.5f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f},
        (rdrVertex){-0.5f, +0.5f, +.5f, -1.f, +0.5f, +0.5f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f},

        // Right 
        (rdrVertex){+0.5f, -0.5f, -.5f, 1.f, -0.5f, -.5f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f},
        (rdrVertex){+0.5f, -0.5f, +.5f, 1.f, -0.5f, +.5f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f},
        (rdrVertex){+0.5f, +0.5f, -.5f, 1.f, +0.5f, -.5f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f},

        (rdrVertex){+0.5f, +0.5f, -.5f, 1.f, +0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f},
        (rdrVertex){+0.5f, -0.5f, +.5f, 1.f, -0.5f, +0.5f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f},
        (rdrVertex){+0.5f, +0.5f, +.5f, 1.f, +0.5f, +0.5f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f},

        // Top
        (rdrVertex){ 0.5f,  0.5f, +0.5f,  0.5f, 1.f, +0.5f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f},
        (rdrVertex){-0.5f,  0.5f, +0.5f, -0.5f, 1.f, +0.5f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f},
        (rdrVertex){-0.5f,  0.5f, -0.5f, -0.5f, 1.f, -0.5f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f},

        (rdrVertex){ 0.5f,  0.5f, +0.5f,  0.5f, 1.f, +0.5f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f},
        (rdrVertex){-0.5f,  0.5f, -0.5f, -0.5f, 1.f, -0.5f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f},
        (rdrVertex){ 0.5f,  0.5f, -0.5f,  0.5f, 1.f, -0.5f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f},

        // Bottom
        (rdrVertex){ 0.5f, -0.5f, +0.5f,  0.5f, -1.f, +0.5f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f},
        (rdrVertex){-0.5f, -0.5f, -0.5f, -0.5f, -1.f, -0.5f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f},
        (rdrVertex){-0.5f, -0.5f, +0.5f, -0.5f, -1.f, +0.5f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f},

        (rdrVertex){ 0.5f, -0.5f, +0.5f,  0.5f, -1.f, +0.5f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f},
        (rdrVertex){ 0.5f, -0.5f, -0.5f,  0.5f, -1.f, -0.5f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f},
        (rdrVertex){-0.5f, -0.5f, -0.5f, -0.5f, -1.f, -0.5f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f},};

    cube.transformModel = Mat4::CreateTransformationMatrix({0.f, 0.f, 2.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 180.f});
    return cube;
}

Object Object::Square()
{
    Object square;
    square.vertices = (std::vector<rdrVertex>){
        (rdrVertex){-0.5f, -0.5f, 0.f, -.5f, -.5f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f},
        (rdrVertex){+0.5f, -0.5f, 0.f, +.5f, -.5f, 1.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f},
        (rdrVertex){-0.5f, +0.5f, 0.f, -.5f, +.5f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f},

        (rdrVertex){-0.5f, +0.5f, 0.f, -0.5f, +0.5f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f},
        (rdrVertex){+0.5f, -0.5f, 0.f, +0.5f, -0.5f, 1.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f},
        (rdrVertex){+0.5f, +0.5f, 0.f, +0.5f, +0.5f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f},};

    square.transformModel = Mat4::CreateTransformationMatrix({0.f, 0.f, 2.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 180.f});
    return square;
}

static Vec3 getSphericalCoords(float r, float theta, float phi)
{
    return {r * sinf(theta) * cosf(phi),
            r * cosf(theta),
            r * sinf(theta) * sinf(phi)};
}

float sphereSDF(Vec3 samplePoint)
{
    return samplePoint.Magnitude() - 1.0;
}

Vec3 getSphereNormal(Vec3 p)
{
    const float EPSILON = 0.00001;
    Vec3 normal (
        sphereSDF(Vec3(p.x + EPSILON, p.y, p.z)) - sphereSDF(Vec3(p.x - EPSILON, p.y, p.z)),
        sphereSDF(Vec3(p.x, p.y + EPSILON, p.z)) - sphereSDF(Vec3(p.x, p.y - EPSILON, p.z)),
        sphereSDF(Vec3(p.x, p.y, p.z + EPSILON)) - sphereSDF(Vec3(p.x, p.y, p.z - EPSILON)));
    return normal.Normalize();
}

Object Object::Sphere(const int lon, const int lat)
{
    Object sphere;
    float r = 0.5f;

    for (int j = 0; j < lat; ++j)
    {
        float theta0 = ((j + 0) / (float)lat) * M_PI;
        float theta1 = ((j + 1) / (float)lat) * M_PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi0 = ((i + 0) / (float)lon) * 2.f * M_PI;
            float phi1 = ((i + 1) / (float)lon) * 2.f * M_PI;

            Vec3 c0 = getSphericalCoords(r, theta0, phi0);
            Vec3 c1 = getSphericalCoords(r, theta0, phi1);
            Vec3 c2 = getSphericalCoords(r, theta1, phi1);
            Vec3 c3 = getSphericalCoords(r, theta1, phi0);

            Vec3 normalC0 = getSphereNormal(c0);
            Vec3 normalC1 = getSphereNormal(c1);
            Vec3 normalC2 = getSphereNormal(c2);
            Vec3 normalC3 = getSphereNormal(c3);

            sphere.vertices.push_back({c0.x, c0.y, c0.z, normalC0.x, normalC0.y, normalC0.z, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f});
            sphere.vertices.push_back({c1.x, c1.y, c1.z, normalC1.x, normalC1.y, normalC1.z, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f});
            sphere.vertices.push_back({c2.x, c2.y, c2.z, normalC2.x, normalC2.y, normalC2.z, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f});

            sphere.vertices.push_back({c0.x, c0.y, c0.z, normalC0.x, normalC0.y, normalC0.z, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f});
            sphere.vertices.push_back({c2.x, c2.y, c2.z, normalC2.x, normalC2.y, normalC2.z, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f});
            sphere.vertices.push_back({c3.x, c3.y, c3.z, normalC3.x, normalC3.y, normalC3.z, 0.f, 0.f, 0.f, 1.f, 1.f, 1.f});
        }
    }

    sphere.transformModel = Mat4::CreateTransformationMatrix({0.f, 0.f, 2.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 180.f});
    return sphere;
}

void Object::Draw(Renderer& renderer, std::vector<Light> lights, const Vec3& positionCam, Vec3 &RGB)
{
    renderer.SetModel(transformModel);
    renderer.SetTexture(texture);
    renderer.DrawTriangles(vertices.data(), (int)vertices.size(), lights, positionCam, alpha, RGB);
}

void Object::SetTransformModel(const Vec3& translation, const Vec3 &scale, const Vec3 &rotation)
{
    transformModel = Mat4::CreateTransformationMatrix(translation, scale, rotation);
}

void Object::SetOpacity(float alphaSet)
{
    alpha = alphaSet;
}