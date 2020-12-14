#ifndef TRANSFORM_H
#define TRANSFORM_H

#include"../util/RtxMath.h"

namespace rtx
{

	using namespace util;

	namespace render
	{
		class Transform
		{
		public:

			Transform(glm::mat4& ModelMatrix)
				: m_position(glm::vec3(0.0f)), m_rotation(glm::vec3(0.0f)), m_scale(glm::vec3(1.0f)),
				m_trans(glm::mat4(1.0f))
			{}

			inline glm::vec3 GetPosition()
			{
				return m_position;
			}

			inline glm::vec3 GetRotateion()
			{
				return m_rotation;
			}

			inline glm::vec3 GetScale()
			{
				return m_scale;
			}

			inline void SetPosition(const glm::vec3& position)
			{
				m_position = position;
				//  TODO 矩阵计算
			}

			inline void SetRotateion(const glm::vec3& rotation)
			{
				m_rotation = rotation;
				//  TODO 矩阵计算
			}

			inline void SetSclae(const glm::vec3& scale)
			{
				m_scale = scale;
				//  TODO 矩阵计算
			}

			void RotateArround(const glm::vec3& target, const float& speed);

		private:

			glm::vec3 m_position;

			//  TODO: 以后可能要改成四元数
			glm::vec3 m_rotation;

			glm::vec3 m_scale;

			glm::mat4 m_trans;

		};
	}
}

#endif // !TRANSFORM_H
