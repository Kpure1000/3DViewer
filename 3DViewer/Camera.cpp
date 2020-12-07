#include "render/Camera.h"

namespace rtx
{
	namespace render
	{
		Camera::Camera(glm::vec3 LookFrom, glm::vec3 LookAt)
		{
			origin = LookFrom;
			target = LookAt;
			direction = glm::normalize(origin- target);

			cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, direction));
			//cameraUp = glm::normalize(glm::cross(-direction, cameraRight));
			view = glm::lookAt(origin, target, cameraUp);
		}

		Camera::Camera(glm::vec3 LookFrom, glm::vec3 LookAt,
			float FoV, float Aspect)
		{
			origin = LookFrom;
			target = LookAt;
			direction = glm::normalize(origin- target);

			cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, direction));
			//cameraUp = glm::normalize(glm::cross(-direction, cameraRight));
			view = glm::lookAt(origin, target, cameraUp);

			foV = FoV;
			aspect = Aspect;
			near = 0.01f; far = 100.0f;
			projection = glm::perspective(glm::radians(foV), aspect, 0.01f, 100.0f);
		}

		Camera::Camera(glm::vec3 LookFrom, glm::vec3 LookAt,
			float FoV, float Aspect, float Near, float Far)
		{
			origin = LookFrom;
			target = LookAt;
			direction = glm::normalize(origin- target);

			cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, direction));
			//cameraUp = glm::normalize(glm::cross(-direction, cameraRight));
			view = glm::lookAt(origin, target, cameraUp);

			foV = FoV;
			aspect = Aspect;
			near = Near; far = Far;
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
