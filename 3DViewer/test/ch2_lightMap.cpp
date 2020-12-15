#include"ch2_test.h"

#include<iostream>

#include"../render/Render.h"
#include"../graph//Graph.h"
#include"../event/Event.h"
#include"../system/System.h"
#include"../util/Util.h"

using namespace rtx;
using namespace std;
using render::Window;
using graph::CubeMesh;
using graph::SphereMesh;

void test_ch2_4_processInput(render::Window window);

//int ch2_lightMap_main()
//{
//	int width = 800, height = 600;
//	Window App(glm::vec2(width, height), "LightMap", Window::ClearMode::DepthMode);
//
//	SphereMesh light;
//	/*light.GetTransform()
//		.SetPosition(glm::vec3(0.0f))
//		.SetRotation*/
//
//}

void test_ch2_4_processInput(render::Window window)
{
	//  press ESC to close window and exit
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.Close();


}