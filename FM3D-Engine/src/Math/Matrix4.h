#pragma once
#include <Engine.h>

namespace FM3D {
	namespace Math {

		template<typename Scalar>
		class Matrix<4U, 4U, Scalar> {
			static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be an arithmetic type (int, float..)");
		public:
			union {
				float elements[16];
				Vector4<Scalar> rows[4];
			};

			//Constructors
			Matrix(const Scalar* elements) {
				memcpy(this->elements, elements, 16 * sizeof(Scalar));
			}
			Matrix(const Vector<4, Scalar>* rows) {
				memcpy(this->rows, rows, 16 * sizeof(Scalar));
			}
			Matrix(const Vector4<Scalar>& row0, const Vector4<Scalar>& row1, const Vector4<Scalar>& row2, const Vector4<Scalar>& row3) {
				rows[0] = row0; rows[1] = row1; rows[2] = row2; rows[3] = row3;
			}

			//Constant matrices
			static Matrix Null() {
				float elements[16];
				memset(elements, 0, 16 * sizeof(Scalar));
				return Matrix(elements);
			}
			static Matrix Diagonal(Scalar scalar) {
				float elements[16];
				memset(elements, 0, 16 * sizeof(Scalar));
				elements[0 + 0 * 4] = scalar;
				elements[1 + 1 * 4] = scalar;
				elements[2 + 2 * 4] = scalar;
				elements[3 + 3 * 4] = scalar;
				return Matrix(elements);
			}
			static Matrix Identity() {
				float elements[16];
				memset(elements, 0, 16 * sizeof(Scalar));
				elements[0 + 0 * 4] = 1.0f;
				elements[1 + 1 * 4] = 1.0f;
				elements[2 + 2 * 4] = 1.0f;
				elements[3 + 3 * 4] = 1.0f;
				return Matrix(elements);
			}

			//Element access
			inline Scalar At(uint row, uint column) const {
				return elements[column + row * 4];
			}
			inline const Vector4<Scalar>& operator[](uint row) const {
				return rows[row];
			}
			inline Vector4<Scalar> GetColumn(int index) const {
				return Vector4<Scalar>(elements[index + 0 * 4], elements[index + 1 * 4], elements[index + 2 * 4], elements[index + 3 * 4]);
			}


			//Member functions
			Matrix& Add(const Matrix& other) {
				for (uint i = 0; i < 16; i++) {
					elements[i] += other.elements[i];
				}
				return *this;
			}
			Matrix& Multiply(Scalar scalar) {
				for (uint i = 0; i < 16; i++) {
					elements[i] *= scalar;
				}
				return *this;
			}
			Matrix& Multiply(const Matrix& other) {
				float data[16];
				for (int row = 0; row < 4; row++) {
					for (int col = 0; col < 4; col++) {
						float sum = 0.0f;
						for (int e = 0; e < 4; e++) {
							sum += elements[e + row * 4] * other.elements[col + e * 4];
						}
						data[col + row * 4] = sum;
					}
				}
				memcpy(elements, data, 16 * sizeof(Scalar));
				return *this;
			}
			Matrix& Invert() {
				Scalar temp[16];

				temp[0] = elements[5] * elements[10] * elements[15] -
					elements[5] * elements[11] * elements[14] -
					elements[9] * elements[6] * elements[15] +
					elements[9] * elements[7] * elements[14] +
					elements[13] * elements[6] * elements[11] -
					elements[13] * elements[7] * elements[10];

				temp[4] = -elements[4] * elements[10] * elements[15] +
					elements[4] * elements[11] * elements[14] +
					elements[8] * elements[6] * elements[15] -
					elements[8] * elements[7] * elements[14] -
					elements[12] * elements[6] * elements[11] +
					elements[12] * elements[7] * elements[10];

				temp[8] = elements[4] * elements[9] * elements[15] -
					elements[4] * elements[11] * elements[13] -
					elements[8] * elements[5] * elements[15] +
					elements[8] * elements[7] * elements[13] +
					elements[12] * elements[5] * elements[11] -
					elements[12] * elements[7] * elements[9];

				temp[12] = -elements[4] * elements[9] * elements[14] +
					elements[4] * elements[10] * elements[13] +
					elements[8] * elements[5] * elements[14] -
					elements[8] * elements[6] * elements[13] -
					elements[12] * elements[5] * elements[10] +
					elements[12] * elements[6] * elements[9];

				temp[1] = -elements[1] * elements[10] * elements[15] +
					elements[1] * elements[11] * elements[14] +
					elements[9] * elements[2] * elements[15] -
					elements[9] * elements[3] * elements[14] -
					elements[13] * elements[2] * elements[11] +
					elements[13] * elements[3] * elements[10];

				temp[5] = elements[0] * elements[10] * elements[15] -
					elements[0] * elements[11] * elements[14] -
					elements[8] * elements[2] * elements[15] +
					elements[8] * elements[3] * elements[14] +
					elements[12] * elements[2] * elements[11] -
					elements[12] * elements[3] * elements[10];

				temp[9] = -elements[0] * elements[9] * elements[15] +
					elements[0] * elements[11] * elements[13] +
					elements[8] * elements[1] * elements[15] -
					elements[8] * elements[3] * elements[13] -
					elements[12] * elements[1] * elements[11] +
					elements[12] * elements[3] * elements[9];

				temp[13] = elements[0] * elements[9] * elements[14] -
					elements[0] * elements[10] * elements[13] -
					elements[8] * elements[1] * elements[14] +
					elements[8] * elements[2] * elements[13] +
					elements[12] * elements[1] * elements[10] -
					elements[12] * elements[2] * elements[9];

				temp[2] = elements[1] * elements[6] * elements[15] -
					elements[1] * elements[7] * elements[14] -
					elements[5] * elements[2] * elements[15] +
					elements[5] * elements[3] * elements[14] +
					elements[13] * elements[2] * elements[7] -
					elements[13] * elements[3] * elements[6];

				temp[6] = -elements[0] * elements[6] * elements[15] +
					elements[0] * elements[7] * elements[14] +
					elements[4] * elements[2] * elements[15] -
					elements[4] * elements[3] * elements[14] -
					elements[12] * elements[2] * elements[7] +
					elements[12] * elements[3] * elements[6];

				temp[10] = elements[0] * elements[5] * elements[15] -
					elements[0] * elements[7] * elements[13] -
					elements[4] * elements[1] * elements[15] +
					elements[4] * elements[3] * elements[13] +
					elements[12] * elements[1] * elements[7] -
					elements[12] * elements[3] * elements[5];

				temp[14] = -elements[0] * elements[5] * elements[14] +
					elements[0] * elements[6] * elements[13] +
					elements[4] * elements[1] * elements[14] -
					elements[4] * elements[2] * elements[13] -
					elements[12] * elements[1] * elements[6] +
					elements[12] * elements[2] * elements[5];

				temp[3] = -elements[1] * elements[6] * elements[11] +
					elements[1] * elements[7] * elements[10] +
					elements[5] * elements[2] * elements[11] -
					elements[5] * elements[3] * elements[10] -
					elements[9] * elements[2] * elements[7] +
					elements[9] * elements[3] * elements[6];

				temp[7] = elements[0] * elements[6] * elements[11] -
					elements[0] * elements[7] * elements[10] -
					elements[4] * elements[2] * elements[11] +
					elements[4] * elements[3] * elements[10] +
					elements[8] * elements[2] * elements[7] -
					elements[8] * elements[3] * elements[6];

				temp[11] = -elements[0] * elements[5] * elements[11] +
					elements[0] * elements[7] * elements[9] +
					elements[4] * elements[1] * elements[11] -
					elements[4] * elements[3] * elements[9] -
					elements[8] * elements[1] * elements[7] +
					elements[8] * elements[3] * elements[5];

				temp[15] = elements[0] * elements[5] * elements[10] -
					elements[0] * elements[6] * elements[9] -
					elements[4] * elements[1] * elements[10] +
					elements[4] * elements[2] * elements[9] +
					elements[8] * elements[1] * elements[6] -
					elements[8] * elements[2] * elements[5];

				float determinant = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];
				determinant = 1.0f / determinant;

				for (int i = 0; i < 4 * 4; i++)
					elements[i] = temp[i] * determinant;

				return *this;
			}
			Matrix& Transpose() {
				Matrix copy(elements);
				rows[0].x = copy.rows[0].x;
				rows[0].y = copy.rows[1].x;
				rows[0].z = copy.rows[2].x;
				rows[0].w = copy.rows[3].x;

				rows[1].x = copy.rows[0].y;
				rows[1].y = copy.rows[1].y;
				rows[1].z = copy.rows[2].y;
				rows[1].w = copy.rows[3].y;

				rows[2].x = copy.rows[0].z;
				rows[2].y = copy.rows[1].z;
				rows[2].z = copy.rows[2].z;
				rows[2].w = copy.rows[3].z;

				rows[3].x = copy.rows[0].w;
				rows[3].y = copy.rows[1].w;
				rows[3].z = copy.rows[2].w;
				rows[3].w = copy.rows[3].w;

				return *this;
			}
			bool IsEqualTo(const Matrix& other) const {
				for (uint i = 0; i < 16; i++) {
					if (elements[i] != other.elements[i]) return false;
				}
				return true;
			}
			bool IsUnequalTo(const Matrix& other) const {
				for (uint i = 0; i < 16; i++) {
					if (elements[i] == other.elements[i]) return false;
				}
				return true;
			}

			//Static functions
			static Matrix Multiply(const Matrix& left, const Matrix& right) {
				float data[16];
				for (int row = 0; row < 4; row++) {
					for (int col = 0; col < 4; col++) {
						float sum = 0.0f;
						for (int e = 0; e < 4; e++) {
							sum += left.elements[e + row * 4] * right.elements[col + e * 4];
						}
						data[col + row * 4] = sum;
					}
				}
				return Matrix(data);
			}
			inline Matrix Add(Matrix left, const Matrix& right) { return left.Add(right); }
			static Vector4<Scalar> Multiply(const Matrix& left, const Vector4<Scalar>& right) {
				return Vector4<Scalar>(
					left.rows[0].x * right.x + left.rows[0].y * right.y + left.rows[0].z * right.z + left.rows[0].w * right.w,
					left.rows[1].x * right.x + left.rows[1].y * right.y + left.rows[1].z * right.z + left.rows[1].w * right.w,
					left.rows[2].x * right.x + left.rows[2].y * right.y + left.rows[2].z * right.z + left.rows[2].w * right.w,
					left.rows[3].x * right.x + left.rows[3].y * right.y + left.rows[3].z * right.z + left.rows[3].w * right.w
				);
			}
			static Vector3<Scalar> Multiply(const Matrix& left, const Vector3<Scalar>& right) {
				return Vector3<Scalar>(
					left.rows[0].x * right.x + left.rows[0].y * right.y + left.rows[0].z * right.z + left.rows[0].w,
					left.rows[1].x * right.x + left.rows[1].y * right.y + left.rows[1].z * right.z + left.rows[1].w,
					left.rows[2].x * right.x + left.rows[2].y * right.y + left.rows[2].z * right.z + left.rows[2].w
					);
			}
			inline static Matrix Multiply(Matrix matrix, Scalar scalar) {
				return matrix.Multiply(scalar);
			}
			static Matrix Invert(const Matrix& matrix) {
				Matrix result = matrix;
				return result.Invert();
			}
			static Matrix Transpose(const Matrix& matrix) {
				return Matrix(
					Vector4f(matrix.rows[0].x, matrix.rows[1].x, matrix.rows[2].x, matrix.rows[3].x),
					Vector4f(matrix.rows[0].y, matrix.rows[1].y, matrix.rows[2].y, matrix.rows[3].y),
					Vector4f(matrix.rows[0].z, matrix.rows[1].z, matrix.rows[2].z, matrix.rows[3].z),
					Vector4f(matrix.rows[0].w, matrix.rows[1].w, matrix.rows[2].w, matrix.rows[3].w)
				);
			}

			//Member operators
			inline Matrix& operator+=(const Matrix& other) { return Add(other); }
			inline Matrix& operator*=(Scalar scalar) { return Multiply(scalar); }
			inline Matrix& operator*=(const Matrix& other) { return Multiply(other); }

			//Static operators
			inline friend Matrix operator*(const Matrix& left, const Matrix& right) { return Multiply(left, right); }
			inline friend Matrix operator+(Matrix left, const Matrix& right) { return left.Add(right); }
			inline friend Vector4<Scalar> operator*(const Matrix& left, const Vector4<Scalar>& right) { return Multiply(left, right); }
			inline friend Vector3<Scalar> operator*(const Matrix& left, const Vector3<Scalar>& right) { return Multiply(left, right); }
			inline friend Matrix operator*(Matrix matrix, Scalar scalar) { return Multiply(matrix, scalar); }
			inline friend Vector4<Scalar>& operator *=(Vector4<Scalar>& vec, const Matrix& matrix) {
				vec.x = matrix.rows[0].x * vec.x + matrix.rows[0].y * vec.y + matrix.rows[0].z * vec.z + matrix.rows[0].w * vec.w,
				vec.y = matrix.rows[1].x * vec.x + matrix.rows[1].y * vec.y + matrix.rows[1].z * vec.z + matrix.rows[1].w * vec.w,
				vec.z = matrix.rows[2].x * vec.x + matrix.rows[2].y * vec.y + matrix.rows[2].z * vec.z + matrix.rows[2].w * vec.w,
				vec.w =	matrix.rows[3].x * vec.x + matrix.rows[3].y * vec.y + matrix.rows[3].z * vec.z + matrix.rows[3].w * vec.w
			}
			inline friend bool operator==(const Matrix& left, const Matrix& right) {
				return left.IsEqualTo(right);
			}
			inline friend bool operator!=(const Matrix& left, const Matrix& right) {
				return left.IsUnequalTo(right);
			}

			//Special Matrices
			static Matrix Orthographic(float left, float right, float bottom, float top, float near, float far) {
				Matrix4f result = Identity();

				result.elements[0 + 0 * 4] = 2.0f / (right - left);

				result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

				result.elements[2 + 2 * 4] = 2.0f / (near - far);

				result.elements[3 + 0 * 4] = (left + right) / (left - right);
				result.elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
				result.elements[3 + 2 * 4] = (far + near) / (far - near);

				return result;
			}
			static Matrix ProjectionFOV(float fov, float aspectRatio, float near, float far) {
				Matrix4f result = Identity();

				float x  = 1.0f / tan(Math::toRadians(0.5f * fov));

				result.elements[0 + 0 * 4] = x / aspectRatio;
				result.elements[1 + 1 * 4] = x;
				result.elements[2 + 2 * 4] = (near) / (near - far);
				result.elements[3 + 2 * 4] = (near * far) / (near - far);

				result.elements[2 + 3 * 4] = -1.0f;

				return result;
			}
			static Matrix Projection(Scalar l, Scalar r, Scalar t, Scalar b, Scalar n, Scalar f) {
					Matrix4f result = Identity();

					result.elements[0 + 0 * 4] = (2.0f * n) / (r - l);
					result.elements[2 + 0 * 4] = (r + l) / (r - l);

					result.elements[1 + 1 * 4] = (2.0f * n) / (t - b);
					result.elements[2 + 1 * 4] = (t + b) / (t - b);

					result.elements[2 + 2 * 4] = -(f + n) / (f - n);
					result.elements[3 + 2 * 4] = (-2.0f * f * n) / (f - n);

					result.elements[2 + 3 * 4] = -1.0f;

					return result;
			}
			static Matrix ProjectionSymm(Scalar w, Scalar h, Scalar n, Scalar f) {
				Matrix4f result = Identity();

				result.elements[0 + 0 * 4] = n / (0.5f * w);
				result.elements[1 + 1 * 4] = n / (0.5f * h);
				result.elements[2 + 2 * 4] = -(f + n) / (f - n);
				result.elements[3 + 2 * 4] = (-2.0f * f * n) / (f - n);

				result.elements[2 + 3 * 4] = -1.0f;

				return result;
			}
			static Matrix Translate(const Vector3<Scalar>& translation) {
				Matrix4f result = Identity();

				result.elements[3 + 0 * 4] = translation.x;
				result.elements[3 + 1 * 4] = translation.y;
				result.elements[3 + 2 * 4] = translation.z;

				return result;
			}
			static Matrix Scale(const Vector3<Scalar>& scale) {
				Matrix4f result = Identity();

				result.elements[0 + 0 * 4] = scale.x;
				result.elements[1 + 1 * 4] = scale.y;
				result.elements[2 + 2 * 4] = scale.z;

				return result;
			}
			static inline Matrix Rotation(Vector3<Scalar> angle) {
				return RotationZ(angle.z) * (RotationY(angle.y) * RotationX(angle.x));
			}
			static inline Matrix Transformation(const Vector3<Scalar>& translation, const Vector3<Scalar>& scale, const Vector3<Scalar>& angle) {
				return   Matrix4f::Translate(translation) * (Matrix4f::Rotation(angle) * Matrix4f::Scale(scale));
			}
			
			static inline Matrix RotationX(float angle) {
				return RotationXR(toRadians(angle));
			}
			static inline Matrix RotationY(float angle) {
				return RotationYR(toRadians(angle));
			}
			static inline Matrix RotationZ(float angle) {
				return RotationZR(toRadians(angle));
			}
			
			static Matrix RotationXR(float angle) {
				Matrix result = Matrix4f::Identity();
				float c = cos(angle);
				float s = sin(angle);
				result.elements[1 + 1 * 4] = c;
				result.elements[2 + 1 * 4] = -s;
				result.elements[1 + 2 * 4] = s;
				result.elements[2 + 2 * 4] = c;
				return result;
			}
			static Matrix RotationYR(float angle) {
				Matrix result = Matrix4f::Identity();
				float c = cos(angle);
				float s = sin(angle);
				result.elements[0 + 0 * 4] = c;
				result.elements[2 + 0 * 4] = s;
				result.elements[0 + 2 * 4] = -s;
				result.elements[2 + 2 * 4] = c;
				return result;
			}
			static Matrix RotationZR(float angle) {
				Matrix result = Matrix4f::Identity();
				float c = cos(angle);
				float s = sin(angle);
				result.elements[0 + 0 * 4] = c;
				result.elements[1 + 0 * 4] = -s;
				result.elements[0 + 1 * 4] = s;
				result.elements[1 + 1 * 4] = c;
				return result;
			}

			static inline Matrix Rotation(float angle, const Vector3<Scalar>& axis) {
				return RotationR(toRadians(angle), axis);
			}
			static Matrix RotationR(float angle, const Vector3<Scalar>& axis) {
				Matrix4f result = Identity();
				float c = cos(angle);
				float s = sin(angle);
				float omc = 1.0f - c;

				float x = axis.x;
				float y = axis.y;
				float z = axis.z;

				result.elements[0 + 0 * 4] = x * x * omc + c;
				result.elements[0 + 1 * 4] = y * x * omc + z * s;
				result.elements[0 + 2 * 4] = x * z * omc - y * s;

				result.elements[1 + 0 * 4] = x * y * omc - z * s;
				result.elements[1 + 1 * 4] = y * y * omc + c;
				result.elements[1 + 2 * 4] = y * z * omc + x * s;

				result.elements[2 + 0 * 4] = x * z * omc + y * s;
				result.elements[2 + 1 * 4] = y * z * omc - x * s;
				result.elements[2 + 2 * 4] = z * z * omc + c;

				return result;
			}


			//Output
			static inline constexpr std::string Name() { return "Matrix 4x4"; }
			friend std::ostream& operator<<(std::ostream& stream, const Matrix& matrix) {
#define width 12
				stream << "/";
				for (int c = 0; c < 4; c++) {
					if (c != 0) stream << ", ";
					stream << std::setw(width) << matrix.elements[c + 0 * 4];
				}
				stream << "\\" << std::endl;
				for (uint i = 1; i < 4 - 1; i++) {
					stream << "|";
					for (int c = 0; c < 4; c++) {
						if (c != 0) stream << ", ";
						stream << std::setw(width) << matrix.elements[c + i * 4];
					}
					stream << "|" << std::endl;
				}
				stream << "\\";
				for (int c = 0; c < 4; c++) {
					if (c != 0) stream << ", ";
					stream << std::setw(width) << matrix.elements[c + (4 - 1) * 4];
				}
				stream << "/" << std::endl;
#undef width
				return stream;
			}
		};


	}
}