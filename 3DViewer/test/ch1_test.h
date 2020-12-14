#ifndef CH1_TEST_H
#define CH1_TEST_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#pragma region Test Entrance

#define _CH1_TEST_0 1

#ifdef _CH1_TEST_1
/// <summary>
/// test1: glObject and Shader
/// </summary>
/// <returns>exit state</returns>
int ch1_shader_main();
#endif // _CH1_TEST_1

#ifdef _CH1_TEST_2
/// <summary>
/// test2: Texture
/// </summary>
/// <returns></returns>
int ch1_texture_main();
#endif // _CH1_TEST_2

#ifdef _CH1_TEST_3
/// <summary>
/// test3: Transform
/// </summary>
/// <returns></returns>
int ch1_transform_main();
#endif // _CH1_TEST_3

#ifdef _CH1_TEST_4
/// <summary>
/// test4: Axis
/// </summary>
/// <returns></returns>
int ch1_axis_main();
#endif // _CH1_TEST_4

#ifdef _CH1_TEST_5
/// <summary>
/// test5: Camera
/// </summary>
/// <returns></returns>
int ch1_camera_main();
#endif // _CH1_TEST_5

#pragma endregion

#endif // !CH1_TEST_H
