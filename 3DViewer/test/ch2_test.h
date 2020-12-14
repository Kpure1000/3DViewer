#ifndef CH2_TEST_H
#define CH2_TEST_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#pragma region Test Entrance

#define _CH2_TEST_3 

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

#endif // _CH2_TEST_4

#pragma endregion


#endif // !CH2_TEST_H
