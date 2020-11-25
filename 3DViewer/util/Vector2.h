#ifndef VECTOR2_H
#define VECTOR2_H
#include<cmath>

namespace rtx
{

	namespace util
	{

		template<class T>
		class Vector2
		{
		public:

			Vector2() {}

			Vector2(T x, T y) {
				v[0] = x;
				v[1] = y;
			}

			static Vector2 One;

			static Vector2 Zero;

			inline T x()const { return v[0]; }
			inline T y()const { return v[1]; }

			bool operator== (const Vector2& b)const
			{
				return (*this)[0] == b[0] && (*this)[1] == b[1];
			}

			Vector2& operator=(const Vector2& b)
			{
				(*this)[0] = b[0];
				(*this)[1] = b[1];
				return (*this);
			}

			inline const Vector2& operator+() const { return *this; }
			inline Vector2 operator-()const { return Vector2(-v[0], -v[1]); }
			inline T operator[](const int& index)const { return v[index]; }
			inline T& operator[](const int& index) { return v[index]; }

			inline Vector2& operator+=(const Vector2& v2)
			{
				v[0] += v2.v[0];
				v[1] += v2.v[1];
				return *this;
			}

			inline Vector2& operator-=(const Vector2& v2)
			{
				v[0] -= v2.v[0];
				v[1] -= v2.v[1];
				return *this;
			}

			inline Vector2& operator*=(const Vector2& v2)
			{
				v[0] *= v2.v[0];
				v[1] *= v2.v[1];
				return *this;
			}

			inline Vector2& operator/=(const Vector2& v2)
			{
				v[0] /= v2.v[0];
				v[1] /= v2.v[1];
				return *this;
			}

			inline Vector2& operator*=(const float& t)
			{
				v[0] *= t;
				v[1] *= t;
				return *this;
			}

			inline Vector2& operator/=(const float& t)
			{
				float k = 1.0f / t;
				v[0] *= k;
				v[1] *= k;
				return *this;
			}

			inline float Magnitude()const
			{
				return sqrtf(v[0] * v[0] + v[1] * v[1]);
			}

			inline float SqaureMagnitude()const
			{
				return v[0] * v[0] + v[1] * v[1];
			}

			inline Vector2 Normalize()
			{
				return (*this) /= (*this).Magnitude();
			}

			static float Magnitude(const Vector2& v);

			static Vector2 Normalize(const Vector2& v2);

			inline static float Dot(const Vector2& v1, const Vector2& v2)
			{
				return v1[0] * v2[0] + v1[1] * v2[1];
			}

			/*inline static Vector2 Cross(const Vector2& v1, const Vector2& v2)
			{
				return Vector2(v1[1] * v2[2] - v1[2] * v2[1],
					v1[2] * v2[0] - v1[0] * v2[2],
					v1[0] * v2[1] - v1[1] * v2[0]);
			}*/

			inline static float Distance(const Vector2& v1, const Vector2& v2)
			{
				return (float)sqrt((v1[0] - v2[0]) * (v1[0] - v2[0]) +
					(v1[1] - v2[1]) * (v1[1] - v2[1]));
			}

			T v[2];
		};


		typedef Vector2<int> Vector2i;
		typedef Vector2<float> Vector2f;
		typedef Vector2<double> Vector2d;


		template<class T>
		inline Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2)
		{
			return Vector2<T>(v1[0] + v2[0], v1[1] + v2[1]);
		}

		template<class T>
		inline Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2)
		{
			return Vector2<T>(v1[0] - v2[0], v1[1] - v2[1]);
		}

		template<class T>
		inline Vector2<T> operator*(const Vector2<T>& v1, const Vector2<T>& v2)
		{
			return Vector2<T>(v1[0] * v2[0], v1[1] * v2[1]);
		}

		template<class T>
		inline Vector2<T> operator/(const Vector2<T>& v1, const Vector2<T>& v2)
		{
			return Vector2<T>(v1[0] / v2[0], v1[1] / v2[1]);
		}

		template<class T>
		inline Vector2<T> operator*(const float& t, const Vector2<T>& v2)
		{
			return Vector2<T>(v2[0] * t, v2[1] * t);
		}

		template<class T>
		inline Vector2<T> operator*(const Vector2<T>& v2, const float& t)
		{
			return Vector2<T>(v2[0] * t, v2[1] * t);
		}

		template<class T>
		inline Vector2<T> operator/(const Vector2<T>& v2, const float& t)
		{
			float k = 1.0f / t;
			return Vector2<T>(v2[0] * k, v2[1] * k);
		}

		template<class T>
		inline float Vector2<T>::Magnitude(const Vector2<T>& v)
		{
			return (float)sqrt(v[0] * v[0] + v[1] * v[1]);
		}

		template<class T>
		inline Vector2<T> Vector2<T>::Normalize(const Vector2<T>& v2)
		{
			return v2 / v2.Magnitude();
		}


	}



}
#endif // !VECTOR2_H