#ifndef COLOR_H
#define COLOR_H
#include"RtxMath.h"

#include"../util/RtxMath.h"

namespace rtx
{
	namespace util
	{
		class Color
		{

		public:

			Color() : rgba(0, 0, 0, 1.0f) {}

			Color(float r, float g, float b) :rgba(r, g, b, 1.0f) {}

			Color(glm::vec3 color) :rgba(color, 1.0f) {}

			Color(float r, float g, float b, float a) :rgba(r, g, b, a) {}

			Color(glm::vec3 color, float a) :rgba(color, a) {}

			Color(unsigned long color)
			{
				if (color > 0xffffff)
				{
					rgba.a = static_cast<float>(color & 0xff);
					rgba.b = static_cast<float>((color >> 8) & 0xff);
					rgba.g = static_cast<float>((color >> 16) & 0xff);
					rgba.r = static_cast<float>((color >> 24) & 0xff);
				}
				else
				{
					rgba.a = 1.0f;
					rgba.b = static_cast<float>((color) & 0xff);
					rgba.g = static_cast<float>((color >> 8) & 0xff);
					rgba.r = static_cast<float>((color >> 16) & 0xff);
				}
				rgba /= TO_RGB;
			}

			float& operator[](const int& index)
			{
				if (index >= 0 && index < 3)
				{
					return rgba[index];
				}
				return rgba.a;
			}

			float operator[](const int& index)const
			{
				if (index >= 0 && index < 3)
				{
					return rgba[index];
				}
				return 0.0f;
			}

			glm::vec4& RGBA()
			{
				return rgba;
			}

			glm::vec4 RGBA()const
			{
				return rgba;
			}

			glm::vec3 RGB()const
			{
				return glm::vec3(rgba.r, rgba.g, rgba.b);
			}

			float r()const { return rgba.r; }
			float g()const { return rgba.g; }
			float b()const { return rgba.b; }
			float a()const { return rgba.a; }

			float& r() { return rgba.r; }
			float& g() { return rgba.g; }
			float& b() { return rgba.b; }
			float& a() { return rgba.a; }

		private:

			glm::vec4 rgba;
		};
	}

}
#endif // !COLOR_H