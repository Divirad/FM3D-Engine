#pragma once
#include <Engine.h>

#define ZERO (Scalar) 0.0f
#define ONE (Scalar) 1.0f

namespace FM3D {
	namespace Math {

		template<typename Scalar>
		class Vector3 {
		public:
			union {
				struct { Scalar x; Scalar y; Scalar z; };
				struct { Vector2<Scalar> xy; Scalar z; };
				Scalar components[3];
			};

			Vector3() : x(ZERO), y(ZERO), z(ZERO) {}
			Vector3(Scalar scalar) : x(scalar), y(scalar), z(scalar) {}
			Vector3(Scalar x, Scalar y) : x(x), y(y), z(ZERO) {}
			Vector3(Vector2<Scalar> xy, Scalar z) : xy(xy), z(z) {}
			Vector3(Scalar x, Scalar y, Scalar z) : x(x), y(y), z(z) {}

			inline static Vector3 Zero() { return Vector3(ZERO, ZERO, ZERO); }
			inline static Vector3 XAxis() { return Vector3(ONE, ZERO, ZERO); }
			inline static Vector3 YAxis() { return Vector3(ZERO, ONE, ZERO); }
			inline static Vector3 ZAxis() { return Vector3(ZERO, ZERO, ONE); }

			inline Vector3& Add(const Vector3& other) { x += other.x; y += other.y; z += other.z; return *this; }
			inline Vector3& Subtract(const Vector3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
			inline Vector3& Multiply(const Vector3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
			inline Vector3& Divide(const Vector3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

			inline Vector3& Add(Scalar other) { x += other; y += other; z += other; return *this; }
			inline Vector3& Subtract(Scalar other) { x -= other; y -= other; z -= other; return *this; }
			inline Vector3& Multiply(Scalar other) { x *= other; y *= other; z *= other; return *this; }
			inline Vector3& Divide(Scalar other) { x /= other; y /= other; z /= other; return *this; }

			inline static Vector3& Add(Vector3 left, const Vector3& right) { return left.Add(right); }
			inline static Vector3& Subtract(Vector3 left, const Vector3& right) { return left.Subtract(right); }
			inline static Vector3& Multiply(Vector3 left, const Vector3& right) { return left.Multiply(right); }
			inline static Vector3& Divide(Vector3 left, const Vector3& right) { return left.Divide(right); }

			inline static Vector3& Add(Vector3 left, Scalar right) { return left.Add(right); }
			inline static Vector3& Subtract(Vector3 left, Scalar right) { return left.Subtract(right); }
			inline static Vector3& Multiply(Vector3 left, Scalar right) { return left.Multiply(right); }
			inline static Vector3& Divide(Vector3 left, Scalar right) { return left.Divide(right); }

			inline friend Vector3 operator+(Vector3 left, const Vector3& right) { return left.Add(right); }
			inline friend Vector3 operator-(Vector3 left, const Vector3& right) { return left.Subtract(right); }
			inline friend Vector3 operator*(Vector3 left, const Vector3& right) { return left.Multiply(right); }
			inline friend Vector3 operator/(Vector3 left, const Vector3& right) { return left.Divide(right); }

			inline friend Vector3 operator+(Vector3 left, Scalar right) { return left.Add(right); }
			inline friend Vector3 operator-(Vector3 left, Scalar right) { return left.Subtract(right); }
			inline friend Vector3 operator*(Vector3 left, Scalar right) { return left.Multiply(right); }
			inline friend Vector3 operator/(Vector3 left, Scalar right) { return left.Divide(right); }

			inline Vector3& operator+=(const Vector3& other) { return Add(other); }
			inline Vector3& operator-=(const Vector3& other) { return Subtract(other); }
			inline Vector3& operator*=(const Vector3& other) { return Multiply(other); }
			inline Vector3& operator/=(const Vector3& other) { return Divide(other); }

			inline Vector3& operator+=(Scalar other) { return Add(other); }
			inline Vector3& operator-=(Scalar other) { return Subtract(other); }
			inline Vector3& operator*=(Scalar other) { return Multiply(other); }
			inline Vector3& operator/=(Scalar other) { return Divide(other); }

			inline bool operator<(const Vector3& other) const { return x < other.x && y < other.y && z < other.z; }
			inline bool operator<=(const Vector3& other) const { return x <= other.x && y <= other.y && z <= other.z; }
			inline bool operator>(const Vector3& other) const { return x > other.x && y > other.y && z > other.z; }
			inline bool operator>=(const Vector3& other) const { return x >= other.x && y >= other.y && z >= other.z; }
			inline bool operator==(const Vector3& other) const { return x == other.x && y == other.y && z == other.z; }
			inline bool operator!=(const Vector3& other) const { return !(*this == other); }

			//inline Vector3 operator-(const Vector3& Vector3tor) { return Vector3(-Vector3tor.x, -Vector3tor.y, -Vector3tor.z); }

			inline Vector3 Cross(const Vector3& other) const { return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }
			inline Scalar Dot(const Vector3& other) const { return x * other.x + y * other.y + z * other.z; }

			inline Scalar LengthSquared() const { return x * x + y * y + z * z; }

			inline static float Length(const Vector3& vec) { return (float)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z); }
			inline float Length() const { return (float)sqrt(x * x + y * y + z * z); }

			inline Vector3& Normalize() { return Divide((Scalar)Length()); }
			inline static Vector3 Normalize(Vector3& v) { return Divide(v, v.Length()); }

			inline float Distance(const Vector3& other) const { return Divide(*this, other).Length(); }

			inline friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector) { return stream << "Vector3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")"; }

			inline Scalar& operator[](byte x) { return components[x]; };
			inline const Scalar& operator[](byte x) const { return components[x]; };

			inline std::string ToString() const {
				std::stringstream ss; ss << x << ", " << y << ", " << z; return ss.str();
			}
		};
	}
}

#undef ZERO
#undef ONE