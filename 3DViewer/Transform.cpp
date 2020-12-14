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

		Transform& Transform::Rotate(const glm::vec3& rotation, const float& angle)
		{
			isUpdated = true;
			m_rotation = rotation;
			m_angle += angle;
			return *this;
		}

		Transform& Transform::RotateArround(const glm::vec3& target,
			const glm::vec3& up, float& angle, const float& speed)
		{
			//isUpdated = false;//  TODO 
			m_trans = glm::mat4(1.0);
			angle += system::Time::deltaTime() * speed;

			//glm::vec3 tmpPos= m_position;

			m_trans = glm::translate(m_trans, target);
			m_trans = glm::rotate(m_trans, (float)glm::radians(angle), up);
			//m_trans = glm::rotate(m_trans, (float)glm::radians(speed) * system::Time::deltaTime(), up);
			m_trans = glm::translate(m_trans, target - m_position);
			m_trans = glm::scale(m_trans, m_scale);

			//m_position = (glm::vec3)(m_trans * glm::vec4(target, 1.0f));

			//isUpdated = true;

			return *this;
		}


	}
}
