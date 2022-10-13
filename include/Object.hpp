#pragma once

#include <vector>
#include <myMath.hpp>
#include <Texture.hpp>
#include <Renderer.hpp>

class Object
{
private:
    Mat4 transformModel;
    Texture* texture;
    float alpha;

public:
    std::vector<rdrVertex> vertices;
    Object();
    Object(const std::vector<rdrVertex>& vertices, const Mat4& p_transformModel);
    ~Object();

    static Object Triangle();
    static Object Cube();
    static Object Sphere(const int lon, const int lat);
    static Object Square();

    void Draw(Renderer& renderer, std::vector<Light> lights, const Vec3& positionCam, Vec3 &RGB);

    std::vector<rdrVertex> GetVertices() {return vertices;};
    const Mat4 GetTransformModel() {return transformModel;};
    Texture* GetTexture() {return texture;};
    void SetVertices(const std::vector<rdrVertex>& p_vertices) {vertices = p_vertices;};
    void SetTransformModel(const Vec3& translation, const Vec3 &scale, const Vec3 &rotation);
    void SetTexture(Texture* p_texture) {texture = p_texture;};
    void SetOpacity(float alpha);
};