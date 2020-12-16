#include"ch2_test.h"

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<thread>

#include"../util/Util.h"
#include"../render/Render.h"
#include"../graph/Graph.h"
#include"../event/Event.h"
#include"../system/System.h"

using namespace rtx;
using namespace std;
using render::Window;
using graph::CubeMesh;
using graph::SphereMesh;

void test_ch2_3_processInput(render::Window window);

int ch2_material_main()
{
	int width = 800, height = 600;

	render::Window App(glm::vec2(width, height), "ch2_color", Window::ClearMode::DepthMode);

	SphereMesh sphere;
	sphere.GetTransform().SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	sphere.GetTransform().SetRotation(glm::vec3(0.5f, 1.0f, 0.0f), 0.0f);
	sphere.GetTransform().SetScale(glm::vec3(1.0f));

	glm::vec3 lightPosition(5.0f, 0.0f, 5.0f);
	Color lightColor(0xFFFF66);

	SphereMesh lightSphere;
	lightSphere.GetTransform().SetPosition(lightPosition);
	lightSphere.GetTransform().SetScale(glm::vec3(2.0f));

	render::Shader shader("../data/shader/ch2_material.vert",
		"../data/shader/ch2_material.frag");

	render::Shader lightShader("../data/shader/ch2_material.vert",
		"../data/shader/ch2_material_light.frag");

	shader.Use();
	shader.SetRGB("_material.ambient", util::Color(0xffffff));
	shader.SetRGB("_material.diffuse", util::Color(0x349cff));
	shader.SetRGB("_material.specular", util::Color(0xffffff));
	shader.SetInt("_material.shininess", 32);

	shader.SetVector3("_lightPos", lightSphere.GetTransform().GetPosition());
	shader.SetRGB("_light.ambient", util::Color(0x0f0f0f));
	shader.SetRGB("_light.diffuse", lightColor);
	shader.SetRGB("_light.specular", lightColor);

	lightShader.Use();
	lightShader.SetRGB("_lightColor", lightColor);

	render::FPSCamera fpsCamera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0),
		45.0f, (float)width / height, 0.01f, 100.0f, 5.0f);

#pragma region render loop

	App.DrawStart(Window::DrawMode::Fill);

	float arround_angle_tmp = 0.0f;

	glm::vec3 up = glm::cross(glm::vec3(1.0f, 1.0f, 1.0f), lightSphere.GetTransform().GetPosition() - sphere.GetTransform().GetPosition());

	//  if window has not been closed yet
	while (App.isOpen())
	{
		//  input dealing
		test_ch2_3_processInput(App);

		//  redner setting
		App.Clear(util::Color(0x030303ff));

		fpsCamera.Update(App);

		lightSphere.GetTransform().Rotate(glm::vec3(0.5f, 1.0f, 0.0f),
			45.0f * system::Time::deltaTime());

		sphere.GetTransform().RotateArround(lightSphere.GetTransform().GetPosition(),
			up, 55.0f * system::Time::deltaTime());

#pragma region Draw

		//  shader update
		shader.Use();
		shader.SetMatrix4("_view", fpsCamera.GetCamera().GetView());
		shader.SetMatrix4("_projection", fpsCamera.GetCamera().GetProjection());
		shader.SetMatrix4("_model", sphere.GetTransform().GetTransMat());
		shader.SetVector3("_lightPos", lightSphere.GetTransform().GetPosition());
		App.Draw(sphere);

		lightShader.Use();
		lightShader.SetMatrix4("_view", fpsCamera.GetCamera().GetView());
		lightShader.SetMatrix4("_projection", fpsCamera.GetCamera().GetProjection());
		lightShader.SetMatrix4("_model", lightSphere.GetTransform().GetTransMat());
		App.Draw(lightSphere);

#pragma endregion

		App.Display();

		printf("\rdeltaTime: %.3f        ", system::Time::deltaTime());

	}

#pragma endregion

#pragma region release all resouces of gl

	glfwTerminate();

#pragma endregion

	return 0;

}

void test_ch2_3_processInput(render::Window window)
{
	//  press ESC to close window and exit
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.Close();
	

}