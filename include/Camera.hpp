#pragma once

#include <myMath.hpp>

struct InputsCamera
{
    float deltaX = 0.f;
    float deltaY = 0.f;
    bool moveForward    = true;
    bool moveBackward   = true;
    bool moveRight      = true;
    bool moveLeft       = true;
    bool moveUp         = true;
    bool moveDown       = true;
};

class Camera
{
private:
    Vec3 position;
    Vec3 rotation;
    float far       = 20.f;
    float near      =  1.f;
    float right     =  1.f;
    float left      = -1.f;
    float top       =  1.f;
    float bottom    = -1.f;

    float FOV       = 60.f;
    float speed     = 0.1f;
    float aspect    = 0.f;

public:
    Camera(const int width = 1, const int height = 1);

    void Update(const InputsCamera& inputsCamera);

    Mat4 GetViewMatrix();
    Mat4 GetProjection();

    // Get
    const Vec3 GetPosition() {return position;};
    const Vec3 GetRotation() {return rotation;};
    const float GetFar() {return far;};
    const float GetNear() {return near;};
    // Set
    void SetPosition(const Vec3& p_position) {position = p_position;};
    void SetRotation(const Vec3& p_rotation) {rotation = p_rotation;};
    void SetFOV(const float p_fov) {FOV = p_fov;};
    void SetRenderDistance(const float p_near, const float p_far) {near = p_near; far = p_far;};
    void SetSpeed(const float p_speed) {speed = p_speed;};
    
    // ImGui
    void ShowImGuiControls();
};