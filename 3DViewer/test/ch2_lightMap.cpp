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

int ch2_lightMap_main()
{
	
	int width = 800, height = 600;
	Window App(glm::vec2(width, height), "LightMap", Window::ClearMode::DepthMode, true);
	width = (int)App.GetSize().x;
	height = (int)App.GetSize().y;

	glm::vec3 lightPosition(2.0f, 0.0f, 2.0f);
	Color lightColor(0xFFFF66);

	SphereMesh light;
	light.GetTransform().SetPosition(lightPosition);
	light.GetTransform().SetScale(glm::vec3(0.3f));

	CubeMesh box;
	box.GetTransform().SetPosition(glm::vec3(0.0f));

	render::Shader lightShader("../data/shader/ch2_lightMap.vert",
		"../data/shader/ch2_lightMap_light.frag");

	render::Shader objShader("../data/shader/ch2_lightMap.vert",
		"../data/shader/ch2_lightMap.frag");

	Texture diffuseTex;
	diffuseTex.LoadFromFile("../data/texture/container2.png");

	Image specularImage;
	specularImage.LoadFromFile("../data/texture/container2_specular.png");
	//  Add colorful info to original specular image
	specularImage.DealImage([](int w, int h, int ch, vector<unsigned char>& data)
		{
			Color cl;
			cl[2] = 0;
			for (size_t i = 0; i < w; i++)
			{
				for (size_t j = 0; j < h; j++)
				{
					cl[0] = 255 * (1 - (float)i / w);
					cl[1] = 255 * ((float)j / h);
					data[j * w * ch + i * ch] = data[j * w * ch + i * ch] > 10 ?
						static_cast<int>((cl[0] + data[j * w * ch + i * ch]) / 2) : 0;
					data[j * w * ch + i * ch + 1] = data[j * w * ch + i * ch + 1] > 10 ?
						static_cast<int>((cl[1] + data[j * w * ch + i * ch + 1]) / 2) : 0;
					data[j * w * ch + i * ch + 2] = static_cast<int>(cl[2]);
				}
			}
		});
	specularImage.SaveData("../data/texture/specularImage.png");

	Texture specularTex;
	specularTex.LoadFromImage(specularImage);

	Texture emissionTex;
	emissionTex.LoadFromFile("../data/texture/matrix.jpg");

	objShader.Use();
	//  _material:
	diffuseTex.Bind();
	objShader.SetSampler2D("_material.diffuse", diffuseTex);
	specularTex.Bind();
	objShader.SetSampler2D("_material.specular", specularTex);
	emissionTex.Bind();
	objShader.SetSampler2D("_material.emission", emissionTex);

	objShader.SetInt("_material.shininess", 32);
	//  _light:
	objShader.SetVector3("_lightPos", light.GetTransform().GetPosition());
	objShader.SetRGB("_light.ambient", util::Color(0x0f0f0f));
	objShader.SetRGB("_light.diffuse", lightColor);
	objShader.SetRGB("_light.specular", lightColor);

	lightShader.Use();
	lightShader.SetRGB("_lightColor", lightColor);

	render::FPSCamera fpsCamera(glm::vec3(0, -0.1f, 3.0f), glm::vec3(1.2f, 0.1f, 1.2f),
		45.0f, (float)width / height, 0.01f, 100.0f, 5.0f);

	App.DrawStart(Window::DrawMode::Fill);

	while (App.isOpen())
	{
		test_ch2_4_processInput(App);

		App.Clear(util::Color(0x112234ff));

		fpsCamera.Update(App);

		/*light.GetTransform().RotateArround(box.GetTransform().GetPosition(),
			glm::vec3(0.0f, 1.0f, 0.0f), 50.0f * system::Time::deltaTime());*/

		objShader.Use();
		objShader.SetMatrix4("_view", fpsCamera.GetCamera().GetView());
		objShader.SetMatrix4("_projection", fpsCamera.GetCamera().GetProjection());
		objShader.SetMatrix4("_model", box.GetTransform().GetTransMat());
		objShader.SetVector3("_lightPos", light.GetTransform().GetPosition());
		App.Draw(box);

		lightShader.Use();
		lightShader.SetMatrix4("_view", fpsCamera.GetCamera().GetView());
		lightShader.SetMatrix4("_projection", fpsCamera.GetCamera().GetProjection());
		lightShader.SetMatrix4("_model", light.GetTransform().GetTransMat());
		App.Draw(light);

		App.Display();

	}

	glfwTerminate();

	return 0;
}

void test_ch2_4_processInput(render::Window window)
{
	//  press ESC to close window and exit
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.Close();


}