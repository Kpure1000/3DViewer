#ifndef MOUSE_H
#define MOUSE_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"../util/RtxMath.h"


namespace rtx
{
	namespace render
	{
		class Window;
	}

	namespace event
	{

		class Mouse
		{
		public:

			enum class Button
			{
				Left,
				Right,
				Middle,
				XButton1,   // The first extra mouse button
				XButton2,   // The second extra mouse button

				ButtonCount // Keep last -- the total number of mouse buttons
			};

			enum class Wheel
			{
				VerticalWheel,
				HorizontalWheel
			};

			typedef struct MousePositionData
			{
				MousePositionData(glm::vec2 Position) :position(Position) {}
				glm::vec2 position;
			};

			typedef struct MouseScrollData
			{
				MouseScrollData(glm::vec2 Scroll) :scroll(Scroll) {}
				glm::vec2 scroll;
			};

			static glm::vec2 GetPosition(rtx::render::Window const& window)
			{
				return m_position;
			}

			static bool isMouseMoved()
			{
				return m_isMoved;
			}

			static glm::vec2 GetScrollOffset(rtx::render::Window const& window)
			{
				return m_scroll;
			}

			static bool isWheelScrolled()
			{
				return m_isScrolled;
			}

			static void SetPosition(rtx::render::Window const& window, glm::vec2 const& pos);

			static bool isButtonPressed(rtx::render::Window const& window, Mouse::Button button);

		private:

			static void ResetMouseState()
			{
				m_scroll = glm::vec2(0.0f);
				m_isMoved = false;
				m_isScrolled = false;
			}

			friend class render::Window;

			static glm::vec2 m_position;
			static bool m_isMoved;

			static glm::vec2 m_scroll;
			static bool m_isScrolled;
		};
	}
}
#endif // !MOUSE_H
