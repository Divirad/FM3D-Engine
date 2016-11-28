#pragma once
#include <Engine.h>

#define ZERO (Scalar) 0.0f
#define ONE (Scalar) 1.0f

namespace FM3D {
	namespace Math {

		template<typename Scalar>
		class Vector4 {
		public:
			union {
				struct { Scalar x; Scalar y; Scalar z; Scalar w; };
				Scalar components[4];
			};

			Vector4() : x(ZERO), y(ZERO), z(ZERO), w(ZERO) {}
			Vector4(Scalar scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}
			Vector4(Scalar x, Scalar y) : x(x), y(y), z(ZERO), w(ZERO) {}
			Vector4(Scalar x, Scalar y, Scalar z) : x(x), y(y), z(z), w(ZERO) {}
			Vector4(Scalar x, Scalar y, Scalar z, Scalar w) : x(x), y(y), z(z), w(w) {}

			inline static Vector4 Zero() { return ZERO, ZERO, ZERO; }

			inline Vector4& Add(const Vector4& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
			inline Vector4& Subtract(const Vector4& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
			inline Vector4& Multiply(const Vector4& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
			inline Vector4& Divide(const Vector4& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }

			inline Vector4& Add(Scalar other) { x += other; y += other; z += other; w += other; return *this; }
			inline Vector4& Subtract(Scalar other) { x -= other; y -= other; z -= other; w -= other; return *this; }
			inline Vector4& Multiply(Scalar other) { x *= other; y *= other; z *= other; w *= other; return *this; }
			inline Vector4& Divide(Scalar other) { x /= other; y /= other; z /= other; w /= other; return *this; }

			inline static Vector4& Add(Vector4 left, const Vector4& right) { return left.Add(right); }
			inline static Vector4& Subtract(Vector4 left, const Vector4& right) { return left.Subtract(right); }
			inline static Vector4& Multiply(Vector4 left, const Vector4& right) { return left.Multiply(right); }
			inline static Vector4& Divide(Vector4 left, const Vector4& right) { return left.Divide(right); }

			inline static Vector4& Add(Vector4 left, Scalar right) { return left.Add(right); }
			inline static Vector4& Subtract(Vector4 left, Scalar right) { return left.Subtract(right); }
			inline static Vector4& Multiply(Vector4 left, Scalar right) { return left.Multiply(right); }
			inline static Vector4& Divide(Vector4 left, Scalar right) { return left.Divide(right); }

			inline friend Vector4 operator+(Vector4 left, const Vector4& right) { return left.Add(right); }
			inline friend Vector4 operator-(Vector4 left, const Vector4& right) { return left.Subtract(right); }
			inline friend Vector4 operator*(Vector4 left, const Vector4& right) { return left.Multiply(right); }
			inline friend Vector4 operator/(Vector4 left, const Vector4& right) { return left.Divide(right); }

			inline friend Vector4 operator+(Vector4 left, Scalar right) { return left.Add(right); }
			inline friend Vector4 operator-(Vector4 left, Scalar right) { return left.Subtract(right); }
			inline friend Vector4 operator*(Vector4 left, Scalar right) { return left.Multiply(right); }
			inline friend Vector4 operator/(Vector4 left, Scalar right) { return left.Divide(right); }

			inline Vector4& operator+=(const Vector4& other) { return Add(other); }
			inline Vector4& operator-=(const Vector4& other) { return Subtract(other); }
			inline Vector4& operator*=(const Vector4& other) { return Multiply(other); }
			inline Vector4& operator/=(const Vector4& other) { return Divide(other); }

			inline Vector4& operator+=(Scalar other) { return Add(other); }
			inline Vector4& operator-=(Scalar other) { return Subtract(other); }
			inline Vector4& operator*=(Scalar other) { return Multiply(other); }
			inline Vector4& operator/=(Scalar other) { return Divide(other); }

			inline bool operator<(const Vector4& other) const { return x < other.x && y < other.y && z < other.z && w < other.w; }
			inline bool operator<=(const Vector4& other) const { return x <= other.x && y <= other.y && z <= other.z && w <= other.w; }
			inline bool operator>(const Vector4& other) const { return x > other.x && y > other.y && z > other.z && w > other.w; }
			inline bool operator>=(const Vector4& other) const { return x >= other.x && y >= other.y && z >= other.z && w >= other.w; }
			inline bool operator==(const Vector4& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
			inline bool operator!=(const Vector4& other) const { return !(*this == other); }

			inline Vector4 operator-(const Vector4& vector) { return -vector.x, -vector.y, -vector.z, -vector.w; }

			inline Scalar Dot(const Vector4& other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }

			inline Scalar LengthSquared() const { return x * x + y * y + z * z + w * w; }

			inline static float Length(const Vector4& vec) { return (float)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w); }
			inline float Length() const { return (float)sqrt(x * x + y * y + z * z + w * w); }

			inline Vector4& Normalize() { return Divide((Scalar)Length()); }
			inline static Vector4 Normalize(Vector4& v) { return Divide(v, v.Length()); }

			inline float Distance(const Vector4& other) const { return Divide(*this, other).Length(); }

			inline friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector) { return stream << "Vector4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")"; }

			inline Scalar& operator[](byte x) { return components[x]; };
			inline const Scalar& operator[](byte x) const { return components[x]; };
		};
	}
}

#undef ZERO
#undef ONE