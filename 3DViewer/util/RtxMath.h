#ifndef MAX_FLOAT
#define MAX_FLOAT 1e30f
#endif // !MAX_FLOAT

#ifndef TO_RGB
#define TO_RGB 255.99f
#endif // !_TO_RGB

#ifndef RAND_M
#define RAND_M 0x100000000LL  
#endif // !RAND_M
#ifndef RAND_C
#define RAND_C 0xB16  
#endif // !RAND_C
#ifndef RAND_A
#define RAND_A 0x5DEECE66DLL 
#endif // !RAND_A

#ifndef Pi
#define Pi (glm::pi<float>())
#endif // !Pi


#ifndef RAYMATH_H
#define RAYMATH_H
#include<iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace rtx
{
	namespace util
	{
		class RayMath
		{
		public:

			static inline double Drand48()
			{
				seed = (RAND_A * seed + RAND_C) & 0xffffffffffffLL;
				unsigned int x = static_cast<unsigned int>(seed >> 16);
				return  ((double)x / (double)RAND_M);
			}

			static inline void Srand48(unsigned int i)
			{
				srand(i);
				seed = (((long long int)i) << 16) | rand();
			}

			static inline glm::vec3 randomUnitVector()
			{
				glm::vec3 re;
				do
				{
					re = 2.0f * glm::vec3(Drand48(), Drand48(), Drand48()) - glm::vec3(1, 1, 1);
				} while (re.length() > 1.0f);
				return re;
			}

			static inline glm::vec3 random_in_unit_ball()
			{
				glm::vec3 re;
				do
				{
					re = 2.0f * glm::vec3(Drand48(), Drand48(), Drand48()) - glm::vec3(1, 1, 1);
				} while (re.length() > 1.0f);
				return re;
			}

			static inline glm::vec3 Reflect(const glm::vec3& in, const glm::vec3& normal)
			{
				return in - 2 * glm::dot(in, normal) * normal;
			}

			static bool Refract(const glm::vec3& in, const glm::vec3& normal, const float& refRate, glm::vec3& refracted)
			{
				glm::vec3 uvin = glm::normalize(in);
				float dt = glm::dot(uvin, normal);
				float discrimination = 1 - refRate * refRate * (1 - dt * dt);
				if (discrimination > 0)
				{
					refracted = refRate * (uvin - normal * dt) - normal * sqrt(discrimination);
					return true;
				}
				return false;
			}

			static inline float Schlick(const float& cosine, const float& refRate)
			{
				float r0 = (1 - refRate) / (1 + refRate);
				r0 *= r0;
				return r0 + (1 - r0) * powf((1 - cosine), 5);
			}

			static std::string ToString(glm::vec3 vector3)
			{
				char str[64];
				sprintf_s(str, "(%.3f, %.3f, %.3f)", vector3.x, vector3.y, vector3.z);
				return std::string(str);
			}

			static std::string ToString(glm::vec2 vector2)
			{
				char str[64];
				sprintf_s(str, "(%.3f, %.3f)", vector2.x, vector2.y);
				return std::string(str);
			}

		private:

			static unsigned long long seed;

		};

	}
}


#endif // !RAYMATH_H
