#include"ch2_test.h"

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<thread>

#include"../render/Shader.h"
#include"../render/Image.h"
#include"../util/Color.h"
#include"../render/Texture.h"
#include"../render/FPSCamera.h"
#include"../system/Time.h"

#include"../render/Window.h"
#include"../event/Mouse.h"
#include"../graph/CubeMesh.h"

using namespace rtx;
using namespace std;
using render::Window;
using graph::CubeMesh;

int ch2_material_main()
{
	int width = 800, height = 600;

	Window App(glm::vec2(width, height), "ch2_color");

	CubeMesh cube();

}