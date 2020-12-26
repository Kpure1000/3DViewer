#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include"Camera.h"
#include"Window.h"
#include"../event/Mouse.h"
#include"../system/Time.h"
#include"../util/RtxMath.h"
namespace rtx
{
	namespace render
	{
		class FPSCamera
		{
		public:

			FPSCamera(glm::vec3 LookFrom, glm::vec3 LookAt,
				float FoV, float Aspect, float Near, float Far, float CameraSpeed)
				: isMoved(false),
				yaw(0.0f), pitch(0.0f),
				cameraFov(45),
				cameraSpeed(CameraSpeed),
				camera(LookFrom, LookAt, glm::vec3(0.0f, 1.0f, 0.0f), FoV, Aspect, Near, Far)
			{
				cameraDirection = -camera.GetDirection();
				pitch = cameraDirection.y > 0 ? asin(cameraDirection.y) : -asin(-cameraDirection.y);
				//  Must clamp before this asin, or it may cause NaN(ind)
				yaw = cameraDirection.x > 0 ? -asin(glm::clamp(-cameraDirection.z / cos(pitch), -1.0f, 1.0f))
					: Pi + asin(glm::clamp(-cameraDirection.z / cos(pitch), -1.0f, 1.0f));

				cameraOrigin = camera.GetOrigin();
				cameraUp = camera.GetCameraUp();
				realSpeed = 0.0f;
				lastPos = glm::vec2(0.0f);
			}

			inline Camera GetCamera() const { return camera; }

			inline Camera& GetCamera() { return camera; }

			void Update(Window const& window)
			{
				//  TODO: this resize setting should move into window callback
				camera.SetAspect(window.GetSize().x / window.GetSize().y);
				isMoved = false;
				cameraOrigin = camera.GetOrigin();
				cameraDirection = -camera.GetDirection();
				cameraUp = camera.GetCameraUp();
				realSpeed = system::Time::deltaTime() * cameraSpeed; // adjust accordingly
				KeyContoller(window);
				MouseController(window);
				WheelController(window);
				if (isMoved)
				{
					camera.SetFoV(cameraFov);
					camera.SetOrigin(cameraOrigin);
					camera.SetTarget(cameraOrigin + cameraDirection);
					isMoved = false;
				}
			}

		private:

			void KeyContoller(Window const& window)
			{
				if (glfwGetKey(window.GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
				{
					cameraOrigin += realSpeed * cameraDirection;
					isMoved = true;
				}
				if (glfwGetKey(window.GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
				{
					cameraOrigin -= realSpeed * cameraDirection;
					isMoved = true;
				}
				if (glfwGetKey(window.GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
				{
					cameraOrigin -= glm::normalize(
						glm::cross(cameraDirection, cameraUp)
					) * realSpeed;
					isMoved = true;
				}
				if (glfwGetKey(window.GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
				{
					cameraOrigin += glm::normalize(
						glm::cross(cameraDirection, cameraUp)
					) * realSpeed;
					isMoved = true;
				}
			}


			void MouseController(Window const& window)
			{
				glm::vec2 mousePos = rtx::event::Mouse::GetPosition(window);
				if (!event::Mouse::isMouseMoved() || !event::Mouse::isButtonPressed(window, event::Mouse::Button::Right))
				{
					lastPos = mousePos;
					return;
				}
				float xoffset = mousePos.x - lastPos.x;
				float yoffset = lastPos.y - mousePos.y;
				lastPos = mousePos;

				float sensitivity = std::min(0.1f, system::Time::deltaTime() * cameraSpeed * 0.024f);
				xoffset *= sensitivity;
				yoffset *= sensitivity;

				yaw += xoffset;
				pitch += yoffset;

				if (pitch > Pi / 2.0f - 0.01f)
					pitch = Pi / 2.0f - 0.01f;
				else if (pitch < -Pi / 2.0f + 0.01f)
					pitch = -Pi / 2.0f + 0.01f;

				cameraDirection.x = cos(pitch) * cos(yaw);
				cameraDirection.z = cos(pitch) * sin(yaw);
				cameraDirection.y = sin(pitch);
				cameraDirection = glm::normalize(cameraDirection);
				isMoved = true;
			}

			void WheelController(Window const& window)
			{
				if (!event::Mouse::isWheelScrolled())return;

				if (cameraFov >= MinFov && cameraFov <= MaxFov)
					cameraFov -= event::Mouse::GetScrollOffset(window).y;
				if (cameraFov <= MinFov)
					cameraFov = MinFov;
				if (cameraFov >= MaxFov)
					cameraFov = MaxFov;

				isMoved = true;
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

			bool isMoved;

			float cameraFov;
			const float MinFov = 20.0f, MaxFov = 90.0f;

			float yaw, pitch;

		};
	}
}
#endif // !FPSCAMERA_H
