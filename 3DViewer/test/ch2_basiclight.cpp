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


using namespace rtx;
using namespace std;

void test_ch2_2_processInput(render::Window window);

float ambientStrength = 0.1f;
float specularStrength = 0.1f;
int gloss = 2;

int ch2_basiclight_main() {

#pragma region create window

	int width = 800, height = 600;

	render::Window App(glm::vec2(width, height), "ch2_color", render::Window::ClearMode::DepthMode,false);

#pragma endregion

	//  create 
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//  bind vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//  copy vertices data to memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//  create vertices array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//  bind vao
	glBindVertexArray(VAO);

	//  set the atrribution of vertices.position data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//  apply the atrribution set before
	glEnableVertexAttribArray(0);

	//  set the atrribution of vertices.color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//  apply the atrribution set before
	glEnableVertexAttribArray(1);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//  set the atrribution of vertices.color data
	//  set the atrribution of vertices.position data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//  apply the atrribution set before
	glEnableVertexAttribArray(0);

	//  set the atrribution of vertices.color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//  apply the atrribution set before
	glEnableVertexAttribArray(1);

#pragma region some setting or source releasing before render

	//  release bind of vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//  release bind of vao
	glBindVertexArray(0);
	//  release bind of ebo
	//  <ATTENTION!!!> DO NOT RELEASE EBO BEFORE VAO 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//  set draw mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //  draw fill face
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //  only draw line
	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); //  only draw vertices

	glEnable(GL_DEPTH_TEST);

#pragma endregion

	//  注意,如果使用的是glm-0.9.9及以上版本,变换前矩阵需要初始化为单位矩阵
	glm::mat4 model = glm::mat4(1.0f);

	glm::vec3 lightPosition(1.2f, 1.0f, 2.0f);

	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPosition);
	lightModel = glm::scale(lightModel, glm::vec3(0.3f));

	render::Shader shader("../data/shader/ch2_basiclight.vert",
		"../data/shader/ch2_basiclight.frag");

	render::Shader lightShader("../data/shader/ch2_basiclight.vert",
		"../data/shader/ch2_basiclight_light.frag");

	shader.Use();
	shader.SetRGB("objectColor", util::Color(1.0f, 0.5f, 0.2f));
	shader.SetRGB("lightColor", util::Color(1.0f, 1.0f, 1.0f));
	shader.SetVector3("lightPos", lightPosition);

	shader.SetFloat("_ambientStrength", ambientStrength);
	shader.SetFloat("_specularStrength", specularStrength);
	shader.SetInt("_gloss", gloss);

	lightShader.Use();

	render::FPSCamera fpsCamera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0),
		45.0f, (float)width / height, 0.01f, 100.0f, 8.0f);

#pragma region render loop

	//App.SetCursorEnable(false);

	//  if window has not been closed yet
	while (App.isOpen())
	{
		//  input dealing
		test_ch2_2_processInput(App);

		//  redner setting
		App.Clear(util::Color(0.1f, 0.2f, 0.3f, 1.0f));

		fpsCamera.Update(App);

#pragma region Draw

		//  shader update
		shader.Use();
		shader.SetFloat("_ambientStrength", ambientStrength);
		shader.SetFloat("_specularStrength", specularStrength);
		shader.SetInt("_gloss", gloss);

		shader.SetMatrix4("view", fpsCamera.GetCamera().GetView());
		shader.SetMatrix4("projection", fpsCamera.GetCamera().GetProjection());
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 0.0f,
			glm::vec3(0.5f, 1.0f, 0.0f));
		shader.SetMatrix4("model", model);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightShader.Use();
		lightShader.SetMatrix4("view", fpsCamera.GetCamera().GetView());
		lightShader.SetMatrix4("projection", fpsCamera.GetCamera().GetProjection());
		lightModel = glm::rotate(lightModel, (float)glm::radians(0.3f), glm::vec3(0.5f, 1.0f, 0.0f));
		lightShader.SetMatrix4("model", lightModel);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

#pragma endregion

		App.Display();

		printf("\rdeltaTime: %.3f        ", system::Time::deltaTime());

	}

#pragma endregion

#pragma region release all resouces of gl

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

#pragma endregion

	return 0;
}

/// <summary>
/// The input event
/// </summary>
/// <param name="window">Current window</param>
void test_ch2_2_processInput(render::Window window)
{
	//  press ESC to close window and exit
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.Close();
	
	if (event::Mouse::isWheelScrolled())
	{
		float yoffset = event::Mouse::GetScrollOffset(window).y * system::Time::deltaTime() * 30.0f;
		float isHit = false;
		if (glfwGetKey(window.GetWindow(), GLFW_KEY_1) == GLFW_PRESS)
		{
			isHit = true;
			if (yoffset < 0)
				ambientStrength = max(0.001f, ambientStrength * 0.8f);
			else if (yoffset > 0)
				ambientStrength = min(1.0f, ambientStrength / 0.8f);
		}
		if (glfwGetKey(window.GetWindow(), GLFW_KEY_2) == GLFW_PRESS)
		{
			isHit = true;
			if (yoffset < 0)
				specularStrength = max(0.001f, specularStrength * 0.8f);
			else if (yoffset > 0)
				specularStrength = min(1.0f, specularStrength / 0.8f);
		}
		if (glfwGetKey(window.GetWindow(), GLFW_KEY_3) == GLFW_PRESS)
		{
			isHit = true;
			if (yoffset < 0)
				gloss = max(2, gloss / 2);
			else if (yoffset > 0)
				gloss = min(256, gloss * 2);
		}
		/*if (isHit)
		{
			printf("\ram: %.3f, sp: %.3f, gl: %d        ", ambientStrength, specularStrength, gloss);
		}*/
	}

}
