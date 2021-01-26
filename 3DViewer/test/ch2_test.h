#ifndef CH2_TEST_H
#define CH2_TEST_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#pragma region Test Entrance

#define _CH2_TEST_5

#define _CH2_TEST_8

#ifdef _CH2_TEST_1
/// <summary>
/// Light: color
/// </summary>
/// <returns></returns>
int ch2_color_main();
#endif // _CH2_TEST_1

#ifdef _CH2_TEST_2
/// <summary>
/// Basic light
/// </summary>
/// <returns></returns>
int ch2_basiclight_main();
#endif // _CH2_TEST_2

#ifdef _CH2_TEST_3
/// <summary>
/// The material(not exist the class Material)
/// </summary>
/// <returns></returns>
int ch2_material_main();
#endif // _CH2_TEST_3

#ifdef _CH2_TEST_4
/// <summary>
/// The light mapping
/// </summary>
/// <returns></returns>
int ch2_lightMap_main();
#endif // _CH2_TEST_4

#ifdef _CH2_TEST_5
/// <summary>
/// The light caster
/// </summary>
/// <returns></returns>
int ch2_lightCaster_main();
#endif // !_CH2_TEST_5

#ifdef _CH2_TEST_6
/// <summary>
/// The model loading. 
/// This should have been set in ch3_model but ch3_model is too short 
/// to be a single chapter. So it's here!
/// </summary>
/// <returns></returns>
int ch2_model_main();
#endif // _CH2_TEST_6

#ifdef _CH2_TEST_7
/// <summary>
/// The test from learnOpengl
/// </summary>
/// <returns></returns>
int ch2_learnModel_main();
#endif

#ifdef _CH2_TEST_8
/// <summary>
/// The multiple lights test
/// </summary>
/// <returns></returns>
int ch2_multiLights_main();
#endif // _CH2_TEST_8

#pragma endregion


#endif // !CH2_TEST_H
