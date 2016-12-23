#pragma once
#include "pch.h"

namespace DesignerLib {

	public ref class Vec3 {
	public:
		property float X;
		property float Y;
		property float Z;

		Vec3^ Add(Vec3^ other) {
			this->X += other->X;
			this->Y += other->Y;
			this->Z += other->Z;
			return this;
		}

		Vec3(float x, float y, float z) {
			X = x;
			Y = y;
			Z = z;
		}

		Vec3(const FM3D::Vector3f& other) {
			X = other.x;
			Y = other.y;
			Z = other.z;
		}

		FM3D::Vector3f Convert() {
			return FM3D::Vector3f(X, Y, Z);
		}
	};
}