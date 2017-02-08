#pragma once

#include "Vector.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#define PI 3.14159265358f

namespace FM3D {
	namespace Math {
		template<typename Scalar>
		using Vector2 = Vector<2U, Scalar>;
		template<typename Scalar>
		using Vector3 = Vector<3U, Scalar>;
		template<typename Scalar>
		using Vector4 = Vector<4U, Scalar>;
	}

	using Vector3f = Math::Vector3<float>;
	using Vector3i = Math::Vector3<int>;
	using Vector3d = Math::Vector3<double>;
	using Vector3u = Math::Vector3<unsigned int>;
	
	using Vector2f = Math::Vector2<float>;
	using Vector2i = Math::Vector2<int>;
	using Vector2d = Math::Vector2<double>;
	using Vector2u = Math::Vector2<unsigned int>;
	
	using Vector4f = Math::Vector4<float>;
	using Vector4i = Math::Vector4<int>;
	using Vector4d = Math::Vector4<double>;
	using Vector4u = Math::Vector4<unsigned int>;
	
	using Color3f = Vector3f;
	using Color4f = Vector4f;
	using Color3b = Math::Vector3<byte>;
	using Color4b = Math::Vector4<byte>;

	namespace Math {
		inline float toRadians(float degrees) {
			return (float)(degrees * (PI / 180.0f));
		}

		inline float toDegrees(float radians) {
			return (float)(radians * (180.0f / PI));
		}

		template<typename T>
		inline T Max(const T& first, const T& second) {
			return first > second ? first : second;
		}

		//0 = ex^2 + lx + c
		inline float QuadraticEquation(float exponent, float linear, float constant) {
			return (-linear + sqrtf(linear * linear - 4 * exponent * constant)) / (2 * exponent);
		}

		inline float AbsoluteValue(float abs){
			if (abs < 0){ abs *= -1; }
			return abs;
			
		}

		Color3f ConvertColor(const Color3b& color);
		Color3b ConvertColor(const Color3f& color);
		Color4f ConvertColor(const Color4b& color);
		Color4b ConvertColor(const Color4f& color);
	}
}
#include "Matrix.h"
#include "Matrix4.h"

namespace FM3D {
	namespace Math {

		template<typename Scalar>
		using Matrix2 = Math::Matrix<2, 2, Scalar>;
		template<typename Scalar>
		using Matrix3 = Math::Matrix<3, 3, Scalar>;
		template<typename Scalar>
		using Matrix4 = Math::Matrix<4, 4, Scalar>;

		template<typename Scalar>
		using Matrix22 = Math::Matrix<2, 2, Scalar>;
		template<typename Scalar>
		using Matrix33 = Math::Matrix<3, 3, Scalar>;
		template<typename Scalar>
		using Matrix44 = Math::Matrix<4, 4, Scalar>;

		template<typename Scalar>
		using Matrix23 = Math::Matrix<2, 3, Scalar>;
		template<typename Scalar>
		using Matrix24 = Math::Matrix<2, 4, Scalar>;
		template<typename Scalar>
		using Matrix32 = Math::Matrix<3, 2, Scalar>;
		template<typename Scalar>
		using Matrix34 = Math::Matrix<3, 4, Scalar>;
		template<typename Scalar>
		using Matrix42 = Math::Matrix<4, 2, Scalar>;
		template<typename Scalar>
		using Matrix43 = Math::Matrix<4, 3, Scalar>;
	}

	using Matrix2f  = Math::Matrix<2, 2, float>;
	using Matrix3f  = Math::Matrix<3, 3, float>;
	using Matrix4f  = Math::Matrix<4, 4, float>;

	using Matrix22f = Math::Matrix<2, 2, float>;
	using Matrix33f = Math::Matrix<3, 3, float>;
	using Matrix44f = Math::Matrix<4, 4, float>;

	using Matrix23f = Math::Matrix<2, 3, float>;
	using Matrix24f = Math::Matrix<2, 4, float>;
	using Matrix32f = Math::Matrix<3, 2, float>;
	using Matrix34f = Math::Matrix<3, 4, float>;
	using Matrix42f = Math::Matrix<4, 2, float>;
	using Matrix43f = Math::Matrix<4, 3, float>;

	using Matrix2d = Math::Matrix<2, 2, double>;
	using Matrix3d = Math::Matrix<3, 3, double>;
	using Matrix4d = Math::Matrix<4, 4, double>;

	using Matrix22d = Math::Matrix<2, 2, double>;
	using Matrix33d = Math::Matrix<3, 3, double>;
	using Matrix44d = Math::Matrix<4, 4, double>;

	using Matrix23d = Math::Matrix<2, 3, double>;
	using Matrix24d = Math::Matrix<2, 4, double>;
	using Matrix32d = Math::Matrix<3, 2, double>;
	using Matrix34d = Math::Matrix<3, 4, double>;
	using Matrix42d = Math::Matrix<4, 2, double>;
	using Matrix43d = Math::Matrix<4, 3, double>;

	namespace Math {

		ENGINE_DLL inline Vector3f GetLookingDirection(Vector3f& rotation, const Vector3f& standardDirection = Vector3f(0.0f, 0.0f, -1.0f)) {
			return (Matrix4f::Rotation(rotation) * standardDirection).Normalize();
		}

		ENGINE_DLL inline Vector3f GetLookingDirection2D(Vector3f& rotation, const Vector3f& standardDirection = Vector3f(0.0f, 0.0f, -1.0f)) {
			return (Matrix4f::Rotate(rotation.y, Vector3f(0.0f, 1.0f, 0.0f)) * standardDirection).Normalize();
		}
	}


}

#include "Quaternion.h"

namespace FM3D {
	using Quaternionf = Math::Quaternion<float>;
	using Quaterniond = Math::Quaternion<double>;
}

#include "Transfornation.h"