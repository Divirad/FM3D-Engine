#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#define PI 3.14159265358f

namespace ENGINE_NAME {

	typedef Math::Vector3<float> Vector3f;
	typedef Math::Vector3<int> Vector3i;
	typedef Math::Vector3<double> Vector3d;
	typedef Math::Vector3<unsigned int> Vector3u;

	typedef Math::Vector2<float> Vector2f;
	typedef Math::Vector2<int> Vector2i;
	typedef Math::Vector2<double> Vector2d;
	typedef Math::Vector2<unsigned int> Vector2u;

	typedef Math::Vector4<float> Vector4f;
	typedef Math::Vector4<int> Vector4i;
	typedef Math::Vector4<double> Vector4d;
	typedef Math::Vector4<unsigned int> Vector4u;


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
	}
}
#include "Matrix4.h"

namespace ENGINE_NAME {
	namespace Math {

		ENGINE_DLL inline Vector3f GetLookingDirection(Vector3f& rotation, const Vector3f& standardDirection = Vector3f(0.0f, 0.0f, -1.0f)) {
			return (Matrix4f::Rotation(rotation) * standardDirection).Normalize();
		}

		ENGINE_DLL inline Vector3f GetLookingDirection2D(Vector3f& rotation, const Vector3f& standardDirection = Vector3f(0.0f, 0.0f, -1.0f)) {
			return (Matrix4f::Rotate(rotation.y, Vector3f(0.0f, 1.0f, 0.0f)) * standardDirection).Normalize();
		}
	}
}