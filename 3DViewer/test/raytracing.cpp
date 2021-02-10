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

#include "../imgui/imgui.h"
#include"../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

using namespace rtx;
using namespace std;

void raytracing_processInput(Window window);

int raytracing()
{

	Window App(glm::vec2(800, 600), "Real-time Ray Tracing",
		Window::ClearMode::DepthMode, false);
	glm::vec2 appSize = App.GetSize();

	// Camera
	FPSCamera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
		45.0f, appSize.x / appSize.y, 0.01f, 100.0f, 5.0f);

	//  Raytracing render target 
	graph::Sprite canvas;
	canvas.GetTransform().SetScale(glm::vec3(4.0f, 3.0f, 1.0f));
	canvas.GetTransform().SetOrigin(glm::vec3(0.5f, 0.5f, 0.0f));
	/*canvas.GetTransform().SetScale(glm::vec3(3.0f, 3.0f, 3.0f));
	canvas.GetTransform().SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	canvas.GetTransform().SetOrigin(glm::vec3(0.0f, 0.0f, 0.5f));*/
	render::Shader shader("../data/shader/raytracingPlus.vert",
		"../data/shader/raytracingPlus.frag");
	//  texture (material)
	render::Texture diffuseTex;
	diffuseTex.LoadFromFile("../data/texture/container2.png");
	render::Texture specularTex;
	specularTex.LoadFromFile("../data/texture/container2_specular.png");
	shader.Use();
	diffuseTex.Bind(0);
	shader.SetSampler2D("_material.diffuse", 0);
	specularTex.Bind(1);
	shader.SetSampler2D("_material.specular", 1);
	shader.SetInt("_material.shininess", 32);
	
	//  transform
	shader.SetMatrix4("_view", camera.GetCamera().GetView());
	shader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
	shader.SetMatrix4("_model", canvas.GetTransform().GetTransMat());
	//  reset the fpsCamera to the raytracing camera 
	/*camera.GetCamera().SetOrigin(glm::vec3(0.0f, 0.0f, 2.0f));
	camera.GetCamera().SetTarget(glm::vec3(0.0f, 0.0f, -1.0f));
	camera.Update(App);*/
	shader.SetVector3("_camera.lookFrom", camera.GetCamera().GetOrigin());
	glm::vec3 leftButtom(0.0f), horizontal(0.0f), vertical(0.0f);
	camera.GetCamera().GetLeftBottom(leftButtom, horizontal, vertical);
	shader.SetVector3("_camera.left_buttom", leftButtom);
	shader.SetVector3("_camera.horizontal", horizontal);
	shader.SetVector3("_camera.vertical", vertical);
	//  get screen size
	shader.SetVector2("_screen_size", appSize);

	//  ui setting
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(App.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsClassic();
	bool show_demo_window = true;
	int currentItem = 0;
	const char* itemStr = "Fill\0Line\0Point\0";

	//  tracing shader rand seed
	float randSeed[4];
	util::RayMath::Srand48((unsigned int)time(NULL));
	int MinSamplerTimes = 5;
	int MaxSamplerTimes = 20;
	int SamplerTimes = 1;
	float sssTime = 0.0f;
		
	//  start rendering
	App.DrawStart(Window::DrawMode::Fill);
	while (App.isOpen())
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Propertis Window", &show_demo_window);
		//ImGui::SliderFloat3("Light Position", glm::value_ptr(lightPos), -5.0f, 5.0f, "%.3f", 1.0f);
		ImGui::SliderInt("Min Sampler Times", &MinSamplerTimes, 3, 20);
		ImGui::SliderInt("Max Sampler Times", &MaxSamplerTimes, 20, 40);
		ImGui::Text(("Sampler Times Per Second: " + to_string(SamplerTimes)).c_str());
		ImGui::Text(("FPS: " + to_string(1.0f / system::Time::deltaTime()) + "\n").c_str());
		if (ImGui::Combo("Draw Mode", &currentItem, itemStr))
		{
			switch (currentItem)
			{
			case 0:
				App.SetDrawMode(Window::DrawMode::Fill);
				break;
			case 1:
				App.SetDrawMode(Window::DrawMode::Line);
				break;
			case 2:
				App.SetDrawMode(Window::DrawMode::Point);
				break;
			default:
				break;
			}
		}
		if (ImGui::Button("Close Me"))
			glfwSetWindowShouldClose(App.GetWindow(), true);
		ImGui::End();

		ImGui::Render();

		raytracing_processInput(App);

		App.pollEvents();

		App.Clear(0x123456);

		camera.Update(App);
		sssTime += system::Time::deltaTime();
		if (event::Mouse::isMouseMoved())
		{
			sssTime = 0.0f;
			SamplerTimes = MinSamplerTimes;
		}
		else if (sssTime > 0.4f)
		{
			SamplerTimes = std::min(MaxSamplerTimes, SamplerTimes + 1);
		}
		//  draw object
		for (size_t i = 0; i < 4; i++)
			randSeed[i] = static_cast<float>(util::RayMath::Drand48());
		shader.Use();
		shader.SetVector2("_screen_size", App.GetSize());
		shader.SetArray("_rdSeed", 4, randSeed);
		shader.SetInt("_maxSampeler", SamplerTimes);
		shader.SetVector3("_camera.lookFrom", camera.GetCamera().GetOrigin());
		camera.GetCamera().GetLeftBottom(leftButtom, horizontal, vertical);
		shader.SetVector3("_camera.left_buttom", leftButtom);
		shader.SetVector3("_camera.horizontal", horizontal);
		shader.SetVector3("_camera.vertical", vertical);
		//  Don't move the render sprite
		/*shader.SetMatrix4("_view", camera.GetCamera().GetView());
		shader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
		shader.SetMatrix4("_model", canvas.GetTransform().GetTransMat());*/

		App.Draw(canvas);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		App.Display();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

	return EXIT_SUCCESS;
}

void raytracing_processInput(Window window)
{
	//  press ESC to close window and exit
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window.GetWindow(), true);
}
