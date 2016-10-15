#pragma once
#include <Engine.h>

#define ZERO (Scalar) 0.0f
#define ONE (Scalar) 1.0f

namespace ENGINE_NAME {
	namespace Math {

		template<typename Scalar>
		class Vector2 {
		public:
			union {
				struct { Scalar x; Scalar y; };
				Scalar components[2];
			};

			Vector2() : x(ZERO), y(ZERO) {}
			Vector2(Scalar x, Scalar y) : x(x), y(y) {}

			inline static Vector2 Zero() { return ZERO, ZERO, }
			inline static Vector2 XAxis() { return ONE, ZERO, }
			inline static Vector2 YAxis() { return ZERO, ONE, }

			inline Vector2& Add(const Vector2& other) { x += other.x; y += other.y; return *this; }
			inline Vector2& Subtract(const Vector2& other) { x -= other.x; y -= other.y; return *this; }
			inline Vector2& Multiply(const Vector2& other) { x *= other.x; y *= other.y; return *this; }
			inline Vector2& Divide(const Vector2& other) { x /= other.x; y /= other.y; return *this; }

			inline Vector2& Add(Scalar other) { x += other; y += other; return *this; }
			inline Vector2& Subtract(Scalar other) { x -= other; y -= other; return *this; }
			inline Vector2& Multiply(Scalar other) { x *= other; y *= other; return *this; }
			inline Vector2& Divide(Scalar other) { x /= other; y /= other; return *this; }

			inline static Vector2& Add(Vector2 left, const Vector2& right) { return left.Add(right); }
			inline static Vector2& Subtract(Vector2 left, const Vector2& right) { return left.Subtract(right); }
			inline static Vector2& Multiply(Vector2 left, const Vector2& right) { return left.Multiply(right); }
			inline static Vector2& Divide(Vector2 left, const Vector2& right) { return left.Divide(right); }

			inline static Vector2& Add(Vector2 left, Scalar right) { return left.Add(right); }
			inline static Vector2& Subtract(Vector2 left, Scalar right) { return left.Subtract(right); }
			inline static Vector2& Multiply(Vector2 left, Scalar right) { return left.Multiply(right); }
			inline static Vector2 Divide(Vector2 left, Scalar right) { return left.Divide(right); }

			inline friend Vector2 operator+(Vector2 left, const Vector2& right) { return left.Add(right); }
			inline friend Vector2 operator-(Vector2 left, const Vector2& right) { return left.Subtract(right); }
			inline friend Vector2 operator*(Vector2 left, const Vector2& right) { return left.Multiply(right); }
			inline friend Vector2 operator/(Vector2 left, const Vector2& right) { return left.Divide(right); }

			inline friend Vector2 operator+(Vector2 left, Scalar right) { return left.Add(right); }
			inline friend Vector2 operator-(Vector2 left, Scalar right) { return left.Subtract(right); }
			inline friend Vector2 operator*(Vector2 left, Scalar right) { return left.Multiply(right); }
			inline friend Vector2 operator/(Vector2 left, Scalar right) { return left.Divide(right); }

			inline Vector2& operator+=(const Vector2& other) { return Add(other); }
			inline Vector2& operator-=(const Vector2& other) { return Subtract(other); }
			inline Vector2& operator*=(const Vector2& other) { return Multiply(other); }
			inline Vector2& operator/=(const Vector2& other) { return Divide(other); }

			inline Vector2& operator+=(Scalar other) { return Add(other); }
			inline Vector2& operator-=(Scalar other) { return Subtract(other); }
			inline Vector2& operator*=(Scalar other) { return Multiply(other); }
			inline Vector2& operator/=(Scalar other) { return Divide(other); }

			inline bool operator<(const Vector2& other) const { return x < other.x && y < other.y; }
			inline bool operator<=(const Vector2& other) const { return x <= other.x && y <= other.y; }
			inline bool operator>(const Vector2& other) const { return x > other.x && y > other.y; }
			inline bool operator>=(const Vector2& other) const { return x >= other.x && y >= other.y; }
			inline bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }
			inline bool operator!=(const Vector2& other) const { return !(*this == other); }

			inline Vector2 operator-(const Vector2& Vector2tor) { return Vector2(-Vector2tor.x, -Vector2tor.y); }

			inline Scalar Dot(const Vector2& other) const { return x * other.x + y * other.y; }

			inline Scalar LengthSquared() const { return x * x + y * y; }

			inline static float Length(const Vector2& vec) { return (float)sqrt(vec.x * vec.x + vec.y * vec.y); }
			inline float Length() const { return (float)sqrt(x * x + y * y); }

			inline Vector2& Normalize() { return Divide((Scalar)Length()); }
			inline static Vector2 Normalize(Vector2& v) { return Divide(v, v.Length()); }

			inline float Distance(const Vector2& other) const { return Divide(*this, other).Length(); }

			inline friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector) { return stream << "Vector2: (" << vector.x << ", " << vector.y << ")"; }

			inline Scalar& operator[](byte x) { return components[x]; };
			inline const Scalar& operator[](byte x) const { return components[x]; };
		};
	}
}

#undef ZERO
#undef ONE