#include"render/Window.h"

#include<functional>

namespace rtx
{
	namespace render
	{

		bool Window::isFocused = false;

		Window::Window(glm::vec2 Size, std::string Title)
			: m_size(Size), m_title(Title)
		{
			glfwInit(); // 初始化glfw
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			m_window = glfwCreateWindow((int)Size.x, (int)Size.y, Title.c_str(), NULL, NULL);

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

			glViewport(0, 0, (int)Size.x, (int)Size.y); // 设置视口大小

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

	}
}