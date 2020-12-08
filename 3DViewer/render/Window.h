#ifndef WINDOW_H
#define WINDOW_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"../util/RtxMath.h"

#include"../event/Mouse.h"

namespace rtx
{
	namespace render
	{
		class Window
		{
		public:

			Window():m_window(nullptr) {}

			Window(glm::vec2 Size, std::string Title)
				: m_size(Size), m_title(Title), 
				m_window(glfwCreateWindow(Size.x, Size.y, Title.c_str(), NULL, NULL))
			{
				glfwInit(); // 初始化glfw
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

				glViewport(0, 0, Size.x, Size.y); // 设置视口大小

				//以下是回调的设置
				
				//glfwSetWindowUserPointer(m_window,&event::Mouse)

			}

		private:

			friend class event::Mouse;

			GLFWwindow* m_window;

			glm::vec2 m_size;

			std::string m_title;

			

		};
	}
}
#endif // !WINDOW_H
