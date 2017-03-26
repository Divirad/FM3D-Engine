#pragma once
#include <Engine.h>

namespace FM3D {
	namespace EntitySystem {

		class Preset {
		public:
			virtual void SetComponents(EntityPtr e) = 0;
		};
	}
}