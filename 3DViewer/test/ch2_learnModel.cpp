#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../render/Render.h"
#include"../util/Color.h"
#include"../graph/LearnMesh.h"
#include"../graph/LearnModel.h"
#include"../graph/Graph.h"
#include <iostream>

using namespace rtx::render;
using namespace rtx::graph;
using namespace rtx::util;

void test_ch2_7_processInput(Window window);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int ch2_learnModel_main()
{
	Window App(glm::vec2(800, 600), "Chapter2: Test 6: Model Loading", Window::ClearMode::DepthMode, false);

	glm::vec2 appSize = App.GetSize();

	FPSCamera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f),
		45.0f, appSize.x / appSize.y, 0.01f, 100.0f, 5.0f);

	Shader ourShader("../data/shader/ch2_model.vert", "../data/shader/ch2_model.frag");

	Model ourModel("../data/model/nanosuit/nanosuit.obj");
	ourModel.GetTransform().SetScale(glm::vec3(0.1f));
	ourModel.GetTransform().SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	App.DrawStart(Window::DrawMode::Fill);

	while (App.isOpen())
	{
		test_ch2_7_processInput(App);

		camera.Update(App);

		App.Clear(0x123456);

		ourShader.Use();
		ourShader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
		ourShader.SetMatrix4("_view", camera.GetCamera().GetView());

		ourShader.SetMatrix4("_model", ourModel.GetTransform().GetTransMat());
		//ourModel.Draw(ourShader);
		App.Draw(ourModel, ourShader);

		App.Display();

	}

	glfwTerminate();
	return 0;
}

void test_ch2_7_processInput(Window window)
{
	//  press ESC to close window and exit
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.Close();
}