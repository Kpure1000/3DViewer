#ifndef VECTOR3_H
#define VECTOR3_H
#include<cmath>

namespace rtx
{

	namespace util
	{

		template<class T>
		class Vector3
		{
		public:

			Vector3() {}

			Vector3(T x, T y, T z) {
				v[0] = x;
				v[1] = y;
				v[2] = z;
			}

			static Vector3 One;

			static Vector3 Zero;

			inline T x()const { return v[0]; }
			inline T y()const { return v[1]; }
			inline T z()const { return v[2]; }

			bool operator== (const Vector3& b)const
			{
				return (*this)[0] == b[0] && (*this)[1] == b[1] && (*this)[2] == b[2];
			}

			Vector3& operator=(const Vector3& b)
			{
				(*this)[0] = b[0];
				(*this)[1] = b[1];
				(*this)[2] = b[2];
				return (*this);
			}

			inline const Vector3& operator+() const { return *this; }
			inline Vector3 operator-()const { return Vector3(-v[0], -v[1], -v[2]); }
			inline T operator[](const int& index)const { return v[index]; }
			inline T& operator[](const int& index) { return v[index]; }

			inline Vector3& operator+=(const Vector3& v2)
			{
				v[0] += v2.v[0];
				v[1] += v2.v[1];
				v[2] += v2.v[2];
				return *this;
			}

			inline Vector3& operator-=(const Vector3& v2)
			{
				v[0] -= v2.v[0];
				v[1] -= v2.v[1];
				v[2] -= v2.v[2];
				return *this;
			}

			inline Vector3& operator*=(const Vector3& v2)
			{
				v[0] *= v2.v[0];
				v[1] *= v2.v[1];
				v[2] *= v2.v[2];
				return *this;
			}

			inline Vector3& operator/=(const Vector3& v2)
			{
				v[0] /= v2.v[0];
				v[1] /= v2.v[1];
				v[2] /= v2.v[2];
				return *this;
			}

			inline Vector3& operator*=(const float& t)
			{
				v[0] *= t;
				v[1] *= t;
				v[2] *= t;
				return *this;
			}

			inline Vector3& operator/=(const float& t)
			{
				float k = 1.0f / t;
				v[0] *= k;
				v[1] *= k;
				v[2] *= k;
				return *this;
			}

			inline float Magnitude()const
			{
				return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
			}

			inline float SqaureMagnitude()const
			{
				return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
			}

			inline Vector3 Normalize()
			{
				return (*this) /= (*this).Magnitude();
			}

			static float Magnitude(const Vector3& v);

			static Vector3 Normalize(const Vector3& v2);

			inline static float Dot(const Vector3& v1, const Vector3& v2)
			{
				return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
			}

			inline static Vector3 Cross(const Vector3& v1, const Vector3& v2)
			{
				return Vector3(v1[1] * v2[2] - v1[2] * v2[1],
					v1[2] * v2[0] - v1[0] * v2[2],
					v1[0] * v2[1] - v1[1] * v2[0]);
			}

			inline static float Distance(const Vector3& v1, const Vector3& v2)
			{
				return (float)sqrt((v1[0] - v2[0]) * (v1[0] - v2[0]) +
					(v1[1] - v2[1]) * (v1[1] - v2[1]) +
					(v1[2] - v2[2]) * (v1[2] - v2[2]));
			}

			T v[3];
		};


		typedef Vector3<int> Vector3i;
		typedef Vector3<float> Vector3f;
		typedef Vector3<double> Vector3d;


		template<class T>
		inline Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2)
		{
			return Vector3<T>(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
		}

		template<class T>
		inline Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2)
		{
			return Vector3<T>(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
		}

		template<class T>
		inline Vector3<T> operator*(const Vector3<T>& v1, const Vector3<T>& v2)
		{
			return Vector3<T>(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
		}

		template<class T>
		inline Vector3<T> operator/(const Vector3<T>& v1, const Vector3<T>& v2)
		{
			return Vector3<T>(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
		}

		template<class T>
		inline Vector3<T> operator*(const float& t, const Vector3<T>& v2)
		{
			return Vector3<T>(v2[0] * t, v2[1] * t, v2[2] * t);
		}

		template<class T>
		inline Vector3<T> operator*(const Vector3<T>& v2, const float& t)
		{
			return Vector3<T>(v2[0] * t, v2[1] * t, v2[2] * t);
		}

		template<class T>
		inline Vector3<T> operator/(const Vector3<T>& v2, const float& t)
		{
			float k = 1.0f / t;
			return Vector3<T>(v2[0] * k, v2[1] * k, v2[2] * k);
		}

		template<class T>
		inline float Vector3<T>::Magnitude(const Vector3<T>& v)
		{
			return (float)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
		}

		template<class T>
		inline Vector3<T> Vector3<T>::Normalize(const Vector3<T>& v2)
		{
			return v2 / v2.Magnitude();
		}


	}



}
#endif // !VECTOR3_H