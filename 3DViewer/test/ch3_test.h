#ifndef CH3_TEST_H
#define CH3_TEST_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#pragma region Test Entrance

#define _CH3_TEST_1
#define _CH3_TEST_2

#ifdef _CH3_TEST_1
int ch3_depthTest_main();
#endif // _CH3_TEST_1

#ifdef _CH3_TEST_2
int ch3_frameBuffer_main();
#endif // _CH3_TEST_2

#pragma endregion

#endif // !CH3_TEST_H
