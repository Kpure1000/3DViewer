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

void test_4_processInput(GLFWwindow* window);

int ch1_axis_main() {

#pragma region some initializations

    glfwInit(); // 初始化glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#pragma endregion

#pragma region create window

    int width = 2560, height = 1440;

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

    //  mouse scroll event call back
    glfwSetScrollCallback(window, [](GLFWwindow* win, double offsetX, double offsetY)
        {
            // TODO
            
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

	int indices[] = {
		0,1,2, // front
		2,3,0,

        4,7,6,
        6,5,4,

        0,4,5,
        5,1,0,

        3,2,6,
        6,7,3,

        1,5,6,
        6,2,1,

        0,3,7,
        7,4,0
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

#pragma endregion

    render::Shader shader("../data/shader/ch1_axis.vert",
        "../data/shader/ch1_axis.frag");

    render::Texture t1, t2;
    t1.LoadFromFile("../data/texture/container.jpg");
    t2.LoadFromFile("../data/texture/awesomeface.png");

    shader.Use();
    shader.SetSampler2D("_texture1", 0);
    shader.SetSampler2D("_texture2", 1);

#pragma region render loop

    util::Color color;

    bool isImage1 = true;

    time_t startTime = clock();
    time_t curTime = startTime;
    int i = 0;

    //  注意,如果使用的是glm-0.9.9及以上版本,变换前矩阵需要初始化为单位矩阵
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    float FoV = 45.0f;

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(FoV), (float)width / height, 0.1f, 100.0f);
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
	//  if window has not been closed yet
	while (!glfwWindowShouldClose(window))
	{
		//  input dealing
		test_4_processInput(window);

		//  redner setting
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //  texture render update
        t1.Bind(0);
        t2.Bind(1);

        //  shader update
        shader.Use();

        shader.SetFloat("_rate", 0.5f + 0.5f * static_cast<float>(sin(6 * glfwGetTime())));
        FoV = 90.0f * (0.65f + 0.5f * static_cast<float>(sin(2 * glfwGetTime())));
        projection = glm::perspective(glm::radians(FoV), (float)width / height, 0.1f, 100.0f);
       
        shader.SetMatrix4("_model", model);
        shader.SetMatrix4("_view", view);
        shader.SetMatrix4("_projection", projection);

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
void test_4_processInput(GLFWwindow* window)
{
    //  press ESC to close window and exit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
