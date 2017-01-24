#pragma once
#include <Engine.h>

namespace FM3D {
	namespace EntitySystem {

		template<class C>
		class IComponentArgs {
		public:
			void SetComponent(EntityPtr e) = 0;
		};

		template<class C, class... Args>
		class ComponentArgs : public IComponentArgs<C> {
		private:
			std::function<void(EntityPtr)> m_func;
		public:
			ComponentArgs(Args... arg) {
				m_func = [=](EntityPtr e) { e->Add<C>(arg...); };
			}

			void SetComponent(EntityPtr e) override {
				m_func(e);
			}
		};
	}
}