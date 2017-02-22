#pragma once
#include<Engine.h>

namespace FM3D {

	struct Transformation {
		Vector3f position;
		Quaternionf rotation;
		Vector3f scale;

		Transformation();

		Transformation(const Vector3f& position, const Quaternionf& rotation, const Vector3f& scale);

		Matrix4f ToMatrix() const;

		Transformation Interpolate(const Transformation& other, float t) const;

		static Transformation FromMatrix(Matrix4f matrix);

		friend std::ostream& operator<<(std::ostream& stream, const Transformation& trans);

		friend Transformation operator*(const Transformation& left, const Transformation& right);
	};

	 
}