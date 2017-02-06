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
#include "Matrix4.h"

namespace FM3D {
	namespace Math {

		ENGINE_DLL inline Vector3f GetLookingDirection(Vector3f& rotation, const Vector3f& standardDirection = Vector3f(0.0f, 0.0f, -1.0f)) {
			return (Matrix4f::Rotation(rotation) * standardDirection).Normalize();
		}

		ENGINE_DLL inline Vector3f GetLookingDirection2D(Vector3f& rotation, const Vector3f& standardDirection = Vector3f(0.0f, 0.0f, -1.0f)) {
			return (Matrix4f::Rotate(rotation.y, Vector3f(0.0f, 1.0f, 0.0f)) * standardDirection).Normalize();
		}
	}
}