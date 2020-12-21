#ifndef TEST_TOTAL_H
#define TEST_TOTAL_H

#define _CHAPTER_1 
#define _CHAPTER_2
#define _CHAPTER_3

#ifdef _CHAPTER_1
#include"ch1_test.h"
#endif

#ifdef _CHAPTER_2
#include"ch2_test.h"
#endif // _CHAPTER

#ifdef _CHAPTER_3
#include"ch3_test.h"
#endif // _CHAPTER_3

#include"raytracing.h"

#endif // !TEST_TOTAL_H
