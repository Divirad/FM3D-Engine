#pragma once
#include <Engine.h>

namespace FM3D {
	namespace Math {

		template<uint R, uint C, typename Scalar>
		class Matrix {
			static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be an arithmetic type (int, float..)");
			static_assert((R * C) > 1U, "Matrix must have minimum 2 elements");
		public:
			union {
				float elements[R * C];
				Vector<C, Scalar> rows[R];
			};

			//Constructors
			Matrix(const Scalar* elements) {
				memcpy(this->elements, elements, R * C * sizeof(Scalar));
			}
			Matrix(const Vector<C, Scalar>* rows) {
				memcpy(this->rows, rows, R * C * sizeof(Scalar));
			}

			//Constant matrices
			static Matrix Null() {
				memset(elements, 0, R * C * sizeof(Scalar));
			}
			static Matrix Diagonal(Scalar scalar) {
				static_assert(R == C, "Matrix is not quadratic");
				memset(elements, 0, R * C * sizeof(Scalar));
				for (uint i = 0; i < R; i++) {
					elements[i + C * i] = scalar;
				}
			}
			static Matrix Identity() {
				static_assert(R == C, "Matrix is not quadratic");
				return Diagonal(1);
			}

			//Element access
			inline Scalar At(uint row, uint column) const {
				return elements[column + row * C];
			}
			inline const Vector<C, Scalar>& operator[](uint row) const {
				return rows[row];
			}

			//Member functions
			Matrix& Add(const Matrix& other) {
				for (uint i = 0; i < R * C; i++) {
					elements[i] += other.elements[i];
				}
				return *this;
			}
			Matrix& Multiply(Scalar scalar) {
				for (uint i = 0; i < R * C; i++) {
					elements[i] *= scalar;
				}
				return *this;
			}
			Matrix& Multiply(const Matrix& other) {
				float data[R * C];
				for (int row = 0; row < R; row++) {
					for (int col = 0; col < C; col++) {
						float sum = 0.0f;
						for (int e = 0; e < C; e++) {
							sum += elements[e + row * C] * other.elements[col + e * T];
						}
						data[col + row * C] = sum;
					}
				}
				memcpy(elements, data, R * C * sizeof(Scalar));
				return *this;
			}
			bool IsEqualTo(const Matrix& other) const {
				for (uint i = 0; i < R*T; i++) {
					if (elements[i] != other.elements[i]) return false;
				}
				return true;
			}
			bool IsUnequalTo(const Matrix& other) const {
				for (uint i = 0; i < R*T; i++) {
					if (elements[i] == other.elements[i]) return false;
				}
				return true;
			}

			//Static functions
			template<uint T>
			static Matrix<R, T, Scalar> Multiply(const Matrix<R, C, Scalar>& left, const Matrix<C, T, Scalar>& right) {
				float data[R * T];
				for (int row = 0; row < R; row++) {
					for (int col = 0; col < T; col++) {
						float sum = 0.0f;
						for (int e = 0; e < C; e++) {
							sum += left.elements[e + row * C] * right.elements[col + e * T];
						}
						data[col + row * T] = sum;
					}
				}
				return Matrix<R, T, Scalar>(data);
			}
			inline Matrix Add(Matrix left, const Matrix& right) { return left.Add(right); }
			static Vector<R, Scalar> Multiply(const Matrix<R, C, Scalar>& left, const Vector<C, Scalar>& right) {
				float data[R];
				for (int row = 0; row < R; row++) {
					float sum = 0.0f;
					for (int e = 0; e < C; e++) {
						sum += left.elements[e + row * C] * right[e];
					}
					data[row] = sum;
				}
				return Vector<R, Scalar>(data);
			}
			inline static Matrix Multiply(Matrix<R, C, Scalar> matrix, Scalar scalar) {
				return matrix.Multiply(scalar);
			}

			//Friend functions
			template<uint T>
			inline friend Matrix<R, T, Scalar> MultiplyMatrices(const Matrix<R, C, Scalar>& left, const Matrix<C, T, Scalar>& right) {
				return Matrix<R, C, Scalar>::Multiply(left, right);
			}
			inline friend Vector<R, Scalar> MultiplyMatrices(const Matrix<R, C, Scalar>& left, const Vector<C, Scalar>& right) {
				return Matrix<R, C, Scalar>::Multiply(left, right);
			}
			inline friend Matrix AddMatrices(Matrix left, const Matrix& right) { return left.Add(right); }
			inline friend Matrix Multiply(Matrix<R, C, Scalar> matrix, Scalar scalar) {
				return matrix.Multiply(scalar);
			}

			//Output
			static inline constexpr std::string Name() { return "Matrix " + std::to_string(R) + "x" + std::to_string(C); }
			friend std::ostream& operator<<(std::ostream& stream, const Matrix& matrix) {
#define width 12
				stream << "/";
				for (int c = 0; c < C; c++) {
					if (c != 0) stream << ", ";
					stream << std::setw(width) << matrix.elements[c + 0 * C];
				}
				stream << "\\" << std::endl;
				for (uint i = 1; i < R - 1; i++) {
					stream << "|";
					for (int c = 0; c < C; c++) {
						if (c != 0) stream << ", ";
						stream << std::setw(width) << matrix.elements[c + i * C];
					}
					stream << "|" << std::endl;
				}
				stream << "\\"; 
				for (int c = 0; c < C; c++) {
					if (c != 0) stream << ", ";
					stream << std::setw(width) << matrix.elements[c + (R-1) * C];
				}
				stream << "/" << std::endl;
#undef width
				return stream;
			}
		};


	}
}