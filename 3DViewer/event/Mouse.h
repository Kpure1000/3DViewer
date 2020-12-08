#ifndef MOUSE_H
#define MOUSE_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"../util/RtxMath.h"

namespace rtx
{

	class render::Window;

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

			glm::vec2 GetPosition(render::Window window)const
			{
				return m_position;
			}

			glm::vec2 GetScrollOffset(render::Window window)const
			{
				return m_scroll;
			}
			
		private:

			friend class render::Window;

			static glm::vec2 m_position;

			static glm::vec2 m_scroll;

			static bool isMoving;

			static bool isEntered;


		};
	}
}
#endif // !MOUSE_H
