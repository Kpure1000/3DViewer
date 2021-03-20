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

int ch3_depthTest_main()
{
	Window App(glm::vec2(800, 600), "Depth Test",
		Window::ClearMode::DepthMode, false);

	glm::vec2 appSize = App.GetSize();

	auto cb1 = CubeMesh();
	auto camera = FPSCamera(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f),
		45.0f, appSize.x / appSize.y, 0.01f, 100.0f, 5.0f);

	Texture ground;
	ground.LoadFromFile("../data/texture/raod1.jpg");

	Texture wall;
	wall.LoadFromFile("../data/texture/brickwall.jpg");

	Shader shader("../data/shader/ch3_depth.vert", "../data/shader/ch3_depth.frag");
	Shader coutourShader("../data/shader/ch3_depth.vert", "../data/shader/ch3_stencil_contour.frag");

	App.DrawStart(Window::DrawMode::Fill);

	Color clearColor(0x123456);

	glDepthFunc(GL_LESS);

	glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilOp(GL_ZERO, GL_KEEP, GL_KEEP);

	//  面剔除
	glEnable(GL_CULL_FACE);
	while (App.isOpen())
	{
		if (glfwGetKey(App.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			App.Close();

		App.pollEvents();

		camera.Update(App);

		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		App.Clear(clearColor);

		glfwSwapInterval(1);

		shader.Use();
		shader.SetMatrix4("_view", camera.GetCamera().GetView());
		shader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
		coutourShader.Use();
		coutourShader.SetMatrix4("_view", camera.GetCamera().GetView());
		coutourShader.SetMatrix4("_projection", camera.GetCamera().GetProjection());

		{
			glStencilFunc(GL_ALWAYS, 1, 0xFF); // 所有的片段都应该更新模板缓冲
			glStencilMask(0xFF); // 启用模板缓冲写入
			cb1.GetTransform().SetScale({ 1.0f,1.0f,1.0f });
			
			wall.Bind(1);
			shader.Use();
			shader.SetSampler2D("_tx", 1);

			cb1.GetTransform().SetPosition({ 0.0f, 0.0f, 0.0f });
			shader.SetMatrix4("_model", cb1.GetTransform().GetTransMat());
			App.Draw(cb1);

			cb1.GetTransform().SetPosition({ -1.4f, 0.0f, -0.4f });
			shader.SetMatrix4("_model", cb1.GetTransform().GetTransMat());
			App.Draw(cb1);
			
			cb1.GetTransform().SetPosition({ 1.6f, 0.0f, 1.3f });
			shader.SetMatrix4("_model", cb1.GetTransform().GetTransMat());
			App.Draw(cb1);
		}
		{
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00); // 禁止模板缓冲的写入
			//glDisable(GL_DEPTH_TEST);
			cb1.GetTransform().SetScale({ 1.05f,1.05f,1.05f });
			
			coutourShader.Use();
			
			cb1.GetTransform().SetPosition({ 0.0f, 0.0f, 0.0f });
			coutourShader.SetMatrix4("_model", cb1.GetTransform().GetTransMat());
			App.Draw(cb1);

			cb1.GetTransform().SetPosition({ -1.4f, 0.0f, -0.4f });
			coutourShader.SetMatrix4("_model", cb1.GetTransform().GetTransMat());
			App.Draw(cb1);

			cb1.GetTransform().SetPosition({ 1.6f, 0.0f, 1.3f });
			coutourShader.SetMatrix4("_model", cb1.GetTransform().GetTransMat());
			App.Draw(cb1);
		}
		{
			glStencilFunc(GL_ALWAYS, 1, 0xFF); // 所有的片段都应该更新模板缓冲
			glStencilMask(0xFF);
			cb1.GetTransform().SetScale({ 6.0f,6.0f,6.0f });

			shader.Use();
			ground.Bind(0);
			shader.SetSampler2D("_tx", 0);

			cb1.GetTransform().SetPosition({ 0.0f, -3.5f, 0.0f });
			shader.SetMatrix4("_model", cb1.GetTransform().GetTransMat());
			App.Draw(cb1);
			
		}
		App.Display();
	}

	glfwTerminate();

	return 0;
}
