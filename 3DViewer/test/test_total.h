#ifndef TEST_TOTAL_H
#define TEST_TOTAL_H

/*
* Chapter1
* 0. OpenGL
* 1. Window
* 2. VBO, VAO and EBO
* 3. Shader
* 4. Texture
* 5. Transform
*/

#define _CHAPTER_1 
#define _CHAPTER_2 

#ifdef _CHAPTER_1
#include"ch1_test.h"
#endif

#ifdef _CHAPTER_2
#include"ch2_test.h"
#endif // _CHAPTER

#include"raytracing.h"

#endif // !TEST_TOTAL_H
