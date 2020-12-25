#include "render/Camera.h"

namespace rtx
{
	namespace render
	{
		Camera::Camera(glm::vec3 LookFrom, glm::vec3 LookAt, glm::vec3 CameraUp,
			float FoV, float Aspect, float Near, float Far)
		{
			m_origin = LookFrom;
			m_target = LookAt;
			m_direction = glm::normalize(m_origin - m_target);

			m_cameraUp = CameraUp;
			m_foV = FoV;
			m_aspect = Aspect;
			m_near = Near;
			m_far = Far;

			glm::vec3 cameraRight = glm::normalize(glm::cross(m_cameraUp, m_direction));
			//cameraUp = glm::normalize(glm::cross(-direction, cameraRight));
			m_view = glm::lookAt(m_origin, m_target, m_cameraUp);

			m_projection = glm::perspective(glm::radians(m_foV), m_aspect, m_near, m_far);
		}

		Camera::Camera(glm::vec3 LookFrom, glm::vec3 LookAt, glm::vec3 CameraUp,
			float FoV, float Aspect, float Near, float Far, bool isTranCa)
		{
			m_origin = LookFrom;
			m_target = LookAt;
			m_direction = glm::normalize(m_origin - m_target);

			m_cameraUp = CameraUp;
			m_foV = FoV;
			m_aspect = Aspect;
			m_near = Near;
			m_far = Far;

			m_trans.SetPosition(LookFrom);
			m_trans.SetRotation(m_direction, 0.0f);

			glm::vec3 cameraRight = glm::normalize(glm::cross(m_cameraUp, m_direction));
			//cameraUp = glm::normalize(glm::cross(-direction, cameraRight));
			m_view = glm::lookAt(m_origin, m_target, m_cameraUp);

			m_projection = glm::perspective(glm::radians(m_foV), m_aspect, m_near, m_far);
		}

		glm::vec3 Camera::GetOrigin() const
		{
			return m_origin;
		}

		glm::vec3 Camera::GetTarget() const
		{
			return m_target;
		}

		glm::vec3 Camera::GetDirection()const
		{
			return m_direction;
		}

		glm::vec3 Camera::GetCameraUp() const
		{
			return m_cameraUp;
		}

		glm::mat4 Camera::GetView() const
		{
			return m_view;
		}

		glm::mat4 Camera::GetProjection() const
		{
			return m_projection;
		}

		float Camera::GetFoV() const
		{
			return m_foV;
		}

		float Camera::GetAspect()const
		{
			return m_aspect;
		}

		void Camera::GetLeftBottom(glm::vec3& leftBottom, glm::vec3& hor, glm::vec3& ver)const
		{
			float theta = glm::radians(m_foV);
			float height = 2 * tan(theta / 2);
			float width = height * m_aspect;
			glm::vec3 front = glm::normalize(m_target - m_origin);
			glm::vec3 right = glm::normalize(glm::cross(-m_cameraUp, front));
			glm::vec3 up = glm::cross(right, front);
			leftBottom = m_origin + front - width / 2 * right - height / 2 * up;
			hor = width * right;
			ver = height * up;
		}

		void Camera::SetOrigin(glm::vec3 LookFrom)
		{
			m_origin = LookFrom;
			m_direction = glm::normalize(m_origin- m_target);
			m_view = glm::lookAt(m_origin, m_target, m_cameraUp);
		}

		void Camera::SetTarget(glm::vec3 LookAt)
		{
			m_target = LookAt;
			m_direction = glm::normalize(m_origin- m_target);
			m_view = glm::lookAt(m_origin, m_target, m_cameraUp);
		}

		void Camera::SetCameraUp(glm::vec3 Up)
		{
			m_cameraUp = Up; 
			glm::vec3 cameraRight = glm::normalize(glm::cross(m_cameraUp, m_direction));
			m_view = glm::lookAt(m_origin, m_target, m_cameraUp);
		}

		void Camera::SetFoV(float FoV)
		{
			m_foV = FoV;
			m_projection = glm::perspective(glm::radians(m_foV), m_aspect, m_near, m_far);
		}

		void Camera::SetAspect(float Aspect)
		{
			m_aspect = Aspect;
			m_projection = glm::perspective(glm::radians(m_foV), m_aspect, m_near, m_far);
		}

	}
}
