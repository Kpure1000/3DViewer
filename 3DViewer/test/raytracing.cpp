#include"raytracing.h"

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<thread>

#include"../graph/Graph.h"
#include"../render/Render.h"
#include"../render/Image.h"
#include"../util/Color.h"
#include"../render/Texture.h"

using namespace rtx;
using namespace std;

void raytracing_processInput(Window window);

int raytracing()
{

    Window App(glm::vec2(800, 600), "Real-time Ray Tracing", Window::ClearMode::DepthMode, false);
    glm::vec2 appSize = App.GetSize();

    graph::Sprite canvas;
    canvas.GetTransform().SetScale(glm::vec3(4.0f,3.0f,1.0f));
    canvas.GetTransform().SetPosition(glm::vec3(-2.0f, -1.5f, 0.0f));

    FPSCamera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
        45.0f, appSize.x / appSize.y, 0.01f, 100.0f, 10.0f);

    render::Shader shader("../data/shader/raytracing.vert",
        "../data/shader/raytracing.frag");

    glm::vec3 leftButtom, horizontal, vertical;

    shader.Use();
    shader.SetVector2("_screen_size", appSize);
    shader.SetMatrix4("_view", camera.GetCamera().GetView());
    shader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
    shader.SetMatrix4("_model", canvas.GetTransform().GetTransMat());

    camera.GetCamera().SetOrigin(glm::vec3(0.0f, 0.0f, 2.0f));
    camera.GetCamera().SetTarget(glm::vec3(-2.0f, -1.0f, -1.0f));

    camera.Update(App);

    shader.SetVector3("ca_lookFrom", camera.GetCamera().GetOrigin());
    camera.GetCamera().GetLeftBottom(leftButtom, horizontal, vertical);
    shader.SetVector3("ca_left_buttom", leftButtom);
    shader.SetVector3("ca_horizontal", horizontal);
    shader.SetVector3("ca_vertical", vertical);

    App.DrawStart(Window::DrawMode::Fill);

    float randSeed[4];
    util::RayMath::Srand48((unsigned int)time(NULL));
    while (App.isOpen())
    {
        raytracing_processInput(App);

        App.Clear(0x123456);

        camera.Update(App);

        for (size_t i = 0; i < 4; i++)
            randSeed[i] = static_cast<float>(util::RayMath::Drand48());
        shader.Use();
        shader.SetVector2("_screen_size", appSize);
        shader.SetArray("_rdSeed", 4, randSeed);
        /*shader.SetVector3("ca_lookFrom", glm::vec3(0.0f, 0.0f, 2.0f));
        shader.SetVector3("ca_left_buttom", glm::vec3(-2.0f, -1.0f, -1.0f));
        float horizontal_ca = 4.0f;
        shader.SetVector3("ca_horizontal", glm::vec3(horizontal_ca, 0.0f, 0.0f));
        shader.SetVector3("ca_vertical", glm::vec3(0.0f, horizontal_ca * appSize.y / appSize.x, 0.0f));*/

        shader.SetVector3("ca_lookFrom", camera.GetCamera().GetOrigin());
        camera.GetCamera().GetLeftBottom(leftButtom, horizontal, vertical);
        shader.SetVector3("ca_left_buttom", leftButtom);
        shader.SetVector3("ca_horizontal", horizontal);
        shader.SetVector3("ca_vertical", vertical);
        App.Draw(canvas);

        App.Display();
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}

void raytracing_processInput(Window window)
{
    //  press ESC to close window and exit
    if (glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.GetWindow(), true);
}
