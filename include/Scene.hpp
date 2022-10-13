#pragma once
#include <vector>
#include <Renderer.hpp>
#include "Light.hpp"

struct ShapeData
{
    Vec3 translation;
    Vec3 rotation;
    Vec3 scale;
    Texture* texture;
};

struct SceneData
{
    float deltaTime;
    Renderer& renderer;
    Vec3 positionCam;
};

enum SwitchScene
{
    SCENE1,
    SCENE2,
    SCENE3,
    SCENE4,
    SCENE5, 
    SCENE6
};

class Scene
{
private:
    double time = 0.0;
    float scale = 1.f;
    float rotation = 0.f;
    
public:
    std::vector<Light> lights;
    SwitchScene switchScene;
    Scene();
    ~Scene();

    void Init(Renderer& renderer);
    void Update(SceneData& sceneData, ShapeData& shapeData,ShapeData& shapeData2, const Vec3 &lightposition);

private:
    void ShowImGuiControls();
};


