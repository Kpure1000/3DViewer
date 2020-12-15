#include"render/Transform.h"
#include"system/Time.h"
namespace rtx
{
	namespace render
	{
		glm::mat4 Transform::GetTransMat()
		{
			if (isUpdated)
			{
				m_trans = glm::mat4(1.0f);
				m_trans = glm::translate(m_trans, m_position);
				m_trans = glm::rotate(m_trans, (float)glm::radians(m_angle), m_rotation);
				m_trans = glm::scale(m_trans, m_scale);
				isUpdated = false;
			}
			return m_trans;
		}

		void Transform::Rotate(const glm::vec3& rotation, const float& angle)
		{
			isUpdated = true;
			m_rotation = rotation;
			m_angle += angle;
			
		}

		void Transform::RotateArround(const glm::vec3& target,
			const glm::vec3& up, const float& speed)
		{
			isUpdated = true;

			glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::translate(trans, target);
			trans = glm::rotate(trans, (float)glm::radians(speed) * system::Time::deltaTime(), up);
			trans = glm::translate(trans, m_position - target);
			trans = glm::scale(trans, m_scale);

			m_position = (glm::vec3)(trans * glm::vec4(glm::vec3(0.0f), 1.0f));
			m_rotation = up;
			m_angle += system::Time::deltaTime() * speed;


			
		}


	}
}
