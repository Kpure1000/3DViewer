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
using graph::Sprite;

int ch3_frameBuffer_main()
{
	Window App(glm::vec2(800, 600), "Depth Test",
		Window::ClearMode::DepthMode, false);

	glm::vec2 appSize = App.GetSize();

	auto cb1 = CubeMesh();
	auto sp1 = Sprite();
	/*sp1.GetTransform().SetOrigin({ 0.5f, 0.5f, -1.0f });
	sp1.GetTransform().SetScale({ 2.0f,2.0f,2.0f });*/

	auto camera = FPSCamera(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f),
		45.0f, appSize.x / appSize.y, 0.01f, 100.0f, 5.0f);

	Texture wall;
	wall.LoadFromFile("../data/texture/brickwall.jpg");

	Shader shader("../data/shader/ch3_depth.vert", "../data/shader/ch3_depth.frag");
	Shader renderShader("../data/shader/ch3_frameBuffer.vert",
		"../data/shader/ch3_frameBuffer.frag");

	renderShader.Use();
	renderShader.SetMatrix4("_view", camera.GetCamera().GetView());
	renderShader.SetMatrix4("_projection", camera.GetCamera().GetProjection());
	renderShader.SetMatrix4("_model", sp1.GetTransform().GetTransMat());

	//  创建帧缓冲
	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	//  创建颜色附件纹理
	unsigned int texColorBf;
	glGenTextures(1, &texColorBf);
	glBindTexture(GL_TEXTURE_2D, texColorBf);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, appSize.x, appSize.y,
		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBf, 0);
	//  创建渲染缓冲对象(深度、模板缓冲)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, appSize.x, appSize.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cerr << "Framebuffer is not complete!\n";
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	App.DrawStart(Window::DrawMode::Fill);

	while (App.isOpen())
	{

		if (glfwGetKey(App.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			App.Close();

		App.pollEvents();

		camera.Update(App);
		{
			//  绑定帧缓冲
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glEnable(GL_DEPTH_TEST);
			App.Clear({ 0.2f,0.4f,0.6f,1.0f });

			shader.Use();
			shader.SetMatrix4("_view", camera.GetCamera().GetView());
			shader.SetMatrix4("_projection", camera.GetCamera().GetProjection());

			wall.Bind(1);
			shader.Use();
			shader.SetSampler2D("_tx", 1);

			cb1.GetTransform().SetPosition({ 0.0f, 0.0f, 0.0f });
			shader.SetMatrix4("_model", cb1.GetTransform().GetTransMat());
			App.Draw(cb1);
		}

		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			App.Clear({ 0.4f,0.6f,0.1f,1.0f });

			glBindTexture(GL_TEXTURE_2D, texColorBf);
			renderShader.Use();
			renderShader.SetSampler2D("_tx", 0);

			//renderShader.SetMatrix4("_model", sp1.GetTransform().GetTransMat());
			App.Draw(sp1);

			glEnable(GL_DEPTH_TEST);
			shader.Use();
			shader.SetMatrix4("_view", camera.GetCamera().GetView());
			shader.SetMatrix4("_projection", camera.GetCamera().GetProjection());

			wall.Bind(1);
			shader.Use();
			shader.SetSampler2D("_tx", 1);

			cb1.GetTransform().SetPosition({ 0.0f, 0.0f, 0.0f });
			shader.SetMatrix4("_model", cb1.GetTransform().GetTransMat());
			App.Draw(cb1);
		}

		App.Display();
	}

	return 0;
}