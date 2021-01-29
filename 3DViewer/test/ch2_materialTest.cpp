#include "ch2_test.h"

#include"../render/Render.h"
#include"../graph//Graph.h"
#include"../event/Event.h"
#include"../system/System.h"
#include"../util/Util.h"

#include "../imgui/imgui.h"
#include"../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include<array>
using std::array;

using namespace rtx;
using namespace std;
using render::Window;
using graph::CubeMesh;
using graph::SphereMesh;

int ch2_materialTest_main()
{
	Window App(glm::vec2(800, 600), "Chapter2: Test 9: Material Test",
		Window::ClearMode::DepthMode, true);

	glm::vec2 appSize = App.GetSize();

	Light light(make_shared<CubeMesh>(), Light::LightType::Point);
	light.SetColor(0xffffff);
	light.GetTransform().SetScale(glm::vec3(0.4f));
	light.SetPosition(glm::vec3(0.2f, 0.3f, 1.0f));

	Shader lightShader("../data/shader/ch2_lightCaster.vert",
		"../data/shader/ch2_lightCaster_light.frag");

	FPSCamera camera(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f),
		45.0f, appSize.x / appSize.y, 0.01f, 100.0f, 5.0f);

	CubeMesh box;
	Texture diffuseTex;
	diffuseTex.LoadFromFile("../data/texture/brickwall.jpg");
	Texture normalTex;
	normalTex.LoadFromFile("../data/texture/brickwall_normal.jpg");
	Texture specularTex;
	specularTex.LoadFromFile("../data/texture/brickwall_spec.png");
	specularTex.DealImage([](int w, int h, int ch, vector<unsigned char>& data)
		{
			Color cl;
			cl[2] = 0;
			for (size_t i = 0; i < w; i++)
			{
				for (size_t j = 0; j < h; j++)
				{
					data[j * w * ch + i * ch] *= 0.3f;
					data[j * w * ch + i * ch + 1] *= 0.3f;
					data[j * w * ch + i * ch + 2] *= 0.3f;
				}
			}
		});
	Texture emissionTex;
	emissionTex.LoadFromFile("../data/texture/matrix.jpg");
	Shader boxShader("../data/shader/ch2_multiLights.vert",
		"../data/shader/ch2_materialTest.frag");
	boxShader.Use();
	//  _light
	boxShader.SetVector3("_eyePos", camera.GetCamera().GetOrigin());
	boxShader.SetInt("_lightsNumber", 1);

	light.LightInShader(boxShader, 0);

	//  _material
	diffuseTex.Bind(0);
	boxShader.SetSampler2D("_material.diffuse", 0);
	normalTex.Bind(1);
	boxShader.SetSampler2D("_material.normal", 1);
	specularTex.Bind(2);
	boxShader.SetSampler2D("_material.specular", 2);
	emissionTex.Bind(3);
	boxShader.SetSampler2D("_material.emission", 3);
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

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(App.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsDark();
	bool show_demo_window = true;

	auto lightPos = light.GetPosition();

	App.DrawStart(Window::DrawMode::Fill);

	while (App.isOpen())
	{
		if (glfwGetKey(App.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			App.Close();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Propertis Window", &show_demo_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::SliderFloat3("Light Position", glm::value_ptr(lightPos), -5.0f, 5.0f, "%.3f", 1.0f);
		light.SetPosition(lightPos);
		ImGui::End();
		ImGui::Render();

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

		light.LightInShader(boxShader, 0);

		lightShader.Use();
		lightShader.SetRGB("_lightColor", light.GetColor());
		lightShader.SetMatrix4("_view", camera.GetCamera().GetView());
		lightShader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
		lightShader.SetMatrix4("_model", light.GetTransform().GetTransMat());
		App.Draw(light);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		App.Display();

	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	return 0;

}