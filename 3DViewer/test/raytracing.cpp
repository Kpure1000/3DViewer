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

	graph::Sprite canvas;
	canvas.GetTransform().SetScale(glm::vec3(4.0f, 3.0f, 1.0f));
	canvas.GetTransform().SetPosition(glm::vec3(-2.0f, -1.5f, 0.0f));

	FPSCamera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
		45.0f, appSize.x / appSize.y, 0.01f, 100.0f, 5.0f);

	render::Shader shader("../data/shader/raytracing.vert",
		"../data/shader/raytracing.frag");


	shader.Use();
	shader.SetVector2("_screen_size", appSize);
	shader.SetMatrix4("_view", camera.GetCamera().GetView());
	shader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
	shader.SetMatrix4("_model", canvas.GetTransform().GetTransMat());

	camera.GetCamera().SetOrigin(glm::vec3(0.0f, 0.0f, 2.0f));
	camera.GetCamera().SetTarget(glm::vec3(0.0f, 0.0f, -1.0f));
	camera.Update(App);

	shader.SetVector3("ca_lookFrom", camera.GetCamera().GetOrigin());
	glm::vec3 leftButtom(0.0f), horizontal(0.0f), vertical(0.0f);
	camera.GetCamera().GetLeftBottom(leftButtom, horizontal, vertical);
	shader.SetVector3("ca_left_buttom", leftButtom);
	shader.SetVector3("ca_horizontal", horizontal);
	shader.SetVector3("ca_vertical", vertical);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(App.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsClassic();
	bool show_demo_window = true;

	App.DrawStart(Window::DrawMode::Fill);

	float randSeed[4];
	util::RayMath::Srand48((unsigned int)time(NULL));
	while (App.isOpen())
	{
		std::string outStr = "Camera Information\nOrigin: " + RayMath::ToString(camera.GetCamera().GetOrigin())
			+ "\nTarget: " + RayMath::ToString(camera.GetCamera().GetTarget()) + "\n";
		outStr += "Left-Bottom: " + RayMath::ToString(leftButtom) + "\n";
		outStr += "Horizontal: " + RayMath::ToString(horizontal) + "\n";
		outStr += "Vertical: " + RayMath::ToString(vertical) + "\n";
		outStr += "FoV: " + to_string(camera.GetCamera().GetFoV()) + "\n";
		outStr += "Aspect: " + to_string(camera.GetCamera().GetAspect());
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Another Window", &show_demo_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text(outStr.c_str());
		if (ImGui::Button("Close Me"))
			glfwSetWindowShouldClose(App.GetWindow(), true);
		ImGui::End();

		ImGui::Render();

		raytracing_processInput(App);

		App.Clear(0x123456);

		camera.Update(App);

		for (size_t i = 0; i < 4; i++)
			randSeed[i] = static_cast<float>(util::RayMath::Drand48());
		shader.Use();
		shader.SetVector2("_screen_size", appSize);
		shader.SetArray("_rdSeed", 4, randSeed);
		shader.SetVector3("ca_lookFrom", camera.GetCamera().GetOrigin());
		camera.GetCamera().GetLeftBottom(leftButtom, horizontal, vertical);
		shader.SetVector3("ca_left_buttom", leftButtom);
		shader.SetVector3("ca_horizontal", horizontal);
		shader.SetVector3("ca_vertical", vertical);

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
