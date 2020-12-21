#include "render/Camera.h"

namespace rtx
{
	namespace render
	{
		Camera::Camera(glm::vec3 LookFrom, glm::vec3 LookAt, glm::vec3 CameraUp,
			float FoV, float Aspect, float Near, float Far)
		{
			origin = LookFrom;
			target = LookAt;
			direction = glm::normalize(origin - target);

			cameraUp = CameraUp;
			foV = FoV;
			aspect = Aspect;
			near = Near;
			far = Far;

			glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, direction));
			//cameraUp = glm::normalize(glm::cross(-direction, cameraRight));
			view = glm::lookAt(origin, target, cameraUp);

			projection = glm::perspective(glm::radians(foV), aspect, near, far);
		}

		Camera::Camera(glm::vec3 LookFrom, glm::vec3 LookAt, glm::vec3 CameraUp,
			float FoV, float Aspect, float Near, float Far, bool isTranCa)
		{
			origin = LookFrom;
			target = LookAt;
			direction = glm::normalize(origin - target);

			cameraUp = CameraUp;
			foV = FoV;
			aspect = Aspect;
			near = Near;
			far = Far;

			m_trans.SetPosition(LookFrom);
			m_trans.SetRotation(direction, 0.0f);

			glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, direction));
			//cameraUp = glm::normalize(glm::cross(-direction, cameraRight));
			view = glm::lookAt(origin, target, cameraUp);

			projection = glm::perspective(glm::radians(foV), aspect, near, far);
		}

		glm::vec3 Camera::GetOrigin() const
		{
			return origin;
		}

		glm::vec3 Camera::GetTarget() const
		{
			return target;
		}

		glm::vec3 Camera::GetDirection()const
		{
			return direction;
		}

		glm::vec3 Camera::GetCameraUp() const
		{
			return cameraUp;
		}

		glm::mat4 Camera::GetView() const
		{
			return view;
		}

		glm::mat4 Camera::GetProjection() const
		{
			return projection;
		}

		float Camera::GetFoV() const
		{
			return foV;
		}

		void Camera::GetLeftBottom(glm::vec3& leftBottom,glm::vec3 &hor,glm::vec3& ver)const
		{
			float theta = glm::radians(foV);
			float height = 2 * tan(theta / 2);
			float width = aspect * height;
			glm::vec3 front = glm::normalize(target - origin);
			glm::vec3 right = glm::normalize(glm::cross(cameraUp, -front));
			glm::vec3 up = cameraUp;
			leftBottom = origin + front - width / 2 * right - height / 2 * up;
			hor = width * right;
			ver = height * up;
		}

		void Camera::SetOrigin(glm::vec3 LookFrom)
		{
			origin = LookFrom;
			direction = glm::normalize(origin- target);
			view = glm::lookAt(origin, target, cameraUp);
		}

		void Camera::SetTarget(glm::vec3 LookAt)
		{
			target = LookAt;
			direction = glm::normalize(origin- target);
			view = glm::lookAt(origin, target, cameraUp);
		}

		void Camera::SetCameraUp(glm::vec3 Up)
		{
			cameraUp = Up; 
			glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, direction));
			view = glm::lookAt(origin, target, cameraUp);
		}

		void Camera::SetFoV(float FoV)
		{
			foV = FoV;
			projection = glm::perspective(glm::radians(foV), aspect, near, far);
		}

		void Camera::SetAspect(float Aspect)
		{
			aspect = Aspect;
			projection = glm::perspective(glm::radians(foV), aspect, near, far);
		}

	}
}
