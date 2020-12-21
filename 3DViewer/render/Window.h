#ifndef WINDOW_H
#define WINDOW_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"../util/RtxMath.h"
#include"../util/Color.h"
#include"../event/Mouse.h"
#include"../system/Time.h"
#include"../graph/RenderTarget.h"

#include<memory>

using namespace rtx::util;
using rtx::event::Mouse;
using rtx::graph::RenderTarget;
using std::shared_ptr;

namespace rtx
{
	namespace render
	{
		class Window : public RenderTarget
		{
		public:

			/// <summary>
			/// Mode of clear
			/// </summary>
			enum class ClearMode
			{
				ColorMode = GL_COLOR_BUFFER_BIT,
				DepthMode = GL_DEPTH_BUFFER_BIT
			};

			/// <summary>
			/// Mode of draw vertices
			/// </summary>
			enum class DrawMode
			{
				Fill = GL_FILL,
				Line = GL_LINE,
				Point = GL_POINT
			};

			Window() :m_window(nullptr), m_size({ 0.0f,0.0f }),
				m_title("Render Window"), isOpened(false), m_clearBit(ClearMode::ColorMode),
				m_drawMode(DrawMode::Fill), m_pVideoMode()
			{}

			/// <summary>
			/// Construct a window
			/// </summary>
			/// <param name="Size">Window size</param>
			/// <param name="Title">Window title</param>
			/// <param name="ClearBit">Clear Mode</param>
			Window(glm::vec2 Size, std::string Title, Window::ClearMode ClearBit, bool isFullScreen);

			/// <summary>
			/// Get window handle
			/// </summary>
			/// <returns></returns>
			inline GLFWwindow* GetWindow()const { return m_window; }

			/// <summary>
			/// Start draw, MUST use this before render loop!!!
			/// </summary>
			/// <param name="drawMode">Mode of draw</param>
			void DrawStart(DrawMode drawMode);

			/// <summary>
			/// Set draw mode
			/// </summary>
			/// <param name="drawMode"></param>
			inline void SetDrawMode(const DrawMode& drawMode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, (unsigned int)(m_drawMode = drawMode));
			}

			/// <summary>
			/// Clear the canvas
			/// </summary>
			/// <param name="color"></param>
			void Clear(util::Color color);

			/// <summary>
			/// Display to the screen, MUST call in the end of frame
			/// </summary>
			void Display();

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

			/// <summary>
			/// Set if enable the cursor
			/// </summary>
			/// <param name="Enable"></param>
			void SetCursorEnable(bool Enable);

			inline glm::vec2 GetSize()const
			{
				int w, h;
				glfwGetWindowSize(m_window, &w, &h);
				//m_size.x = static_cast<float>(w), m_size.y = static_cast<float>(h);
				return glm::vec2(static_cast<float>(w), static_cast<float>(h));
			}

		private:

			GLFWwindow* m_window;

			ClearMode m_clearBit;

			DrawMode m_drawMode;

			/// <summary>
			/// Video mode of primary monitor
			/// </summary>
			GLFWvidmode m_pVideoMode;

			/// <summary>
			/// Array of monitors connected
			/// </summary>
			vector<GLFWmonitor*> m_monitors;

			glm::vec2 m_size;

			std::string m_title;

			bool isOpened;

			//  TODO: this cannot be static
			static bool isFocused;

		};
	}
}
#endif // !WINDOW_H
