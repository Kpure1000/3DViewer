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

void test_ch2_5_processInput(render::Window window);

int ch2_lightCaster_main()
{

	Window App(glm::vec2(800, 600), "Chapter2: Test 5: Light Caster", Window::ClearMode::DepthMode, false);

	glm::vec2 appSize = App.GetSize();

	//  light:
	glm::vec3 lightPosition(0.2f, 1.0f, 0.3f);
	Color lightColor(0xFFFF66);
	SphereMesh light;
	light.GetTransform().SetPosition(lightPosition);
	light.GetTransform().SetScale(glm::vec3(0.3f));
	Shader lightShader("../data/shader/ch2_lightCaster.vert", "../data/shader/ch2_lightCaster_light.frag");
	lightShader.Use();
	lightShader.SetRGB("_lightColor", lightColor);

	//  box:
	CubeMesh box;
	Texture diffuseTex;
	diffuseTex.LoadFromFile("../data/texture/container2.png");
	Texture specularTex;
	specularTex.LoadFromFile("../data/texture/container2_specular.png");
	Texture emissionTex;
	emissionTex.LoadFromFile("../data/texture/matrix.jpg");
	Shader boxShader("../data/shader/ch2_lightCaster.vert", "../data/shader/ch2_lightCaster.frag");
	boxShader.Use();
	diffuseTex.Bind(0); boxShader.SetSampler2D("_material.diffuse", 0);
	specularTex.Bind(1); boxShader.SetSampler2D("_material.specular", 1);
	emissionTex.Bind(2); boxShader.SetSampler2D("_material.emission", 2);
	boxShader.SetInt("_material.shininess", 32);
	//  _light:
	boxShader.SetVector4("_lightLocate", glm::vec4(lightPosition, 0.0f));
	boxShader.SetRGB("_light.ambient", util::Color(0x0f0f0f));
	boxShader.SetRGB("_light.diffuse", lightColor);
	boxShader.SetRGB("_light.specular", lightColor);

	FPSCamera camera(glm::vec3(0.0f, 0.0f, 3.0f), lightPosition,
		45.0f, appSize.x / appSize.y, 0.01f, 100.0f, 5.0f);

	App.DrawStart(Window::DrawMode::Fill);

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	while (App.isOpen())
	{
		test_ch2_5_processInput(App);

		App.Clear(util::Color(0x060a23ff));

		camera.Update(App);

		for (size_t i = 0; i < 10; i++)
		{
			box.GetTransform().SetPosition(cubePositions[i]);
			float angle = 20.0f * i;
			box.GetTransform().SetRotation(glm::vec3(1.0f, 0.3f, 0.5f), angle);
			boxShader.Use();
			boxShader.SetMatrix4("_view", camera.GetCamera().GetView());
			boxShader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
			boxShader.SetMatrix4("_model", box.GetTransform().GetTransMat());
			App.Draw(box);
		}

		lightShader.Use();
		lightShader.SetMatrix4("_view", camera.GetCamera().GetView());
		lightShader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
		lightShader.SetMatrix4("_model", light.GetTransform().GetTransMat());
		App.Draw(light);

		App.Display();

	}

	return 0;
}
void test_ch2_5_processInput(render::Window window)
{
	//  press ESC to close window and exit
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.Close();
}