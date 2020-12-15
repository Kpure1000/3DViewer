#include"ch2_test.h"

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<thread>

#include"../render/Shader.h"
#include"../render/Image.h"
#include"../util/Color.h"
#include"../render/Texture.h"
#include"../render/FPSCamera.h"
#include"../system/Time.h"

#include"../render/Window.h"
#include"../event/Mouse.h"
#include"../graph/CubeMesh.h"
#include"../graph/SphereMesh.h"

using namespace rtx;
using namespace std;
using render::Window;
using graph::CubeMesh;
using graph::SphereMesh;

void test_ch2_3_processInput(render::Window window);

int ch2_material_main()
{

#pragma region create window

	int width = 800, height = 600;

	render::Window App(glm::vec2(width, height), "ch2_color", Window::ClearMode::DepthMode);

#pragma endregion

	SphereMesh sphere;
	sphere.GetTransform().SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	sphere.GetTransform().SetRotation(glm::vec3(0.5f, 1.0f, 0.0f), 0.0f);
	sphere.GetTransform().SetScale(glm::vec3(1.0f));

	glm::vec3 lightPosition(5.0f, 0.0f, 5.0f);

	SphereMesh lightSphere;
	lightSphere.GetTransform().SetPosition(lightPosition);
	lightSphere.GetTransform().SetScale(glm::vec3(2.0f));

	render::Shader shader("../data/shader/ch2_material.vert",
		"../data/shader/ch2_material.frag");

	render::Shader lightShader("../data/shader/ch2_material.vert",
		"../data/shader/ch2_material_light.frag");

	shader.Use();
	shader.SetRGB("objectColor", util::Color(1.0f, 0.5f, 0.2f));
	shader.SetRGB("lightColor", util::Color(1.0f, 1.0f, 1.0f));
	shader.SetVector3("lightPos", lightPosition);
	shader.SetVector3("_material.ambient", util::Color(0xffffff).RGB());
	shader.SetVector3("_material.diffuse", util::Color(0x349cff).RGB());
	shader.SetVector3("_material.specular", util::Color(0xffffff).RGB());
	shader.SetInt("_material.shininess", 32);

	//shader.SetVector3("_light.position", lightPosition);
	shader.SetVector3("lightPos", lightSphere.GetTransform().GetPosition());
	shader.SetVector3("_light.ambient", util::Color(0x0f0f0f).RGB());
	shader.SetVector3("_light.diffuse", util::Color(0x444444).RGB());
	shader.SetVector3("_light.specular", util::Color(0x777474).RGB());

	lightShader.Use();
	lightShader.SetRGB("_LightColor", util::Color(0xFFFF66));

	render::FPSCamera fpsCamera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0),
		45.0f, (float)width / height, 0.01f, 100.0f, 5.0f);

#pragma region render loop

	App.DrawReady();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //  only draw line

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
			up, 55.0f);

#pragma region Draw

		//  shader update
		shader.Use();
		shader.SetMatrix4("view", fpsCamera.GetCamera().GetView());
		shader.SetMatrix4("projection", fpsCamera.GetCamera().GetProjection());
		shader.SetMatrix4("model", sphere.GetTransform().GetTransMat());
		shader.SetVector3("lightPos", lightSphere.GetTransform().GetPosition());
		App.Draw(sphere);

		lightShader.Use();
		lightShader.SetMatrix4("view", fpsCamera.GetCamera().GetView());
		lightShader.SetMatrix4("projection", fpsCamera.GetCamera().GetProjection());
		lightShader.SetMatrix4("model", lightSphere.GetTransform().GetTransMat());
		App.Draw(lightSphere);

#pragma endregion

		App.Display();

		printf("\rdeltaTime: %.3f        ", system::Time::deltaTime());

	}

#pragma endregion

#pragma region release all resouces of gl

	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);*/
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