#include"ch2_test.h"

#include"../render/Render.h"
#include"../graph//Graph.h"
#include"../event/Event.h"
#include"../system/System.h"
#include"../util/Util.h"

#include "../imgui/imgui.h"
#include"../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

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

	FPSCamera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f),
		45.0f, appSize.x / appSize.y, 0.01f, 100.0f, 5.0f);

	//  light:
	glm::vec3 lightPosition(0.8f, 0.0f, 1.1f);
	Color lightColor(0xffffff);

	vector<Light>lights;
	for (int i = 0; i < 1; i++)
	{
		Light newLight(make_shared<CubeMesh>(), Light::LightType::Point);
		newLight.SetColor(lightColor);
		newLight.GetTransform().SetScale(glm::vec3(0.4f));
		/*newLight.SetPosition(glm::vec3(
			-1.0f + rand() % 1000 * 0.0025f,
			1.0f + rand() % 1000 * 0.0025f,
			1.5f + rand() % 1000 * 0.0005f)
		);*/
		newLight.SetPosition({ 0.0f, 4.27f, 1.15f });
		lights.push_back(newLight);
	}

	Shader lightShader("../data/shader/ch2_materialTest.vert", "../data/shader/ch2_model_light.frag");
	lightShader.Use();
	lightShader.SetRGB("_lightColor", lightColor);

	//unsigned char whiteData[4] = { 0x45,0x8d ,0xdf ,0x19 };
	//stbi_write_png("202.png", 1, 1, 4, whiteData, 0);

	//  box:
	graph::Model nanosuit("../data/model/mary/Marry.obj");
	nanosuit.GetTransform().SetScale(glm::vec3(1.2f));
	//nanosuit.GetTransform().SetRotation({ 1.0f,0.0f,0.0f }, -90.0f);

	Shader modelShader("../data/shader/ch2_materialTest.vert", "../data/shader/ch2_cartoon.frag");

	modelShader.Use();
	modelShader.SetInt("_material.shininess", 32);
	modelShader.SetVector3("_eyePos", camera.GetCamera().GetOrigin());
	modelShader.SetInt("_lightsNumber", lights.size());

	vector<glm::vec3>lightPos;
	for (int i = 0; i < lights.size(); i++) {
		lights[i].LightInShader(modelShader, i);
		lightPos.push_back(lights[i].GetPosition());
	}

	glm::vec4 DiffuseSegment(0.1f, 0.526f, 0.875f, 1.0f);
	float SpecularSegment = 0.7f;
	bool DrawLights = true;

	util::Color clearColor(0x8A898901);

	App.DrawStart(Window::DrawMode::Fill);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(App.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsDark();
	bool show_demo_window = true;

	glEnable(GL_BLEND);
	while (App.isOpen())
	{
		test_ch2_6_processInput(App);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Propertis Window", &show_demo_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		for (int i = 0; i < lightPos.size(); i++)
			ImGui::SliderFloat3(("Light Position" + std::string(std::to_string(i))).c_str(),
				glm::value_ptr(lightPos[i]), -5.0f, 5.0f, "%.3f", 1.0f);
		ImGui::ColorEdit4("Clear Color", glm::value_ptr(clearColor.RGBA()));
		ImGui::SliderFloat4("Diffuse Segment", glm::value_ptr(DiffuseSegment), 0.0f, 1.0f, "%.3f", 1.0f);
		ImGui::SliderFloat("Specular Segment", &SpecularSegment, 0.0f, 1.0f, "%.3f", 1.0f);
		ImGui::Checkbox("Draw Lights", &DrawLights);
		ImGui::End();
		ImGui::Render();

		for (int i = 0; i < lights.size(); i++)
			lights[i].SetPosition(lightPos[i]);

		App.pollEvents();

		App.Clear(clearColor);

		camera.Update(App);

		App.Draw(nanosuit, modelShader);

		for (int i = 0; i < lights.size(); i++)
		{
			modelShader.Use();
			modelShader.SetVector3("_eyePos", camera.GetCamera().GetOrigin());
			modelShader.SetVector4("_DiffuseSegment", DiffuseSegment);
			modelShader.SetFloat("_SpecularSegment", SpecularSegment);
			modelShader.SetMatrix4("_view", camera.GetCamera().GetView());
			modelShader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
			modelShader.SetMatrix4("_model", nanosuit.GetTransform().GetTransMat());
			lights[i].LightInShader(modelShader, i);
			
			if (DrawLights) {
				lightShader.Use();
				lightShader.SetRGB("_lightColor", lights[i].GetColor());
				lightShader.SetMatrix4("_view", camera.GetCamera().GetView());
				lightShader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
				lightShader.SetMatrix4("_model", lights[i].GetTransform().GetTransMat());
				App.Draw(lights[i]);
			}
		}


		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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