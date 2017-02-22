#pragma once
#include <Engine.h>

namespace FM3D {

	class OldMatrix {
	public:
		union {
			float elements[4 * 4];
			Vector4f rows[4];
		};

		OldMatrix() { memset(elements, 0, 4 * 4 * sizeof(float)); }
		OldMatrix(float diagonal) { memset(elements, 0, 4 * 4 * sizeof(float)); elements[0 + 0 * 4] = diagonal; elements[1 + 1 * 4] = diagonal; elements[2 + 2 * 4] = diagonal; elements[3 + 3 * 4] = diagonal; }
		OldMatrix(float* elements) { memcpy(this->elements, elements, 4 * 4 * sizeof(float)); }
		OldMatrix(const Vector4f& row0, const Vector4f& row1, const Vector4f& row2, const Vector4f& row3) { rows[0] = row0; rows[1] = row1; rows[2] = row2; rows[3] = row3; }

		static OldMatrix Identity() { return 1.0f; }

		OldMatrix& Multiply(const OldMatrix& other) {
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
			memcpy(elements, data, 4 * 4 * sizeof(float));
			return *this;
		}
		friend OldMatrix operator*(OldMatrix left, const OldMatrix& right) { return left.Multiply(right); }
		OldMatrix& operator*=(const OldMatrix& other) { return Multiply(other); }

		OldMatrix& Multiply(float scalar) {
			for (int i = 0; i < 16; i++) {
				elements[i] *= scalar;
			}
			return *this;
		}
		friend OldMatrix operator*(OldMatrix left, float scalar) { return left.Multiply(scalar); }
		OldMatrix& operator*=(float scalar) { return Multiply(scalar); }

		OldMatrix& Add(const OldMatrix& other) {
			for (int i = 0; i < 16; i++) {
				elements[i] += other.elements[i];
			}
			return *this;
		}
		friend OldMatrix operator+(OldMatrix left, const OldMatrix& right) { return left.Add(right); }
		OldMatrix& operator+=(const OldMatrix& other) { return Add(other); }

		Vector3f Multiply(const Vector3f& other) const {
			return Vector3f(
				rows[0].x * other.x + rows[0].y * other.y + rows[0].z * other.z + rows[0].w,
				rows[1].x * other.x + rows[1].y * other.y + rows[1].z * other.z + rows[1].w,
				rows[2].x * other.x + rows[2].y * other.y + rows[2].z * other.z + rows[2].w
			);
		}
		friend Vector3f operator*(const OldMatrix& left, const Vector3f& right) { return left.Multiply(right); }

		Vector4f Multiply(const Vector4f& other) const {
			return Vector4f(
				rows[0].x * other.x + rows[0].y * other.y + rows[0].z * other.z + rows[0].w * other.w,
				rows[1].x * other.x + rows[1].y * other.y + rows[1].z * other.z + rows[1].w * other.w,
				rows[2].x * other.x + rows[2].y * other.y + rows[2].z * other.z + rows[2].w * other.w,
				rows[3].x * other.x + rows[3].y * other.y + rows[3].z * other.z + rows[3].w * other.w
			);
		}
		friend Vector4f operator*(const OldMatrix& left, const Vector4f& right) { return left.Multiply(right); }

		OldMatrix& Invert() {
			float temp[16];

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

		Vector4f GetColumn(int index) { return Vector4f(elements[index + 0 * 4], elements[index + 1 * 4], elements[index + 2 * 4], elements[index + 3 * 4]); }

		static OldMatrix Orthographic(float left, float right, float bottom, float top, float near, float far) {
			OldMatrix result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);

			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

			result.elements[2 + 2 * 4] = 2.0f / (near - far);

			result.elements[3 + 0 * 4] = (left + right) / (left - right);
			result.elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
			result.elements[3 + 2 * 4] = (far + near) / (far - near);

			return result;
		}
		static OldMatrix Perspective(float fov, float aspectRatio, float near, float far) {
			OldMatrix result(1.0f);

			float q = 1.0f / tan(Math::toRadians(0.5f * fov));
			float a = q / aspectRatio;

			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[2 + 3 * 4] = -1.0f;
			result.elements[3 + 2 * 4] = c;

			return result;
		}
		static OldMatrix Translate(const Vector3f& translation) {
			OldMatrix result(1.0f);

			result.elements[3 + 0 * 4] = translation.x;
			result.elements[3 + 1 * 4] = translation.y;
			result.elements[3 + 2 * 4] = translation.z;

			return result;
		}

		static OldMatrix Rotate(float angle, const Vector3f& axis) {
			OldMatrix result(1.0f);

			float r = Math::toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * 4] = x * omc + c;
			result.elements[0 + 1 * 4] = y * x * omc + z * s;
			result.elements[0 + 2 * 4] = x * z * omc - y * s;

			result.elements[1 + 0 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * omc + c;
			result.elements[1 + 2 * 4] = y * z * omc + x * s;

			result.elements[2 + 0 * 4] = x * z * omc + y * s;
			result.elements[2 + 1 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = z * omc + c;

			return result;
		}

		static OldMatrix Scale(const Vector3f& scale) {
			OldMatrix result(1.0f);

			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;

			return result;
		}

		static inline OldMatrix Rotation(Vector3f angle) {
			return OldMatrix::Rotate(angle.z, Vector3f(0.0f, 0.0f, 1.0f)) *  OldMatrix::Rotate(angle.y, Vector3f(0.0f, 1.0f, 0.0f)) * OldMatrix::Rotate(angle.x, Vector3f(1.0f, 0.0f, 0.0f));
		}

		static OldMatrix Transformation(const Vector3f& translation, const Vector3f& scale, const Vector3f& angle) {
			return   OldMatrix::Translate(translation) * (OldMatrix::Rotation(angle) * OldMatrix::Scale(scale));
		}

		static OldMatrix Invert(const OldMatrix& matrix) {
			OldMatrix result = matrix;
			return result.Invert();
		}

		static OldMatrix Transpose(const OldMatrix& matrix) {
			return OldMatrix(
				Vector4f(matrix.rows[0].x, matrix.rows[1].x, matrix.rows[2].x, matrix.rows[3].x),
				Vector4f(matrix.rows[0].y, matrix.rows[1].y, matrix.rows[2].y, matrix.rows[3].y),
				Vector4f(matrix.rows[0].z, matrix.rows[1].z, matrix.rows[2].z, matrix.rows[3].z),
				Vector4f(matrix.rows[0].w, matrix.rows[1].w, matrix.rows[2].w, matrix.rows[3].w)
			);
		}

		void Transpose() {
			OldMatrix copy(elements);
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
		}

		static OldMatrix Interpolate(const OldMatrix& left, const OldMatrix& right, double timeLeft, double timeMiddle, double timeRight) {
			float f = (float)((timeMiddle - timeLeft) / (timeRight - timeLeft));
			return (left * (1.0f - f)) + (right * f);
		}

		static std::vector<OldMatrix> MassMultiplication(const std::vector<OldMatrix>& m1, const std::vector<OldMatrix>& m2) {
			if (m1.size() != m2.size()) throw std::exception();
			std::vector<OldMatrix> result(m1.size());
			for (uint i = 0; i < m1.size(); i++) {
				result[i] = m1[i] * m2[i];
			}
			return result;
		}

		static void MassMultiplication(std::vector<OldMatrix>& m1, const std::vector<OldMatrix>& m2) {
			if (m1.size() != m2.size()) throw std::exception();
			for (uint i = 0; i < m1.size(); i++) {
				m1[i] *= m2[i];
			}
		}

		friend bool operator==(OldMatrix& left, OldMatrix& right) {
			for (int i = 0; i < 16; i++) {
				if (left.elements[i] != right.elements[i]) return false;
			}
			return true;
		}
		friend bool operator!=(OldMatrix& left, OldMatrix& right) {
			for (int i = 0; i < 16; i++) {
				if (left.elements[i] != right.elements[i]) return true;
			}
			return false;
		}

		inline friend std::ostream& operator<<(std::ostream& stream, const OldMatrix& matrix) {
#define width 12
			stream << "/" << std::setw(width) << matrix.rows[0].x << ", " << std::setw(width) << matrix.rows[0].y << ", " << std::setw(width) << matrix.rows[0].z << ", " << std::setw(width) << matrix.rows[0].w << "\\" << std::endl;
			stream << "|" << std::setw(width) << matrix.rows[1].x << ", " << std::setw(width) << matrix.rows[1].y << ", " << std::setw(width) << matrix.rows[1].z << ", " << std::setw(width) << matrix.rows[1].w << "|" << std::endl;
			stream << "|" << std::setw(width) << matrix.rows[2].x << ", " << std::setw(width) << matrix.rows[2].y << ", " << std::setw(width) << matrix.rows[2].z << ", " << std::setw(width) << matrix.rows[2].w << "|" << std::endl;
			stream << "\\" << std::setw(width) << matrix.rows[3].x << ", " << std::setw(width) << matrix.rows[3].y << ", " << std::setw(width) << matrix.rows[3].z << ", " << std::setw(width) << matrix.rows[3].w << "/" << std::endl;
			return stream;
#undef width
		}
	};
}