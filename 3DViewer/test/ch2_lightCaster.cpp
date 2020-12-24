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

void test_ch2_5_processInput(render::Window window);

int ch2_lightCaster_main()
{

	Window App(glm::vec2(800, 600), "Chapter2: Test 5: Light Caster",
		Window::ClearMode::DepthMode, false);

	glm::vec2 appSize = App.GetSize();

	//  light:
	Light light(make_shared<SphereMesh>(), glm::vec3(0.2f, 0.3f, 1.5f), 0xffffff);
	light.SetLightType(Light::LightType::Point);
	light.GetTransform().SetScale(glm::vec3(0.3f));
	Shader lightShader("../data/shader/ch2_lightCaster.vert", "../data/shader/ch2_lightCaster_light.frag");
	lightShader.Use();
	lightShader.SetRGB("_lightColor", light.GetColor());
	
	FPSCamera camera(glm::vec3(0.0f, 0.0f, 4.0f), light.GetTransform().GetPosition(),
		45.0f, appSize.x / appSize.y, 0.01f, 100.0f, 5.0f);

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
	//  _material
	diffuseTex.Bind(0); 
	boxShader.SetSampler2D("_material.diffuse", 0);
	specularTex.Bind(1); 
	boxShader.SetSampler2D("_material.specular", 1);
	emissionTex.Bind(2); 
	boxShader.SetSampler2D("_material.emission", 2);
	boxShader.SetInt("_material.shininess", 32);
	//  _light:
	boxShader.SetVector4("_light.position", light.GetLightLocation());
	boxShader.SetVector3("viewPos", camera.GetCamera().GetOrigin());
	boxShader.SetRGB("_light.ambient", util::Color(0x0f0f0f));
	boxShader.SetRGB("_light.diffuse", light.GetColor());
	boxShader.SetRGB("_light.specular", light.GetColor());
	boxShader.SetFloat("_light.constant", 1.0f);
	boxShader.SetFloat("_light.linear", 0.07f);
	boxShader.SetFloat("_light.quadratic", 0.017f);

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

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(App.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsDark();
	bool show_demo_window = true;

	App.DrawStart(Window::DrawMode::Fill);

	glm::vec3 lightPos = light.GetTransform().GetPosition();
	glm::vec3 lightScale = light.GetTransform().GetScale();
	int currentItem = 0;
	const char* itemStr = "Fill\0Line\0Point\0";
	while (App.isOpen())
	{
		test_ch2_5_processInput(App);
		std::string outStr = "";
		outStr = "Camera Information\nOrigin: " + RayMath::ToString(camera.GetCamera().GetOrigin())
			+ "\nTarget: " + RayMath::ToString(camera.GetCamera().GetTarget()) + "\n";	
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Propertis Window", &show_demo_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text(outStr.c_str());
		ImGui::SliderFloat3("Light Position", glm::value_ptr(lightPos), -5.0f, 5.0f, "%.3f", 1.0f);
		ImGui::SliderFloat3("Light Scale", glm::value_ptr(lightScale), -3.0f, 3.0f, "%.3f", 1.0f);
		if (ImGui::Combo("Draw Mode", &currentItem, itemStr))
		{
			switch (currentItem)
			{
			case 0:
				App.SetDrawMode(Window::DrawMode::Fill);
				break;
			case 1:
				App.SetDrawMode(Window::DrawMode::Line);
				break;
			case 2:
				App.SetDrawMode(Window::DrawMode::Point);
				break;
			default:
				break;
			}
		}
		if (ImGui::Button("Close Me"))
			glfwSetWindowShouldClose(App.GetWindow(), true);
		ImGui::End();
		ImGui::Render();
		App.Clear(util::Color(0x060a23ff));

		light.GetTransform().SetPosition(lightPos);
		light.GetTransform().SetScale(lightScale);

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
			boxShader.SetVector4("_light.position", light.GetLightLocation());
			boxShader.SetVector3("viewPos", camera.GetCamera().GetOrigin());
			App.Draw(box);
		}

		lightShader.Use();
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

void test_ch2_5_processInput(render::Window window)
{
	//  press ESC to close window and exit
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.Close();
}