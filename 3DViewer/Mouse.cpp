#include"event/Mouse.h"

namespace rtx
{
	namespace event
	{
		glm::vec2 Mouse::m_position = glm::vec2(0.0f, 0.0f);

		glm::vec2 Mouse::m_scroll = glm::vec2(0.0f, 0.0f);

		bool Mouse::isMoving = false;

		bool Mouse::isEntered = false;

	}
}