#ifndef CH2_TEST_H
#define CH2_TEST_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#pragma region Test Entrance

#define _CH2_TEST_2 
#define _CH2_TEST_3 
#define _CH2_TEST_4 
#define _CH2_TEST_5

#ifdef _CH2_TEST_1
int ch2_color_main();
#endif // _CH2_TEST_1

#ifdef _CH2_TEST_2
int ch2_basiclight_main();
#endif // _CH2_TEST_2

#ifdef _CH2_TEST_3
int ch2_material_main();
#endif // _CH2_TEST_3

#ifdef _CH2_TEST_4
int ch2_lightMap_main();
#endif // _CH2_TEST_4

#ifdef _CH2_TEST_5
int ch2_lightCaster_main();
#endif // !_CH2_TEST_5


#pragma endregion


#endif // !CH2_TEST_H
