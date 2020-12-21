#include"ch2_test.h"

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

void test_ch2_6_processInput(render::Window window);

int ch2_model_main()
{

	Window App(glm::vec2(800, 600), "Chapter2: Test 6: Model Loading",
		Window::ClearMode::DepthMode, false);

	glm::vec2 appSize = App.GetSize();

	//  light:
	glm::vec3 lightPosition(0.8f, 0.0f, 1.1f);
	Color lightColor(0xffffff);
	SphereMesh light;
	light.GetTransform().SetPosition(lightPosition);
	light.GetTransform().SetScale(glm::vec3(0.3f));
	Shader lightShader("../data/shader/ch2_model.vert", "../data/shader/ch2_model_light.frag");
	lightShader.Use();
	lightShader.SetRGB("_lightColor", lightColor);

	//  box:
	graph::Model nanosuit("../data/model/nanosuit/nanosuit.obj");
	nanosuit.GetTransform().SetScale(glm::vec3(0.1f));

	Shader modelShader("../data/shader/ch2_model.vert", "../data/shader/ch2_model.frag");
	modelShader.Use();
	
	modelShader.SetInt("_material.shininess", 32);
	//  _light:
	modelShader.SetVector4("_lightLocate", glm::vec4(lightPosition, 1.0f));
	modelShader.SetRGB("_light.ambient", util::Color(0x2f2f2f));
	modelShader.SetRGB("_light.diffuse", lightColor);
	modelShader.SetRGB("_light.specular", lightColor);

	FPSCamera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f),
		45.0f, appSize.x / appSize.y, 0.01f, 100.0f, 5.0f);

	App.DrawStart(Window::DrawMode::Fill);

	while (App.isOpen())
	{
		test_ch2_6_processInput(App);

		App.Clear(util::Color(0x123456));

		camera.Update(App);

		modelShader.Use();
		modelShader.SetMatrix4("_view", camera.GetCamera().GetView());
		modelShader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
		modelShader.SetMatrix4("_model", nanosuit.GetTransform().GetTransMat());
		App.Draw(nanosuit, modelShader);

		lightShader.Use();
		lightShader.SetMatrix4("_view", camera.GetCamera().GetView());
		lightShader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
		lightShader.SetMatrix4("_model", light.GetTransform().GetTransMat());
		App.Draw(light);

		App.Display();

	}

	return 0;
}
void test_ch2_6_processInput(render::Window window)
{
	//  press ESC to close window and exit
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.Close();
}