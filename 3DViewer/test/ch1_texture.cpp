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

using namespace rtx;
using namespace std;

void test_2_processInput(GLFWwindow* window);

int ch1_texture_main() {

#pragma region some initializations

	glfwInit(); // 初始化glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#pragma endregion

#pragma region create window

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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

	glViewport(0, 0, 800, 600); // 设置视口大小

	 //  window resize call back
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

	//  mouse scroll event call back
	glfwSetScrollCallback(window, [](GLFWwindow* win, double offsetX, double offsetY)
		{
			// TODO
			//printf("Offset: (%lf, %lf)\n", offsetX, offsetY);
		});

#pragma endregion

#pragma region triangle initialization

    //  create triangle
    float vertices[] = {
        //  triangle down
        -1.0f,-1.0f,0.0f, //  left-bottom
        0.5f,0.5f,0.5f,
        0.0f,0.0f,

        -1.0f,1.0f,0.0f, //  left-top
        1.0f,0.0f,0.0f,
        0.0f,1.0f,

        1.0f,1.0f,0.0f, //  right-top
        0.0f,1.0f,0.0f,
        1.0f,1.0f,

        1.0f,-1.0f,0.0f, //  right-bottom
        0.0f,0.0f,1.0f,
        1.0f,0.0f
    };

    int indices[] = {
        0,1,2,
        2,3,0
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

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    //  bind ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //  copy element indices data to memory
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

#pragma endregion

#pragma region set vertex atrribution

    //  set the atrribution of vertices.position data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //  apply the atrribution set before
    glEnableVertexAttribArray(0);

    //  set the atrribution of vertices.color data
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //  apply the atrribution set before
    glEnableVertexAttribArray(1);

    //  set the atrribution of vertices.color data
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //  apply the atrribution set before
    glEnableVertexAttribArray(2);

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

#pragma endregion

    render::Shader shader("../data/shader/ch1_texture.vert",
        "../data/shader/ch1_texture.frag");

    render::Texture t1, t2;
    t1.LoadFromFile("../data/texture/container.jpg");
    t2.LoadFromFile("../data/texture/awesomeface.png");

    shader.Use();
    shader.SetSampler2D("_texture1", t1);
    shader.SetSampler2D("_texture2", t2);

#pragma region render loop

    util::Color color;

    bool isImage1 = true;

    time_t startTime = clock();
    time_t curTime = startTime;
    int i = 0;
    //  if window has not been closed yet
    while (!glfwWindowShouldClose(window))
    {
        //  input dealing
        test_2_processInput(window);

        //  redner setting
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //  texture render update
        t1.Use();
        t2.Use();

        //  shader update
        shader.Use();

        shader.SetFloat("_rate", 0.5f + 0.5f * static_cast<float>(sin(4*glfwGetTime())));

        //  bind vao
        glBindVertexArray(VAO);
        //  draw vertices from memory        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //  binary buffer swaping
        glfwSwapBuffers(window);
        //  deal events
        glfwPollEvents();
    }

#pragma endregion

#pragma region release all resouces of gl

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

#pragma endregion

    return 0;
}

/// <summary>
/// The input event
/// </summary>
/// <param name="window">Current window</param>
void test_2_processInput(GLFWwindow* window)
{
    //  press ESC to close window and exit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
