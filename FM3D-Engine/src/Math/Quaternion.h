#pragma once
#include <Engine.h>

namespace FM3D {
	namespace Math {

		template<typename Scalar>
		class Quaternion {
		public:
			union {
				struct { Scalar w; Scalar x; Scalar y; Scalar z; };
				struct { Scalar scalar; Vector3<Scalar> vector; };
				struct { Scalar real; Vector3<Scalar> complex; };
				Scalar components[4];
			};

			//Constructor
			Quaternion(): w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
			Quaternion(Scalar w, Scalar x, Scalar y, Scalar z) : w(w), x(x), y(y), z(z) {}
			Quaternion(const Scalar* components) { memcpy(this->components, components, 4 * sizeof(Scalar)); }
			Quaternion(Scalar scalar, Vector3<Scalar> vector) : scalar(scalar), vector(vector) {}

			//Element access
			const Scalar& operator[](uint i) const { return components[i]; }
			Scalar& operator[](uint i) { return components[i]; }

			//Methods
			Quaternion& Add(const Quaternion& other) {
				x += other.x;
				y += other.y;
				z += other.z;
				w += other.w;
				return *this;
			}
			Quaternion& Subtract(const Quaternion& other) {
				x -= other.x;
				y -= other.y;
				z -= other.z;
				w -= other.w;
				return *this;
			}
			Quaternion& Multiply(Scalar scal) {
				x *= scal;
				y *= scal;
				z *= scal;
				w *= scal;
				return *this;
			}
			Quaternion& Multiply(const Quaternion& other) {
				Quaternion t(components);
				w = (t.w * other.w) - (t.x * other.x) - (t.y * other.y) - (t.z * other.z);
				x = (t.w * other.x) + (t.x * other.w) + (t.y * other.z) - (t.z * other.y);
				y = (t.w * other.y) - (t.x * other.z) + (t.y * other.w) + (t.z * other.x);
				z = (t.w * other.z) + (t.x * other.y) - (t.y * other.x) + (t.z * other.w);
				return *this;
			}
			inline Scalar LengthSquared() const { return x * x + y * y + z * z + w * w; }
			inline float Length() const { return std::sqrtf((float)LengthSquared()); }
			inline double LengthD() const { return std::sqrt((double)LengthSquared()); }
			inline Quaternion& Normalize() { return Multiply(1.0f / std::sqrtf((float)LengthSquared())); }
			Scalar Dot(const Quaternion& other) const {
				return (w * other.w) + (x * other.x) + (y * other.y) + (z * other.z);
			}
			Vector3f ToAngles() {
				double ysqr = y * y;

				double t0 = +2.0 * (w * x + y * z);
				double t1 = +1.0 - 2.0 * (x * x + ysqr);

				double t2 = +2.0 * (w * y - z * x);
				t2 = t2 > 1.0 ? 1.0 : t2;
				t2 = t2 < -1.0 ? -1.0 : t2;

				double t3 = +2.0 * (w * z + x *y);
				double t4 = +1.0 - 2.0 * (ysqr + z * z);

				return Vector3f(toDegrees(std::atan2(t0, t1)), toDegrees(std::asin(t2)), toDegrees(std::atan2(t3, t4)));
			}

			//Convert Methods
			Matrix44<Scalar> ToMatrix44() const {
				Scalar elements[16];
				elements[0 + 0 * 4] = 1 - (2 * y * y) - (2 * z * z);
				elements[0 + 1 * 4] = (2 * x * y) - (2 * w * z);
				elements[0 + 2 * 4] = (2 * x * z) + (2 * w * y);
				elements[0 + 3 * 4] = 0.0f;

				elements[1 + 0 * 4] = (2 * x * y) + (2 * w * z);
				elements[1 + 1 * 4] = 1 - (2 * x * x) - (2 * z * z);
				elements[1 + 2 * 4] = (2 * y * z) - (2 * w * x);
				elements[1 + 3 * 4] = 0.0f;

				elements[2 + 0 * 4] = (2 * x * z) - (2 * w * y);
				elements[2 + 1 * 4] = (2 * y * z) + (2 * w * x);
				elements[2 + 2 * 4] = 1 - (2 * x * x) - (2 * y * y);
				elements[2 + 3 * 4] = 0.0f;

				elements[3 + 0 * 4] = 0.0f;
				elements[3 + 1 * 4] = 0.0f;
				elements[3 + 2 * 4] = 0.0f;
				elements[3 + 3 * 4] = 1.0f;

				Matrix44<Scalar> result = Matrix44<Scalar>(elements);
				result.Transpose();
				return result;
			}
			Matrix34<Scalar> ToMatrix34() const {
				Scalar elements[12];
				elements[0 + 0 * 4] = 1 - (2 * y * y) - (2 * z * z);
				elements[0 + 1 * 4] = (2 * x * y) - (2 * w * z);
				elements[0 + 2 * 4] = (2 * x * z) + (2 * w * y);
				elements[0 + 3 * 4] = 0.0f;

				elements[1 + 0 * 4] = (2 * x * y) + (2 * w * z);
				elements[1 + 1 * 4] = 1 - (2 * x * x) - (2 * z * z);
				elements[1 + 2 * 4] = (2 * y * z) - (2 * w * x);
				elements[1 + 3 * 4] = 0.0f;

				elements[2 + 0 * 4] = (2 * x * z) - (2 * w * y);
				elements[2 + 1 * 4] = (2 * y * z) + (2 * w * x);
				elements[2 + 2 * 4] = 1 - (2 * x * x) - (2 * y * y);
				elements[2 + 3 * 4] = 0.0f;
				return Matrix34<Scalar>(elements);
			}
			Matrix33<Scalar> ToMatrix33() const {
				Scalar elements[9];
				elements[0 + 0 * 3] = 1 - (2 * y * y) - (2 * z * z);
				elements[0 + 1 * 3] = (2 * x * y) - (2 * w * z);
				elements[0 + 2 * 3] = (2 * x * z) + (2 * w * y);

				elements[1 + 0 * 3] = (2 * x * y) + (2 * w * z);
				elements[1 + 1 * 3] = 1 - (2 * x * x) - (2 * z * z);
				elements[1 + 2 * 3] = (2 * y * z) - (2 * w * x);

				elements[2 + 0 * 3] = (2 * x * z) - (2 * w * y);
				elements[2 + 1 * 3] = (2 * y * z) + (2 * w * x);
				elements[2 + 2 * 3] = 1 - (2 * x * x) - (2 * y * y);
				return Matrix33<Scalar>(elements);
			}

			//Static Methods
			static inline Quaternion RotationX(Scalar angle) { return RotationXR(toRadians(angle)); }
			static inline Quaternion RotationY(Scalar angle) { return RotationYR(toRadians(angle)); }
			static inline Quaternion RotationZ(Scalar angle) { return RotationZR(toRadians(angle)); }
			static inline Quaternion RotationXR(Scalar angle) { return Quaternion(cos(angle * 0.5f), sin(angle * 0.5f), 0.0f, 0.0f); }
			static inline Quaternion RotationYR(Scalar angle) { return Quaternion(cos(angle * 0.5f), 0.0f, sin(angle * 0.5f), 0.0f); }
			static inline Quaternion RotationZR(Scalar angle) { return Quaternion(cos(angle * 0.5f), 0.0f, 0.0f, sin(angle * 0.5f)); }

			static inline Quaternion Rotation(Scalar angleX, Scalar angleY, Scalar angleZ) { 
				return RotationR(toRadians(angleX), toRadians(angleY), toRadians(angleZ));
			}
			static inline Quaternion RotationR(Scalar angleX, Scalar angleY, Scalar angleZ) {
				angleX *= 0.5f;
				angleY *= 0.5f;
				angleZ *= 0.5f;

				float xc = std::cos(angleX);
				float xs = std::sin(angleX);
				float yc = std::cos(angleY);
				float ys = std::sin(angleY);
				float zc = std::cos(angleZ);
				float zs = std::sin(angleZ);

				return Quaternion(
					zc * xc * yc + zs * xs * ys,
				    zc * xs * yc - zs * xc * ys,
				    zc * xc * ys + zs * xs * yc,
				    zs * xc * yc - zc * xs * ys
				);
			}

			static Quaternion Slerp(Quaternion v0, Quaternion v1, float t) {
				//spherical linear interpolation
				v0.Normalize();
				v1.Normalize();

				float dot = v0.Dot(v1);

				const float DOT_THRESHOLD = 0.9995f;
				if (dot > DOT_THRESHOLD) {
					// Quaternions are too close
					// linear interpolation
					return (v0 + t * (v1 - v0)).Normalize();
				}

				if (dot < 0.0f) {
					v1 *= -1.0f;
					dot = -dot;
				}
				if (dot > 1.0f) {
					dot = 1.0f;
				}
				float theta = acosf(dot);
				theta *= t;

				Quaternion v2 = v1 - (v0 * dot);
				v2.Normalize();

				return v0*cosf(theta) + v2*sinf(theta);
			}
			static Quaternion FromMatrix(Matrix4<Scalar> m) {
				m.Transpose();
				float trace = m.elements[0 + 0 * 4] + m.elements[1 + 1 * 4] + m.elements[2 + 2 * 4];
				if (trace > 0) {
					float s = 0.5f / sqrtf(trace + 1.0f);
					return Quaternion(
						0.25f / s,
						(m.elements[2 + 1 * 4] - m.elements[1 + 2 * 4]) * s,
						(m.elements[0 + 2 * 4] - m.elements[2 + 0 * 4]) * s,
						(m.elements[1 + 0 * 4] - m.elements[0 + 1 * 4]) * s
					);
				}
				else {
					if (m.elements[0 + 0 * 4] > m.elements[1 + 1 * 4] && m.elements[0 + 0 * 4] > m.elements[2 + 2 * 4]) {
						float s = 2.0f * sqrtf(1.0f + m.elements[0 + 0 * 4] - m.elements[1 + 1 * 4] - m.elements[2 + 2 * 4]);
						return Quaternion(
							(m.elements[2 + 1 * 4] - m.elements[1 + 2 * 4]) / s,
							0.25f * s,
							(m.elements[0 + 1 * 4] + m.elements[1 + 0 * 4]) / s,
							(m.elements[0 + 2 * 4] + m.elements[2 + 0 * 4]) / s
						);
					}
					else if (m.elements[1 + 1 * 4] > m.elements[2 + 2 * 4]) {
						float s = 2.0f * sqrtf(1.0f + m.elements[1 + 1 * 4] - m.elements[0 + 0 * 4] - m.elements[2 + 2 * 4]);
						return Quaternionf(
							(m.elements[0 + 2 * 4] - m.elements[2 + 0 * 4]) / s,
							(m.elements[0 + 1 * 4] + m.elements[1 + 0 * 4]) / s,
							0.25f * s,
							(m.elements[1 + 2 * 4] + m.elements[2 + 1 * 4]) / s
						);
					}
					else {
						float s = 2.0f * sqrtf(1.0f + m.elements[2 + 2 * 4] - m.elements[0 + 0 * 4] - m.elements[1 + 1 * 4]);
						return Quaternionf(
							(m.elements[1 + 0 * 4] - m.elements[0 + 1 * 4]) / s,
							(m.elements[0 + 2 * 4] + m.elements[2 + 0 * 4]) / s,
							(m.elements[1 + 2 * 4] + m.elements[2 + 1 * 4]) / s,
							0.25f * s
						);
					}
				}
			}

			//Member operators
			inline Quaternion& operator+=(const Quaternion& right) { return Add(right); }
			inline Quaternion& operator-=(const Quaternion& right) { return Subtract(right); }
			inline Quaternion& operator*=(const Quaternion& right) { return Multiply(right); }
			inline Quaternion& operator*=(Scalar right) { return Multiply(right); }

			//Static operators
			inline friend Quaternion operator+(Quaternion left, const Quaternion& right) { return left.Add(right); }
			inline friend Quaternion operator-(Quaternion left, const Quaternion& right) { return left.Subtract(right); }
			inline friend Quaternion operator*(Quaternion left, const Quaternion& right) { return left.Multiply(right); }
			inline friend Quaternion operator*(Quaternion left, Scalar right) { return left.Multiply(right); }
			inline friend Quaternion operator*(Scalar left,  Quaternion right) { return right.Multiply(left); }

			//Output
			std::string ToString() const {
				std::stringstream ss;
				ss << "(" << w << " + " << x << "i + " << y << "j + " << z << "k)";
				return ss.str();
			}
			friend std::ostream& operator<<(std::ostream& stream, const Quaternion& quad) {
				return stream << "(" << quad.w << " + " << quad.x << "i + " << quad.y << "j + " << quad.z << "k)";
			}
		};
	}
}