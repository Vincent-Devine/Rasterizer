#include "Light.hpp"

Light::Light(const Vec3 &position, const float ambientComponent, const float diffuseComponent, const float specularComponent)
    : ambientComponent(ambientComponent)
    , diffuseComponent (diffuseComponent)
    , specularComponent(specularComponent)
    , position(position)
{

}

Light::~Light()
{
}

float Light::CalcLightIntensity(const Vec3& positionPixel, const Vec3& normalPosition, const Vec3& positionCam, const float alpha)
{
    // Diffuse
    Vec3 vecLight = position - positionPixel;
    Vec3 vecNormal = normalPosition - positionPixel;
    float angleTheta = vecLight.DotProduct(vecNormal) / (vecLight.Magnitude() * vecNormal.Magnitude());
    
    // Specular
    Vec3 vecView = positionCam - positionPixel;
    Vec3 vecReflection = vecNormal * 2.f * angleTheta - vecLight;
    float angleOmega = vecView.DotProduct(vecReflection) / (vecView.Magnitude() * vecReflection.Magnitude());

    
    // Ambient + Diffuse + Specular
    return ambientComponent + (angleTheta * diffuseComponent) + (specularComponent * powf(angleOmega, alpha));
}