#include"ch2_test.h"

#include"../render/Render.h"
#include"../graph//Graph.h"
#include"../event/Event.h"
#include"../system/System.h"
#include"../util/Util.h"

#include<array>
using std::array;

using namespace rtx;
using namespace std;
using render::Window;
using graph::CubeMesh;
using graph::SphereMesh;

void lightInit(Light* lights, int size);

int ch2_multiLights_main()
{
	Window App(glm::vec2(800, 600), "Chapter2: Test 8: Multiple Lights",
		Window::ClearMode::DepthMode, true);

	glm::vec2 appSize = App.GetSize();
	array<Light, 5> lights;
	lightInit(lights.data(), lights.size());

	Shader lightShader("../data/shader/ch2_lightCaster.vert",
		"../data/shader/ch2_lightCaster_light.frag");
	
	FPSCamera camera(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f),
		45.0f, appSize.x / appSize.y, 0.01f, 100.0f, 5.0f);

	CubeMesh box;
	Texture diffuseTex;
	diffuseTex.LoadFromFile("../data/texture/container2.png");
	Texture specularTex;
	specularTex.LoadFromFile("../data/texture/container2_specular.png");
	Texture emissionTex;
	emissionTex.LoadFromFile("../data/texture/matrix.jpg");
	Shader boxShader("../data/shader/ch2_multiLights.vert", 
		"../data/shader/ch2_multiLights.frag");
	boxShader.Use();
	//  _light
	boxShader.SetVector3("_eyePos", camera.GetCamera().GetOrigin());
	boxShader.SetInt("_lightsNumber", lights.size());
	for (int i = 0; i <lights.size(); i++)
	{
		lights[i].LightInShader(boxShader, i);
	}
	//  _material
	diffuseTex.Bind(0);
	boxShader.SetSampler2D("_material.diffuse", 0);
	specularTex.Bind(1);
	boxShader.SetSampler2D("_material.specular", 1);
	emissionTex.Bind(2);
	boxShader.SetSampler2D("_material.emission", 2);
	boxShader.SetInt("_material.shininess", 32);

	array<glm::vec3, 10> cubePositions = {
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

	App.DrawStart(Window::DrawMode::Fill);

	while (App.isOpen())
	{
		if (glfwGetKey(App.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			App.Close();
		App.pollEvents();

		camera.Update(App);

		App.Clear(0x060a23);


		for (size_t i = 0; i < cubePositions.size(); i++)
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

		for (size_t i = 0; i < lights.size(); i++)
		{
			lights[i].LightInShader(boxShader, i);

			lightShader.Use();
			lightShader.SetRGB("_lightColor", lights[i].GetColor());
			lightShader.SetMatrix4("_view", camera.GetCamera().GetView());
			lightShader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
			lightShader.SetMatrix4("_model", lights[i].GetTransform().GetTransMat());
			App.Draw(lights[i]);
		}

		App.Display();

	}

}

void lightInit(Light* lights, int size)
{
	glm::vec3 spot_direction(-1.0f, 0.0f, 0.5f);
	float cutOff = 12.5f;
	float outerCutOff = 17.5;

	lights[0] = Light(make_shared<CubeMesh>(), Light::LightType::Directional);
	lights[0].SetColor(0x4aee9d);
	lights[0].GetTransform().SetScale(glm::vec3(0.4f));
	lights[0].SetPosition(glm::vec3(0.7f, 0.2f, 2.0f));

	lights[1] = Light(make_shared<CubeMesh>(), Light::LightType::Point);
	lights[1].SetColor(0xde4e9a);
	lights[1].GetTransform().SetScale(glm::vec3(0.4f));
	lights[1].SetPosition(glm::vec3(2.3f, -3.3f, -4.0f));

	lights[2] = Light(make_shared<CubeMesh>(), Light::LightType::Point);
	lights[2].SetColor(0x9deae4);
	lights[2].GetTransform().SetScale(glm::vec3(0.4f));
	lights[2].SetPosition(glm::vec3(-4.0f, 2.0f, -12.0f));

	lights[3] = Light(make_shared<CubeMesh>(), Light::LightType::Spot);
	lights[3].SetColor(0xa9e4de);
	lights[3].GetTransform().SetScale(glm::vec3(0.4f));
	lights[3].SetPosition(glm::vec3(0.0f, 0.0f, -3.0f));
	lights[3].SetInnerCutOff(cutOff);
	lights[3].SetOuterCutOff(outerCutOff);
	lights[3].SetSpotDirection(spot_direction);

	lights[4] = Light(make_shared<CubeMesh>(), Light::LightType::Point);
	lights[4].SetColor(0xdae4e9);
	lights[4].GetTransform().SetScale(glm::vec3(0.4f));
	lights[4].SetPosition(glm::vec3(-4.2f, -3.1f, 5.3f));
}
