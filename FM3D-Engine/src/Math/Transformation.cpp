#include <Engine.h>

namespace FM3D {

	//Transformation operator*(const Transformation& left, const Transformation& right) {
	//	return Transformation{
	//		left.position + right.position,
	//		left.rotation + right.rotation,
	//		left.scale * right.scale
	//	};
	//}

	Transformation::Transformation() :
		position(Vector3f::Zero()), rotation(), scale(Vector3f(1.0f, 1.0f, 1.0f)) {
	}

	Transformation::Transformation(const Vector3f& position, const Quaternionf& rotation, const Vector3f& scale) :
		position(position), rotation(rotation), scale(scale) {
		this->rotation.Normalize();
	}

	Matrix4f Transformation::ToMatrix() const {
		return Matrix4f::Translate(position) * rotation.ToMatrix44() * Matrix4f::Scale(scale);
	}

	Transformation Transformation::Interpolate(const Transformation& other, float t) const {
		return Transformation((position * (1.0f - t)) + (other.position * t), Quaternionf::Slerp(rotation, other.rotation, t), (scale * (1.0f - t)) + (other.scale * t));
	}

	Transformation Transformation::FromMatrix(Matrix4f matrix) {
		Vector3f position(matrix.elements[3 + 0 * 4], matrix.elements[3 + 1 * 4], matrix.elements[3 + 2 * 4]);
		Vector3f scale(matrix.GetColumn(0).xyz.Length(), matrix.GetColumn(1).xyz.Length(), matrix.GetColumn(2).xyz.Length());
		Vector4f scaleInverse = Vector4f(Vector3f(1.0f, 1.0f, 1.0f) / scale, 1.0f);
		matrix.rows[0] *= scaleInverse;
		matrix.rows[1] *= scaleInverse;
		matrix.rows[2] *= scaleInverse;
		return Transformation(position, Quaternionf::FromMatrix(matrix).Normalize(), scale);
	}

	std::ostream& operator<<(std::ostream& stream, const Transformation& trans) {
		stream << trans.position << "," << std::endl << trans.rotation << "," << std::endl << trans.scale;
		return stream;
	}

	Transformation operator*(const Transformation& left, const Transformation& right) {
		return Transformation::FromMatrix(left.ToMatrix() * right.ToMatrix());
	}
}