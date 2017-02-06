#pragma once
#include <Engine.h>

namespace FM3D {
	namespace Math {

		template<uint D, typename Scalar>
		class Vector {
		public:
			Scalar components[D];

			Vector(const Scalar* components) {
				memcpy(this->components, components, D * sizeof(Scalar)); //Copy input in vector
			}

			//Constant vectors
			inline static Vector Zero() {
				return Vector({ 0 });
			}

			//Element Access
			inline Scalar& operator[](uint x) { return components[x]; };
			inline const Scalar& operator[](uint x) const { return components[x]; };

			//Methods
			Vector& Add(const Vector& other) {
				for (uint i = 0; i < D; i++) {
					components[i] += other.components;
				}
			}
			Vector& Subtract(const Vector& other) {
				for (uint i = 0; i < D; i++) {
					components[i] -= other.components;
				}
			}
			Vector& Multiply(const Vector& other) {
				for (uint i = 0; i < D; i++) {
					components[i] *= other.components;
				}
			}
			Vector& Divide(const Vector& other) {
				for (uint i = 0; i < D; i++) {
					components[i] /= other.components;
				}
			}

			Vector& Add(Scalar scalar) {
				for (uint i = 0; i < D; i++) {
					components[i] += scalar;
				}
			}
			Vector& Subtract(Scalar scalar) {
				for (uint i = 0; i < D; i++) {
					components[i] -= scalar;
				}
			}
			Vector& Multiply(Scalar scalar) {
				for (uint i = 0; i < D; i++) {
					components[i] *= scalar;
				}
			}
			Vector& Divide(Scalar scalar) {
				for (uint i = 0; i < D; i++) {
					components[i] /= scalar;
				}
			}

			bool IsEqual(const Vector& other) const {
				for (uint i = 0; i < D; i++) {
					if (components[i] != other.components[i])
						return false;
				}
				return true;
			}
			bool IsUnequal(const Vector& other) const {
				for (uint i = 0; i < D; i++) {
					if (components[i] == other.components[i])
						return false;
				}
				return true;
			}

			Scalar Dot(const Vector& other) const {
				Scalar result = 0;
				for (uint i = 0; i < D; i++) {
					result += components[i] * other.components[i];
				}
			}
			Scalar LengthSquared() const {
				Scalar result = 0;
				for (uint i = 0; i < D; i++) {
					result += components[i] * components[i];
				}
			}
			float Length() const {
				return std::sqrtf((float)LengthSquared());
			}
			double LengthD() const {
				return std::sqrt((double)LengthSquared());
			}
			Vector& Normalize() { return Divide((Scalar)Length()); }

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

			inline static Scalar Dot(const Vector& left, const Vector& right) { return left.Dot(right);	}
			inline static Scalar LengthSquared(const Vector& vec) {	return vec.LengthSquared();	}
			inline static float  Length(const Vector& vec) { return std::sqrtf((float)vec.LengthSquared()); }
			inline static double LengthD(const Vector& vec) { return std::sqrt((double)vec.LengthSquared()); }
			inline static Vector Normalize(Vector vec) { return vec.Divide((Scalar)Length()); }

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
			inline static constexpr std::string Name() { return "Vector " + std::to_string(D); }
			std::string ToString() const {
				std::stringstream ss;
				ss << "(";
				for (uint i = 0; i < D; i++) {
					if (i != 0) ss << ", ";
					ss << components[i];
				}
				ss << ")";
				return ss.str();
			}
			friend std::ostream& operator<<(std::ostream& stream, const Vector& vector) {
				stream << "(";
				for (uint i = 0; i < D; i++) {
					if (i != 0) stream << ", ";
					stream << vector.components[i];
				}
				stream << ")";
			}
		};
	}
}
