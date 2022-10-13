#pragma once
#include <myMath.hpp>
class Light
{
private:
public:
    float ambientComponent;
    float diffuseComponent;
    float specularComponent;
    Vec3 position;
    Light(const Vec3 &position, const float ambientComponent, const float diffuseComponent, const float specularComponent);
    ~Light();

    float CalcLightIntensity(const Vec3& position, const Vec3& normalPosition, const Vec3& positionCam, const float alpha);
};
