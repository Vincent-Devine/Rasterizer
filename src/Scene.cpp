#include <imgui.h>
#include <myMath.hpp>
#include <Scene.hpp>
#include <Object.hpp>

Scene::Scene()
{
    lights.push_back({(Vec3){-0.5f,0.f,1.2f},0.2, 0.4,0.4f});
}

Scene::~Scene()
{
}

void Scene::Init(Renderer& renderer)
{
    renderer.SetView(Mat4::CreateTransformationMatrix({0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 0.f}));
    renderer.SetProjection(Mat4::CreateTransformationMatrix({0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 0.f}));
}

void Scene::Update(SceneData& sceneData, ShapeData& shapeData,ShapeData& shapeData2, const Vec3 &lightposition)
{
    switch(switchScene)
    {
        // Scene Triangle colored 
    case SCENE1:
        {
            Vec3 RGB = {1.f, 1.f,1.f};
            Object triangle = Object::Triangle();
            triangle.SetTransformModel({shapeData.translation.x, shapeData.translation.y, shapeData.translation.z-3.f}, shapeData.scale, shapeData.rotation);
            triangle.Draw(sceneData.renderer, lights, sceneData.positionCam, RGB);
            break;
        }

        // Scene Buffer
    case SCENE2:
        {
            Vec3 RGB1 = {0.f, 1.f,1.f};
            Vec3 RGB2 = {1.f, 0.f,0.f};
            Object triangle = Object::Triangle();
            triangle.SetTransformModel({shapeData.translation.x, shapeData.translation.y, shapeData.translation.z-3.f}, shapeData.scale, shapeData.rotation);
            triangle.Draw(sceneData.renderer, lights, sceneData.positionCam, RGB1);
            Object triangle2 = Object::Triangle();
            triangle2.SetTransformModel({shapeData2.translation.x - 0.25f, shapeData2.translation.y + 0.25f, shapeData2.translation.z-3.f}, shapeData2.scale, {shapeData2.rotation.x, shapeData2.rotation.y + 45.f, shapeData2.rotation.z});
            triangle2.Draw(sceneData.renderer, lights, sceneData.positionCam, RGB2);
            break;
        }

        // Scene Lights
    case SCENE3:
        {
            Vec3 RGB1 = {0.3f, 0.7f, 0.f};
            Object sphere = Object::Sphere(20, 20);
            sphere.SetTransformModel({shapeData.translation.x, shapeData.translation.y, shapeData.translation.z-2.f}, shapeData.scale, {shapeData.rotation.x, rotation, shapeData.rotation.z});
            sphere.Draw(sceneData.renderer, lights, sceneData.positionCam,RGB1);

            Vec3 RGB2 = {0.9f, 0.9f, 0.9f};
            Object sphere2 = Object::Sphere(10, 10);
            sphere2.SetTransformModel(lightposition, {0.15f, 0.15f, 0.15f}, {shapeData.rotation.x, rotation, shapeData.rotation.z});
            sphere2.Draw(sceneData.renderer, lights, sceneData.positionCam,RGB2);
            break;
        }

        // Scene Opacity
    case SCENE4:
        {        
            Vec3 RGB1 = {1.f, 1.f, 0.f};
            Vec3 RGB2 = {0.f, 0.5f, 0.5f};
            Object sphere = Object::Sphere(20, 20);
            sphere.SetTransformModel({shapeData.translation.x, shapeData.translation.y, shapeData.translation.z-2.f}, shapeData.scale, {shapeData.rotation.x, rotation, shapeData.rotation.z});
            sphere.SetOpacity(1.f);

            Object square = Object :: Square();
            square.SetTransformModel({shapeData2.translation.x + 0.5f, shapeData2.translation.y, shapeData2.translation.z-3.f}, shapeData2.scale, {shapeData2.rotation.x, shapeData2.rotation.y +180.f, shapeData2.rotation.z});
            square.SetOpacity(0.25f);

            sphere.Draw(sceneData.renderer, lights, sceneData.positionCam,RGB2);
            square.Draw(sceneData.renderer, lights, sceneData.positionCam,RGB1);
            break;
        }
        // Scene Rotating cube 
    case SCENE5:
        {
            Vec3 RGB = {0.5f, 0.5f,0.f};
            Object cube = Object::Cube();
            cube.SetTransformModel(shapeData.translation, {shapeData.scale.x+1.f, shapeData.scale.y+1.f, shapeData.scale.z+1.f }, {shapeData.rotation.x, rotation, shapeData.rotation.z});

            cube.Draw(sceneData.renderer, lights, sceneData.positionCam,RGB);
            break;
        }
        
        // Scene Texture
    case SCENE6:
        {
            Vec3 RGB = {0.5f, 0.5f,0.5f};
            Object cube = Object::Cube();
            cube.SetTransformModel({shapeData.translation.x+1.5f, shapeData.translation.y, shapeData.translation.z}, {shapeData.scale.x+0.5f, shapeData.scale.y+0.5f, shapeData.scale.z+0.5f }, {shapeData.rotation.x, shapeData.rotation.y +45.f, shapeData.rotation.z});
            cube.SetTexture(shapeData.texture);

            Object cube2 = Object::Cube();
            cube2.SetTransformModel({shapeData.translation.x-1.5f, shapeData.translation.y, shapeData.translation.z}, {shapeData2.scale.x+0.5f, shapeData2.scale.y+0.5f, shapeData2.scale.z+0.5f }, {shapeData2.rotation.x, shapeData2.rotation.y +25.f, shapeData2.rotation.z});
            cube2.SetTexture(shapeData2.texture);

            cube.Draw(sceneData.renderer, lights, sceneData.positionCam,RGB);
            cube2.Draw(sceneData.renderer, lights, sceneData.positionCam,RGB);
            break;
        }
    default:
        break;
    }

    rotation++;

    time += sceneData.deltaTime;
}

void Scene::ShowImGuiControls()
{
    ImGui::SliderFloat("scale", &scale, 0.f, 10.f);
}