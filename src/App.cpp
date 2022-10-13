#include <App.hpp>
#include <Renderer.hpp>
#include <Framebuffer.hpp>
#include <Camera.hpp>
#include <Scene.hpp>
#include <Texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//Get back Events and setup ImGUI frame
void App::NewFrame(bool mouseCaptured)
{
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    if (mouseCaptured)
        ImGui::GetIO().MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
    ImGui::NewFrame();
}

//Clear buffer et render ImGUI
void App::EndFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

//Constructor with Init struct
App::App(const AppInit &p_init)
{
    // Setup glfw
    glfwSetErrorCallback(p_init.ErrorCallback);
    if (!glfwInit())
    {
        printf("glfwInit failed\n");
        state = GLFWFAILED;
        return;
    }

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    window = glfwCreateWindow(p_init.width, p_init.height, p_init.title, nullptr, nullptr);
    if (window == nullptr)
    {
        printf("glfwCreateWindow failed\n");
        state = WINDOWFAILED;
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // V-Sync

    // Setup glad
    if (gladLoadGL((GLADloadfunc)glfwGetProcAddress) == 0)
    {
        printf("gladLoaderLoadGL failed\n");
        state = GLADFAILED;
        return;
    }

    // Setup KHR debug
    if (GLAD_GL_KHR_debug)
    {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(p_init.DebugMessageCallback, NULL);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_PERFORMANCE, GL_DONT_CARE, 0, nullptr, GL_FALSE);
        glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 0, nullptr, GL_FALSE);
    }

    printf("GL_VENDOR: %s\n", glGetString(GL_VENDOR));
    printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));

    // Setup Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    state = SUCCESS;
}

//Update device and call the renderer
void App::Update()
{

    bool mouse = false;

    // Create renderer framebuffer (color+depth+opengl texture)
    // We need an OpenGL texture to display the result of the renderer to the screen
    // Init renderer
    Renderer renderer(
        800, 600);

    Framebuffer *framebuffer = renderer.getFrameBuffer();

    Scene scene;
    scene.Init(renderer);

    InputsCamera inputs;
    Camera* camera = renderer.GetCamera();

    bool mouseCaptured = false;
    double mouseX = 0.0;
    double mouseY = 0.0;
    float mouseDeltaX = 0.0;
    float mouseDeltaY = 0.0;
    scene.switchScene = SCENE1;

    ShapeData shapeData = 
    {
        (Vec3){0.f, 0.f, 5.f},    // Translation (Vec3)
        (Vec3){0.f, 0.f, 0.f},    // Rotation (Vec3)
        (Vec3){1.f, 1.f, 1.f},    // Scale (Vec3)
        new Texture,
    };
    shapeData.texture->LoadTexture("texture/textWood.bmp");

    ShapeData shapeData2 = 
    {
        (Vec3){0.f, 0.f, 5.f},    // Translation (Vec3)
        (Vec3){0.f, 0.f, 0.f},  // Rotation (Vec3)
        (Vec3){1.f, 1.f, 1.f},    // Scale (Vec3)
        new Texture,
    };
    shapeData2.texture->LoadTexture("texture/lowRez.bmp");

    SceneData sceneData = 
    {
        ImGui::GetIO().DeltaTime,
        renderer,
        camera->GetPosition(),
    };

    while (glfwWindowShouldClose(window) == false)
    {
        NewFrame(mouseCaptured); //ImGui
        {
            double newMouseX, newMouseY;
            glfwGetCursorPos(window, &newMouseX, &newMouseY);
            mouseDeltaX = (float)(newMouseX - mouseX);
            mouseDeltaY = (float)(newMouseY - mouseY);
            mouseX = newMouseX;
            mouseY = newMouseY;
        }

        // Update camera
        if (ImGui::IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            mouseCaptured = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        if (mouseCaptured)
        {
            inputs.deltaX        = mouseDeltaX;
            inputs.deltaY        = mouseDeltaY;
            inputs.moveForward   = ImGui::IsKeyDown(GLFW_KEY_W);
            inputs.moveBackward  = ImGui::IsKeyDown(GLFW_KEY_S);
            inputs.moveDown      = ImGui::IsKeyDown(GLFW_KEY_LEFT_SHIFT);
            inputs.moveUp        = ImGui::IsKeyDown(GLFW_KEY_SPACE);
            inputs.moveLeft      = ImGui::IsKeyDown(GLFW_KEY_A);
            inputs.moveRight     = ImGui::IsKeyDown(GLFW_KEY_D);
        }
            camera->Update(inputs);

        if (ImGui::IsKeyPressed(GLFW_KEY_F1))
            renderer.SetWireFrame(!renderer.GetWireFrame());

        if (ImGui::IsKeyPressed(GLFW_KEY_F2))
            scene.switchScene = SCENE1;

        if (ImGui::IsKeyPressed(GLFW_KEY_F3))
            scene.switchScene = SCENE2;

        if (ImGui::IsKeyPressed(GLFW_KEY_F4))
            scene.switchScene = SCENE3;

        if (ImGui::IsKeyPressed(GLFW_KEY_F5))
            scene.switchScene = SCENE4;

        if (ImGui::IsKeyPressed(GLFW_KEY_F6))
            scene.switchScene = SCENE5;   

        if (ImGui::IsKeyPressed(GLFW_KEY_F7))
            scene.switchScene = SCENE6;  

        // Clear buffers
        framebuffer->Clear();

        // Setup matrices
        Mat4 projection = camera->GetProjection();
        Mat4 view = camera->GetViewMatrix();
        renderer.SetProjection(projection);
        renderer.SetView(view);

        // sceneData update
        sceneData.deltaTime = ImGui::GetIO().DeltaTime;
        sceneData.positionCam = camera->GetPosition();

        // Render scene
        scene.Update(sceneData, shapeData, shapeData2, scene.lights[0].position);

        // Upload texture
        framebuffer->UpdateTexture();
        // Display debug controls

        if (ImGui::Begin("Config"))
        {
            if (ImGui::CollapsingHeader("Framebuffer", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::ColorEdit4("clearColor", &(framebuffer->clearColor.x));
            }
            if (ImGui::CollapsingHeader("Objects transformation", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::SliderFloat3("Translation (Object 1)", &shapeData.translation.x, -3.f, 20.f, "%.1f", 0);
                ImGui::SliderFloat3("Rotation (Object 1)", &shapeData.rotation.x, 0.f, 180.f, "%1.f", 0);
                ImGui::SliderFloat3("Scale (Object 1)", &shapeData.scale.x, 0.5f, 2.f, "%.2f", 0);
                ImGui::SliderFloat3("Translation (Object 2)", &shapeData2.translation.x, -3.f, 20.f, "%.1f", 0);
                ImGui::SliderFloat3("Rotation (Object 2)", &shapeData2.rotation.x, 0.f, 180.f, "%1.f", 0);
                ImGui::SliderFloat3("Scale (Object 2)", &shapeData2.scale.x, 0.5f, 2.f, "%.2f", 0);
            }
            if (ImGui::CollapsingHeader("LightPosition", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::SliderFloat3("Position", &scene.lights[0].position.x, -5.f, 5.f, "%.1f", 0);
            }
             if (ImGui::CollapsingHeader("LightValues", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::SliderFloat("Ambient", &scene.lights[0].ambientComponent,0.f, 1.f, "%.3f", 0);
                ImGui::SliderFloat("Diffuse", &scene.lights[0].diffuseComponent,0.f, 1.f, "%.3f", 0);
                ImGui::SliderFloat("Specular", &scene.lights[0].specularComponent,0.f, 1.f, "%.3f", 0);
            }
        }
        ImGui::End();

        ImGui::Begin("Framebuffer");
        ImGui::Text("(Right click to capture mouse, Esc to un-capture)");
        // Display framebuffer (renderer output)
        ImGui::Image((ImTextureID)(size_t)framebuffer->GetColorTexture(), {(float)framebuffer->GetWidth(), (float)framebuffer->GetHeight()});
        if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
        {
            mouseCaptured = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        ImGui::End();
        EndFrame();
    }

    delete shapeData.texture;
    delete shapeData2.texture;
}

//destructor who kill glfw and clean the window buffer
App::~App()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
