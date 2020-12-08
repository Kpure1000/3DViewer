#include"event/Mouse.h"
#include"render/Window.h"

namespace rtx
{
	namespace event
	{
		glm::vec2 Mouse::m_position = glm::vec2(0.0f, 0.0f);
		bool Mouse::m_isMoved = false;

		glm::vec2 Mouse::m_scroll = glm::vec2(0.0f, 0.0f);
		bool Mouse::m_isScrolled = false;

		void Mouse::SetPosition(render::Window const& window, glm::vec2 const& pos)
		{
			glfwSetCursorPos(window.GetWindow(), (double)pos.x, (double)pos.y);
		}

		bool Mouse::isButtonPressed(rtx::render::Window const& window, Mouse::Button button)
		{
			return glfwGetMouseButton(window.GetWindow(), (int)button);
		}
	}
}