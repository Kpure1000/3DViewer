#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include"Camera.h"
#include"Window.h"
#include"../event/Mouse.h"
#include"../system/Time.h"
namespace rtx
{
	namespace render
	{
		class FPSCamera
		{
		public:

			FPSCamera(glm::vec3 LookFrom, glm::vec3 LookAt,
				float FoV, float Aspect, float Near, float Far, float CameraSpeed)
				: isMouseMoved(false), isMouseEntered(false),
				yaw(0.0f), pitch(0.0f),
				cameraFov(45),
				cameraSpeed(CameraSpeed),
				camera(LookFrom, LookAt, glm::vec3(0.0f, 1.0f, 0.0f), FoV, Aspect, Near, Far)
			{
				pitch = asin(camera.GetDirection().y / camera.GetDirection().length());
				yaw = -acos(camera.GetDirection().z / camera.GetDirection().length() *
					camera.GetDirection().y / camera.GetDirection().length()) * 180 / Pi;
				cameraDirection.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
				cameraDirection.y = sin(glm::radians(pitch));
				cameraDirection.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
				cameraDirection = glm::normalize(cameraDirection);
			}

			Camera GetCamera() const { return camera; }

			Camera& GetCamera() { return camera; }

			void Update(Window const& window)
			{
				isMouseMoved = false;
				cameraOrigin = camera.GetOrigin();
				cameraUp = camera.GetCameraUp();
				realSpeed = system::Time::deltaTime() * cameraSpeed; // adjust accordingly
				KeyContoller(window);
				MouseController(window);
				WheelController(window);
				if (isMouseMoved)
				{
					camera.SetFoV(cameraFov);
					camera.SetOrigin(cameraOrigin);
					camera.SetTarget(cameraOrigin + cameraDirection);
					camera.SetCameraUp(cameraUp);
					isMouseMoved = false;
				}
			}

		private:

			void KeyContoller(Window const& window)
			{
				if (glfwGetKey(window.GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
				{
					cameraOrigin += realSpeed * cameraDirection;
					isMouseMoved = true;
				}
				if (glfwGetKey(window.GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
				{
					cameraOrigin -= realSpeed * cameraDirection;
					isMouseMoved = true;
				}
				if (glfwGetKey(window.GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
				{
					cameraOrigin -= glm::normalize(
						glm::cross(cameraDirection, cameraUp)
					) * realSpeed;
					isMouseMoved = true;
				}
				if (glfwGetKey(window.GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
				{
					cameraOrigin += glm::normalize(
						glm::cross(cameraDirection, cameraUp)
					) * realSpeed;
					isMouseMoved = true;
				}
			}

			void MouseController(Window const& window)
			{
				if (!event::Mouse::isMouseMoved())return;
				glm::vec2 mousePos = rtx::event::Mouse::GetPosition(window);
				if (!isMouseEntered)
				{
					lastPos = mousePos;
					isMouseEntered = true;
				}
				float xoffset = mousePos.x - lastPos.x;
				float yoffset = lastPos.y - mousePos.y; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
				lastPos = mousePos;

				float sensitivity = std::min(0.05f, system::Time::deltaTime() * cameraSpeed);
				xoffset *= sensitivity;
				yoffset *= sensitivity;

				yaw += xoffset;
				pitch += yoffset;

				if (pitch > 89.9f)
					pitch = 89.9f;
				else if (pitch < -89.9f)
					pitch = -89.9f;

				cameraDirection.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
				cameraDirection.y = sin(glm::radians(pitch));
				cameraDirection.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
				cameraDirection = glm::normalize(cameraDirection);
				isMouseMoved = true;
			}

			void WheelController(Window const& window)
			{
				if (!event::Mouse::isWheelScrolled())return;

				if (cameraFov >= 20.0f && cameraFov <= 90.0f)
					cameraFov -= event::Mouse::GetScrollOffset(window).y;
				if (cameraFov <= 20.0f)
					cameraFov = 20.0f;
				if (cameraFov >= 90.0f)
					cameraFov = 90.0f;

				isMouseMoved = true;
			}

			Camera camera;

			/// <summary>
			/// Last Mouse Position
			/// </summary>
			glm::vec2 lastPos;

			/// <summary>
			/// New Camera Target(LookAt)
			/// </summary>
			glm::vec3 cameraDirection;
			glm::vec3 cameraOrigin;
			glm::vec3 cameraUp;

			float realSpeed;

			float cameraSpeed;

			bool isMouseMoved;

			bool isMouseEntered;

			float cameraFov;

			float yaw, pitch;

		};
	}
}
#endif // !FPSCAMERA_H
