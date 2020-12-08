#ifndef CAMERA_H
#define CAMERA_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"../util/RtxMath.h"

namespace rtx
{
	namespace render
	{
		class Camera
		{
		public:

			Camera() {}

			Camera(glm::vec3 LookFrom, glm::vec3 LookAt, glm::vec3 CameraUp,
				float FoV, float Aspect, float Near, float Far);

			glm::vec3 GetOrigin()const;

			glm::vec3 GetTarget()const;

			glm::vec3 GetDirection()const;

			glm::vec3 GetCameraUp()const;

			glm::mat4 GetView()const;

			glm::mat4 GetProjection()const;

			float GetFoV()const;

			void SetOrigin(glm::vec3 LookFrom);

			void SetTarget(glm::vec3 LookAt);

			void SetCameraUp(glm::vec3 Up);

			void SetFoV(float FoV);

			void SetAspect(float Aspect);

		private:

			glm::vec3 origin;

			glm::vec3 target;

			glm::vec3 direction;

			glm::vec3 cameraUp;

			glm::mat4 view;

			glm::mat4 projection;

			float foV;

			float aspect;

			float near, far;
		};

	}
}

#endif // !CAMERA_H
