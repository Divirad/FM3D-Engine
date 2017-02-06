#pragma once
#include <Engine.h>

namespace FM3D {
	namespace Math {

		template<uint R, uint C, uint Scalar>
		class Matrix {
		public:
			union {
				float elements[R * C];
				Vector<C, Scalar> rows[R];
			};
		};
	}
}