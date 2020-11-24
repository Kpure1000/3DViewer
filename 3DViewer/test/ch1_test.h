#ifndef CH1_SHADER_TEST_H
#define CH1_SHADER_TEST_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include"../render/Shader.h"
#include"../util/Color.h"

using namespace rtx;
using namespace std;

/// <summary>
/// test1: Triangle and Shader
/// </summary>
/// <returns>exit state</returns>
int ch1_shader_main();

int ch1_texture_main();

/// <summary>
/// The callback after resized window
/// </summary>
/// <param name="window">Current window</param>
/// <param name="width">New width of window</param>
/// <param name="height">New height of window</param>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/// <summary>
/// The input event
/// </summary>
/// <param name="window">Current window</param>
void processInput(GLFWwindow* window);

#endif // !CH1_SHADER_TEST_H
