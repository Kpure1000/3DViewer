#ifndef WINDOW_H
#define WINDOW_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"../util/RtxMath.h"
#include"../util/Color.h"
#include"../event/Mouse.h"
#include"../system/Time.h"

namespace rtx
{
	namespace render
	{
		class Window
		{
		public:

			enum class ClearMode
			{
				ColorMode = GL_COLOR_BUFFER_BIT,
				DepthMode = GL_DEPTH_BUFFER_BIT
			};

			Window() :m_window(nullptr), m_size({ 0.0f,0.0f }),
				m_title("Render Window"), isOpened(false)
			{}

			Window(glm::vec2 Size, std::string Title);

			~Window()
			{
				//glfwTerminate();
			}

			inline GLFWwindow* GetWindow()const { return m_window; }

			inline void Clear(util::Color color)
			{
				if (!isOpened)return;

				glClearColor(color[0], color[1], color[2], color[3]);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			}

			inline void Clear(util::Color color, Window::ClearMode clearBit)
			{
				if (!isOpened)return;

				glClearColor(color[0], color[1], color[2], color[3]);
				glClear((GLbitfield)clearBit);
			}

			void Display()
			{
				if (!isOpened)return;
				//  binary buffer swaping
				glfwSwapBuffers(m_window);
				event::Mouse::ResetMouseState();

				//  deal events
				glfwPollEvents();
				system::Time::FrameDisplay();
			}

			inline bool isOpen()
			{
				return isOpened = !glfwWindowShouldClose(m_window);
			}

			inline bool isOpen()const
			{
				return !glfwWindowShouldClose(m_window);
			}

			inline void Close()
			{
				glfwSetWindowShouldClose(m_window, true);
				isOpened = false;
			}

			inline void Close()const
			{
				glfwSetWindowShouldClose(m_window, true);
			}

			inline bool isFocus()const { return isFocused; }

			inline void SetCursorEnable(bool Enable)
			{
				if (!Enable)
					glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				else
					glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}

		private:

			GLFWwindow* m_window;

			glm::vec2 m_size;

			std::string m_title;

			bool isOpened;

			//  TODO: this cannot be static
			static bool isFocused;

		};
	}
}
#endif // !WINDOW_H
