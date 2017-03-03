#pragma once
#include <Engine.h>

namespace FM3D {
	namespace Math {

		template<typename Scalar>
		class Matrix<2U, 2U, Scalar> {
			static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be an arithmetic type (int, float..)");
		public:
			union {
				float elements[2 * 2];
				Vector<2, Scalar> rows[2];
			};

			//2onstructors
			Matrix(const Scalar* elements) {
				memcpy(this->elements, elements, 2 * 2 * sizeof(Scalar));
			}
			Matrix(const Vector<2, Scalar>* rows) {
				memcpy(this->rows, rows, 2 * 2 * sizeof(Scalar));
			}

			//2onstant matrices
			static Matrix Null() {
				memset(elements, 0, 2 * 2 * sizeof(Scalar));
			}
			static Matrix Diagonal(Scalar scalar) {
				static_assert(2 == 2, "Matrix is not quadratic");
				memset(elements, 0, 2 * 2 * sizeof(Scalar));
				for (uint i = 0; i < 2; i++) {
					elements[i + 2 * i] = scalar;
				}
			}
			static Matrix Identity() {
				static_assert(2 == 2, "Matrix is not quadratic");
				return Diagonal(1);
			}

			//Element access
			inline Scalar At(uint row, uint column) const {
				return elements[column + row * 2];
			}
			inline const Vector<2, Scalar>& operator[](uint row) const {
				return rows[row];
			}

			//Member functions
			Matrix& Add(const Matrix& other) {
				for (uint i = 0; i < 2 * 2; i++) {
					elements[i] += other.elements[i];
				}
				return *this;
			}
			Matrix& Multiply(Scalar scalar) {
				for (uint i = 0; i < 2 * 2; i++) {
					elements[i] *= scalar;
				}
				return *this;
			}
			Matrix& Multiply(const Matrix& other) {
				float data[2 * 2];
				for (int row = 0; row < 2; row++) {
					for (int col = 0; col < 2; col++) {
						float sum = 0.0f;
						for (int e = 0; e < 2; e++) {
							sum += elements[e + row * 2] * other.elements[col + e * T];
						}
						data[col + row * 2] = sum;
					}
				}
				memcpy(elements, data, 2 * 2 * sizeof(Scalar));
				return *this;
			}
			bool IsEqualTo(const Matrix& other) const {
				for (uint i = 0; i < 2*T; i++) {
					if (elements[i] != other.elements[i]) return false;
				}
				return true;
			}
			bool IsUnequalTo(const Matrix& other) const {
				for (uint i = 0; i < 2*T; i++) {
					if (elements[i] == other.elements[i]) return false;
				}
				return true;
			}

			//Static functions
			template<uint T>
			static Matrix<2, T, Scalar> Multiply(const Matrix<2, 2, Scalar>& left, const Matrix<2, T, Scalar>& right) {
				float data[2 * T];
				for (int row = 0; row < 2; row++) {
					for (int col = 0; col < T; col++) {
						float sum = 0.0f;
						for (int e = 0; e < 2; e++) {
							sum += left.elements[e + row * 2] * right.elements[col + e * T];
						}
						data[col + row * T] = sum;
					}
				}
				return Matrix<2, T, Scalar>(data);
			}
			inline Matrix Add(Matrix left, const Matrix& right) { return left.Add(right); }
			static Vector<2, Scalar> Multiply(const Matrix<2, 2, Scalar>& left, const Vector<2, Scalar>& right) {
				float data[2];
				for (int row = 0; row < 2; row++) {
					float sum = 0.0f;
					for (int e = 0; e < 2; e++) {
						sum += left.elements[e + row * 2] * right[e];
					}
					data[row] = sum;
				}
				return Vector<2, Scalar>(data);
			}
			inline static Matrix Multiply(Matrix<2, 2, Scalar> matrix, Scalar scalar) {
				return matrix.Multiply(scalar);
			}
			inline static Matrix Rotation(float angle) {
				return Rotation(toRadians(angle));
			}
			static Matrix RotationR(float angle) {
				float c = cos(angle);
				float s = sin(angle);
				return Matrix(float[4]{ c, s, -s, c });
			}

			//Member operators
			inline Matrix& operator+=(const Matrix& other) { return Add(other); }
			inline Matrix& operator*(Scalar scalar) { return Multiply(scalar); }
			inline Matrix& operator*(const Matrix& other) { return Multiply(other); }
			inline bool operator==(const Matrix& other) const { return IsEqualTo(other); }
			inline bool operator!=(const Matrix& other) const { return other.IsUnequalTo(other); }

			//Static operators
			template<uint T>
			inline friend Matrix<2, T, Scalar> operator*(const Matrix<2, 2, Scalar>& left, const Matrix<2, T, Scalar>& right) {
				return Matrix<2, 2, Scalar>::Multiply(left, right);
			}
			inline friend Vector<2, Scalar> operator*(const Matrix<2, 2, Scalar>& left, const Vector<2, Scalar>& right) {
				return Matrix<2, 2, Scalar>::Multiply(left, right);
			}
			inline friend Matrix operator+(Matrix left, const Matrix& right) { return left.Add(right); }
			inline friend Matrix operator*(Matrix<2, 2, Scalar> matrix, Scalar scalar) {
				return matrix.Multiply(scalar);
			}

			//Output
			static inline constexpr std::string Name() { return "Matrix " + std::to_string(2) + "x" + std::to_string(2); }
			friend std::ostream& operator<<(std::ostream& stream, const Matrix& matrix) {
#define width 12
				stream << "/";
				for (int c = 0; c < 2; c++) {
					if (c != 0) stream << ", ";
					stream << std::setw(width) << matrix.elements[c + 0 * 2];
				}
				stream << "\\" << std::endl;
				for (uint i = 1; i < 2 - 1; i++) {
					stream << "|";
					for (int c = 0; c < 2; c++) {
						if (c != 0) stream << ", ";
						stream << std::setw(width) << matrix.elements[c + i * 2];
					}
					stream << "|" << std::endl;
				}
				stream << "\\";
				for (int c = 0; c < 2; c++) {
					if (c != 0) stream << ", ";
					stream << std::setw(width) << matrix.elements[c + (2 - 1) * 2];
				}
				stream << "/" << std::endl;
#undef width
				return stream;
			}
		};


	}
}