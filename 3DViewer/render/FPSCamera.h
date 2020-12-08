#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include"Camera.h"

namespace rtx
{
	namespace render
	{
		class FPSCamera
		{
		public:

			FPSCamera(glm::vec3 LookFrom, glm::vec3 LookAt,
				float FoV, float Aspect, float Near, float Far)
				: camera(LookFrom, LookAt, 
					glm::vec3(0.0f, 1.0f, 0.0f), FoV, Aspect, Near, Far)
			{
			}

			Camera GetCamera() const{ return camera; }

			Camera& GetCamera() { return camera; }

		private:

			Camera camera;

		};
	}
}
#endif // !FPSCAMERA_H
