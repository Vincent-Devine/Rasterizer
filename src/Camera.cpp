#include <imgui.h>
#include <Camera.hpp>

Camera::Camera(const int width, const int height)
    : aspect((float)width/(float)height)
{
}

void Camera::Update(const InputsCamera& inputsCamera)
{
    rotation.y -= inputsCamera.deltaX / 6.f; 
    rotation.x += inputsCamera.deltaY / 6.f;

    if (rotation.x < -90)
        rotation.x = -90;

    if (rotation.x > 90)
        rotation.x = 90;

    if (rotation.y > 360)
        rotation.y = -360;

    if (rotation.y < -360)
        rotation.y = 360;

    if(inputsCamera.moveForward)
    {
        position.x -= speed*cosf(DEG2RAD*(rotation.y + 90));
        position.z += speed*sinf(DEG2RAD*(rotation.y + 90));
    }
    if(inputsCamera.moveBackward)
    {
        position.x += speed*cosf(DEG2RAD*(rotation.y + 90));
        position.z -= speed*sinf(DEG2RAD*(rotation.y + 90));
    }

    if (inputsCamera.moveLeft)
    {
        position.x += speed*cosf(DEG2RAD*(rotation.y));
        position.z -= speed*sinf(DEG2RAD*(rotation.y));
    }
    if (inputsCamera.moveRight)
    {
        position.x -= speed*cosf(DEG2RAD*(rotation.y));
        position.z += speed*sinf(DEG2RAD*(rotation.y));
    }

    if (inputsCamera.moveUp)
        position.y += speed;

    if (inputsCamera.moveDown)
        position.y -= speed;
}

Mat4 Camera::GetViewMatrix()
{
    return Mat4::CreateXRotationMatrix(-rotation.x) 
         * Mat4::CreateYRotationMatrix(-rotation.y) 
         * Mat4::CreateTranslationMatrix(-position);
}

Mat4 Camera::GetProjection()
{
    float a = 1.f / tanf(DEG2RAD*FOV/2.f);

    Mat4 projection(
        a / aspect, 0.f, 0.f,                    0.f,
        0.f,        a,   0.f,                    0.f,
        0.f,        0.f, -(far+near)/(far-near), -(2*far*near)/(far-near),
        0.f,        0.f, -1.f,                   0.f
    );

    return projection;
}

void Camera::ShowImGuiControls()
{
}