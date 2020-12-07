#ifndef CH1_TEST_H
#define CH1_TEST_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#pragma region Test Entrance

/// <summary>
/// test1: glObject and Shader
/// </summary>
/// <returns>exit state</returns>
int ch1_shader_main();

/// <summary>
/// test2: Texture
/// </summary>
/// <returns></returns>
int ch1_texture_main();

/// <summary>
/// test3: Transform
/// </summary>
/// <returns></returns>
int ch1_transform_main();

/// <summary>
/// test4: Axis
/// </summary>
/// <returns></returns>
int ch1_axis_main();

/// <summary>
/// test5: Camera
/// </summary>
/// <returns></returns>
int ch1_camera_main();
#pragma endregion

#endif // !CH1_TEST_H
