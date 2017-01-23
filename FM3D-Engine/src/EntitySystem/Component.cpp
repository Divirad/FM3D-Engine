#include <Engine.h>

namespace FM3D {
	namespace EntitySystem {

		unsigned int ComponentIds::s_counter = 0;
		std::vector<ComponentIds::ComponentMethods> ComponentIds::s_methods;

		template<>
		const ComponentId ComponentIds::Get<PositionComponent>() {
			static ComponentId id = InitComponent<PositionComponent>();
			return id;
		}

		template<>
		const ComponentId ComponentIds::Get<RotationComponent>() {
			static ComponentId id = InitComponent<RotationComponent>();
			return id;
		}

		template<>
		const ComponentId ComponentIds::Get<ScaleComponent>() {
			static ComponentId id = InitComponent<ScaleComponent>();
			return id;
		}

		template<>
		const ComponentId ComponentIds::Get<RenderableComponent>() {
			static ComponentId id = InitComponent<RenderableComponent>();
			return id;
		}
	}
}