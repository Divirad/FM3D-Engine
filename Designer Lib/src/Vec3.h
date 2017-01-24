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

#define Convert_To_Vec3(vec) gcnew Vec3(vec.x, vec.y, vec.z)
#define Convert_From_Vec3(vec) vec->X, vec->Y, vec->Z
	};
}