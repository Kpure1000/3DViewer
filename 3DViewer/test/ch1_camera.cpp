#include"ch1_test.h"

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

void test_5_processInput(GLFWwindow* window, render::Camera& camera);
void test_5_mouse_callback(GLFWwindow* window, double xpos, double ypos);

float mouseX, mouseY;
float pitch, yaw;
bool isMouseEntered = false;
bool isInputFirst = true;
glm::vec3 newMouseTarget;
bool isMoved = false;
float cameraFov;

int ch1_camera_main() {

#pragma region some initializations

	glfwInit(); // 初始化glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#pragma endregion

#pragma region create window

	int width = 800, height = 600;

	GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, width, height); // 设置视口大小

	 //  window resize call back
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

	glfwSetCursorPosCallback(window, test_5_mouse_callback);

	//  mouse scroll event call back
	glfwSetScrollCallback(window, [](GLFWwindow* win, double offsetX, double offsetY)->void
		{
			isMoved = true;
			if (cameraFov >= 20.0f && cameraFov <= 90.0f)
				cameraFov -= offsetY;
			if (cameraFov <= 20.0f)
				cameraFov = 20.0f;
			if (cameraFov >= 90.0f)
				cameraFov = 90.0f;
		});

#pragma endregion

#pragma region triangle initialization

	//  create triangle
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//  create vertices array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//  bind vao
	glBindVertexArray(VAO);

	//  cerate vertices buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//  bind vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//  copy vertices data to memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

#pragma endregion

#pragma region set vertex atrribution

	//  set the atrribution of vertices.position data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//  apply the atrribution set before
	glEnableVertexAttribArray(0);

	//  set the atrribution of vertices.color data
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//  apply the atrribution set before
	glEnableVertexAttribArray(1);

#pragma endregion

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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

#pragma endregion

	render::Shader shader("../data/shader/ch1_axis.vert",
		"../data/shader/ch1_axis.frag");

	render::Texture t1, t2;
	t1.LoadFromFile("../data/texture/container.jpg");
	t2.LoadFromFile("../data/texture/awesomeface.png");

	shader.Use();
	shader.SetSampler2D("_texture1", t1);
	shader.SetSampler2D("_texture2", t2);

	render::Camera camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), 45.0f, (float)width / height);

	pitch = asin(camera.GetDirection().y / camera.GetDirection().length());
	yaw = -acos(camera.GetDirection().z / camera.GetDirection().length() *
		camera.GetDirection().y / camera.GetDirection().length()) * 180 / Pi;

	cameraFov = camera.GetFoV();

#pragma region render loop

	util::Color color;
	float timeValue;

	bool isImage1 = true;

	time_t startTime = clock();
	time_t curTime = startTime;
	int i = 0;

	//  注意,如果使用的是glm-0.9.9及以上版本,变换前矩阵需要初始化为单位矩阵
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	system::Time::TimeStart();

	//  if window has not been closed yet
	while (!glfwWindowShouldClose(window))
	{
		system::Time::FrameStart();
		//  input dealing
		test_5_processInput(window, camera);

		//  redner setting
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//  texture render update
		t1.Use();
		t2.Use();

		//  shader update
		shader.Use();

		shader.SetFloat("_rate", 0.5f + 0.5f * sin(6 * glfwGetTime()));

		/*float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		camera.SetOrigin(glm::vec3(camX, 0.0, camZ));
		camera.SetFoV(45.0f);*/

		shader.SetMatrix4("_view", camera.GetView());
		shader.SetMatrix4("_projection", camera.GetProjection());

		//  bind vao
		glBindVertexArray(VAO);

		for (int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(90.0f) * 4,
				glm::vec3(0.5f, 1.0f, 0.0f));
			shader.SetMatrix4("_model", model);
			//  draw vertices from memory        
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//  binary buffer swaping
		glfwSwapBuffers(window);
		//  deal events
		glfwPollEvents();

		system::Time::FrameDisplay();
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
void test_5_processInput(GLFWwindow* window, render::Camera& camera)
{
	//  press ESC to close window and exit
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	glm::vec3 cameraOrigin = camera.GetOrigin();
	glm::vec3 cameraUp = camera.GetCameraUp();
	float cameraSpeed = system::Time::deltaTime() * 0.01f; // adjust accordingly
	if (isInputFirst)
	{
		newMouseTarget = -camera.GetDirection();
		isInputFirst = false;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraOrigin += cameraSpeed * newMouseTarget;
		isMoved = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraOrigin -= cameraSpeed * newMouseTarget;
		isMoved = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraOrigin -= glm::normalize(
			glm::cross(newMouseTarget, cameraUp)
		) * cameraSpeed;
		isMoved = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraOrigin += glm::normalize(
			glm::cross(newMouseTarget, cameraUp)
		) * cameraSpeed;
		isMoved = true;
	}
	if (isMoved)
	{
		camera.SetFoV(cameraFov);
		camera.SetOrigin(cameraOrigin);
		camera.SetTarget(cameraOrigin + newMouseTarget);
		camera.SetCameraUp(cameraUp);
		isMoved = false;
	}
}

void test_5_mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!isMouseEntered)
	{
		mouseX = xpos;
		mouseY = ypos;
		isMouseEntered = true;
	}
	float xoffset = xpos - mouseX;
	float yoffset = mouseY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	mouseX = xpos;
	mouseY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.9f)
		pitch = 89.9f;
	else if (pitch < -89.9f)
		pitch = -89.9f;

	newMouseTarget.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	newMouseTarget.y = sin(glm::radians(pitch));
	newMouseTarget.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	isMoved = true;
}
