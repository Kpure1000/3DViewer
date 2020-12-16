#ifndef CAMERA_H
#define CAMERA_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"../util/RtxMath.h"

#include"Transform.h"

namespace rtx
{
	namespace render
	{
		class Camera
		{
		public:

			Camera()
				: origin(glm::vec3(0.0f)), target(glm::vec3(1.0f)), direction(glm::vec3(1.0f)),
				cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)), view(glm::mat4(1.0f)), projection(glm::mat4(1.0f)),
				foV(45.0f), aspect(1.0f), near(0.01f), far(100.0f)
			{}

			/// <summary>
			/// Create a camera
			/// </summary>
			/// <param name="LookFrom">Origin position</param>
			/// <param name="LookAt">Look at</param>
			/// <param name="CameraUp">Up direction</param>
			/// <param name="FoV">Fov</param>
			/// <param name="Aspect">Aspect</param>
			/// <param name="Near">Near distance</param>
			/// <param name="Far">Far distance</param>
			Camera(glm::vec3 LookFrom, glm::vec3 LookAt, glm::vec3 CameraUp,
				float FoV, float Aspect, float Near, float Far);

			/// <summary>
			/// Create a camera
			/// </summary>
			/// <param name="LookFrom">Origin position</param>
			/// <param name="LookAt">Look at</param>
			/// <param name="CameraUp">Up direction</param>
			/// <param name="FoV">Fov</param>
			/// <param name="Aspect">Aspect</param>
			/// <param name="Near">Near distance</param>
			/// <param name="Far">Far distance</param>
			/// <param name="isTranCa">??</param>
			[[deprecated("This constructor will be deleted")]]
			Camera(glm::vec3 LookFrom, glm::vec3 LookAt, glm::vec3 CameraUp,
				float FoV, float Aspect, float Near, float Far, bool isTranCa);

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

			Transform m_trans;

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
