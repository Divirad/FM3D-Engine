#pragma once
#include<Engine.h>

namespace FM3D {
	 
	struct Transformation {
		Vector3f position;
		Quaternionf rotation;
		Vector3f scale;

		Matrix4f ToMatrix() const {
			return Matrix4f::Scale(scale) * rotation.ToMatrix44() *
				Matrix4f::Translate(position);
		}

		Transformation Interpolate(const Transformation& other, float t) const {
			return{
				(position*(1.0f - t)) + (other.position*t),
				Quaternionf::Slerp(rotation, other.rotation, t),
				(scale*(1.0f - t)) + (other.scale*t)
			};
		}

		friend Transformation operator*(const Transformation& left, const Transformation& right) {
			return {
				left.position + right.position,
				left.rotation * right.rotation,
				left.scale * right.scale
			};
		}
	};
}