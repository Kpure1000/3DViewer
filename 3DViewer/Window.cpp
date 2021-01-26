#include"render/Window.h"

#include<functional>

namespace rtx
{
	namespace render
	{
		bool Window::isInitialized = false;

		bool Window::isFocused = false;

		Window::Window(glm::vec2 Size, std::string Title, Window::ClearMode ClearBit, bool isFullScreen)
			: m_size(Size), m_title(Title), m_clearBit(ClearBit),
			m_drawMode(DrawMode::Fill), m_pVideoMode()
		{
			glfwInit(); // init glfw
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			int monitorCount;
			auto monitor = glfwGetMonitors(&monitorCount);
			if (monitorCount > 0)
			{
				m_pVideoMode = *glfwGetVideoMode(monitor[0]);
				m_monitors.reserve(monitorCount);
				m_monitors.assign(monitor, monitor + monitorCount);
			}

			if (isFullScreen)
			{
				m_size.x = (float)m_pVideoMode.width;
				m_size.y = (float)m_pVideoMode.height;
				//  Use the size of primary monitor
				m_window = glfwCreateWindow(m_pVideoMode.width, m_pVideoMode.height, Title.c_str(),
					m_monitors[0], NULL);
			}
			else
			{
				m_window = glfwCreateWindow((int)m_size.x, (int)m_size.y, Title.c_str(), NULL, NULL);
			}

			if (m_window == NULL)
			{
				std::cerr << "Failed to create GLFW window" << std::endl;
				glfwTerminate();
			}
			glfwMakeContextCurrent(m_window);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cerr << "Failed to initialize GLAD" << std::endl;
			}

			glViewport(0, 0, (int)m_size.x, (int)m_size.y);

			// CallBack Setting:

			glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
				{
					glViewport(0, 0, width, height);
				});


			glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y)
				{
					event::Mouse::m_isMoved = true;
					event::Mouse::m_position.x = (float)x;
					event::Mouse::m_position.y = (float)y;
				});

			glfwSetScrollCallback(m_window, [](GLFWwindow* window, double x, double y)
				{
					event::Mouse::m_isScrolled = true;
					event::Mouse::m_scroll.x = (float)x;
					event::Mouse::m_scroll.y = (float)y;
				});

			glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focus)
				{
					focus == 1 ? isFocused = true : isFocused = false;
				});

			isOpened = true;

			system::Time::TimeStart();

		}

		void Window::DrawStart(DrawMode drawMode)
		{
			//  release bind of vbo
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			//  release bind of vao
			glBindVertexArray(0);
			//  release bind of ebo
			//  <ATTENTION!!!> DO NOT RELEASE EBO BEFORE VAO 
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			//  set draw mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //  draw fill face
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //  only draw line
			//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); //  only draw vertices
			if (m_clearBit == ClearMode::DepthMode)
			{
				glEnable(GL_DEPTH_TEST);
			}
			m_drawMode = drawMode;
			//  set draw mode
			glPolygonMode(GL_FRONT_AND_BACK, (unsigned int)m_drawMode);
		}

		void Window::Clear(util::Color&& color)
		{
			if (!isOpened)return;			
			glClearColor(color[0], color[1], color[2], color[3]);
			if (m_clearBit == ClearMode::ColorMode)
			{
				glClear(GL_COLOR_BUFFER_BIT);
			}
			else if (m_clearBit == ClearMode::DepthMode)
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
		}

		void Window::Clear(const util::Color& color)
		{
			if (!isOpened)return;
			glClearColor(color[0], color[1], color[2], color[3]);
			if (m_clearBit == ClearMode::ColorMode)
			{
				glClear(GL_COLOR_BUFFER_BIT);
			}
			else if (m_clearBit == ClearMode::DepthMode)
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
		}

		void Window::Display()
		{
			if (!isOpened)return;
			//  binary buffer swaping
			glfwSwapBuffers(m_window);
			event::Mouse::ResetMouseState();
			system::Time::FrameDisplay();
		}

		void Window::SetCursorEnable(bool Enable)
		{
			if (!Enable)
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

	}
}