#pragma once
#include <Engine.h>

namespace FM3D {
	namespace Math {

		template<typename Scalar>
		class Vector<3U, Scalar> {
			static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be an arithmetic type (int, float..)");
		public:
			union {
				struct { Scalar x; Scalar y; Scalar z; };
				struct { Vector<2U, Scalar> xy; Scalar z; };
				Scalar components[3];
			};

			Vector(Scalar x, Scalar y, Scalar z) : x(x), y(y), z(z) {}
			Vector(const Vector<2U, Scalar>& xy, Scalar z) : xy(xy), z(z) {}
			Vector(const Scalar* components) {
				memcpy(this->components, components, 3); //Copy input in vector
			}

			//Constant vectors
			inline static Vector Zero() { return Vector(0, 0, 0); }
			inline static Vector XAxis() { return Vector(1, 0, 0); }
			inline static Vector YAxis() { return Vector(0, 1, 0); }
			inline static Vector ZAxis() { return Vector(0, 0, 1); }

			//Element Access
			inline Scalar& operator[](uint x) { return components[x]; };
			inline const Scalar& operator[](uint x) const { return components[x]; };

			//Methods
			inline Vector& Add(const Vector& other) { x += other.x; y += other.y; z += other.z; return *this; }
			inline Vector& Subtract(const Vector& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
			inline Vector& Multiply(const Vector& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
			inline Vector& Divide(const Vector& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

			inline Vector& Add(Scalar scalar) { x += scalar; y += scalar; z += scalar; return *this; }
			inline Vector& Subtract(Scalar scalar) { x -= scalar; y -= scalar; z -= scalar; return *this; }
			inline Vector& Multiply(Scalar scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
			inline Vector& Divide(Scalar scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

			inline bool IsEqual(const Vector& other) const { return x == other.x && y == other.y && z == other.z; }
			inline bool IsUnequal(const Vector& other) const { return x != other.x && y != other.y && z != other.z; }

			inline Scalar Dot(const Vector& other) const { return x * other.x + y * other.y + z * other.z; }
			inline Scalar LengthSquared() const { return x * x + y * y + z * z; }
			inline float Length() const { return std::sqrtf((float)LengthSquared()); }
			inline double LengthD() const { return std::sqrt((double)LengthSquared()); }
			inline Vector& Normalize() { return Divide((Scalar)Length()); }
			inline Vector& Cross(const Vector& other) { return  x = y * other.z - z * other.y; y = z * other.x - x * other.z; z = x * other.y - y * other.x; }

			//Member operators
			inline Vector& operator+=(const Vector& other) { return Add(other); }
			inline Vector& operator-=(const Vector& other) { return Subtract(other); }
			inline Vector& operator*=(const Vector& other) { return Multiply(other); }
			inline Vector& operator/=(const Vector& other) { return Divide(other); }

			inline Vector& operator+=(Scalar other) { return Add(other); }
			inline Vector& operator-=(Scalar other) { return Subtract(other); }
			inline Vector& operator*=(Scalar other) { return Multiply(other); }
			inline Vector& operator/=(Scalar other) { return Divide(other); }

			inline bool operator==(const Vector& other) const { return IsEqual(other); }
			inline bool operator!=(const Vector& other) const { return IsUnequal(other); }

			//Static methods
			inline static Vector Add(Vector left, const Vector& right) { return left.Add(right); }
			inline static Vector Subtract(Vector left, const Vector& right) { return left.Subtract(right); }
			inline static Vector Multiply(Vector left, const Vector& right) { return left.Multiply(right); }
			inline static Vector Divide(Vector left, const Vector& right) { return left.Divide(right); }

			inline static Vector Add(Vector left, Scalar right) { return left.Add(right); }
			inline static Vector Subtract(Vector left, Scalar right) { return left.Subtract(right); }
			inline static Vector Multiply(Vector left, Scalar right) { return left.Multiply(right); }
			inline static Vector Divide(Vector left, Scalar right) { return left.Divide(right); }

			inline static Scalar Dot(const Vector& left, const Vector& right) { return left.Dot(right); }
			inline static Scalar LengthSquared(const Vector& vec) { return vec.LengthSquared(); }
			inline static float  Length(const Vector& vec) { return std::sqrtf((float)vec.LengthSquared()); }
			inline static double LengthD(const Vector& vec) { return std::sqrt((double)vec.LengthSquared()); }
			inline static Vector Normalize(Vector vec) { return vec.Divide((Scalar)Length()); }
			inline static Vector Cross(Vector left, const Vector& right) { return left.Cross(); }

			//Static operators
			inline friend Vector operator+(Vector left, const Vector& right) { return left.Add(right); }
			inline friend Vector operator-(Vector left, const Vector& right) { return left.Subtract(right); }
			inline friend Vector operator*(Vector left, const Vector& right) { return left.Multiply(right); }
			inline friend Vector operator/(Vector left, const Vector& right) { return left.Divide(right); }

			inline friend Vector operator+(Vector left, Scalar right) { return left.Add(right); }
			inline friend Vector operator-(Vector left, Scalar right) { return left.Subtract(right); }
			inline friend Vector operator*(Vector left, Scalar right) { return left.Multiply(right); }
			inline friend Vector operator/(Vector left, Scalar right) { return left.Divide(right); }

			//Output - Not optimized for performance
			inline static constexpr std::string Name() { return "Vector 3"; }
			inline std::string ToString() const {
				std::stringstream ss;
				ss << "(" << x << ", " << y << ", " << z << ")";
				return ss.str();
			}
			inline friend std::ostream& operator<<(std::ostream& stream, const Vector& vector) {
				return stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			}
		};
	}
}
