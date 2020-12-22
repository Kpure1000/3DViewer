#include "ch3_test.h"

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

void test_ch3_1_processInput(const render::Window& window);

int ch3_depthTest_main()
{

	Window App(glm::vec2(800, 600), "Depth Test",
		Window::ClearMode::DepthMode, false);

	glm::vec2 appSize = App.GetSize();

	SphereMesh sphA;

	App.DrawStart(Window::DrawMode::Fill);

	Color clearColor(0x123456);

	while (App.isOpen())
	{
		test_ch3_1_processInput(App);

		App.Clear(clearColor);

		App.Draw(sphA);

		App.Display();
	}
	
	glfwTerminate();

	return 0;
}

void test_ch3_1_processInput(const render::Window& window)
{
	//  press ESC to close window and exit
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.Close();
}