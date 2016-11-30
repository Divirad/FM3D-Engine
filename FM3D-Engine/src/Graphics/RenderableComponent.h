#pragma once
#include <Engine.h>

namespace FM3D {

	class RenderableComponent : public Component {
		const Model* m_model;
	public:
		void Construct(const Model* model) {
			m_model = model;
		}
		void Destruct() {}

		inline const Model* GetModel() const { return m_model; }
	};
#define RenderableComponentId ComponentIds::Get<RenderableComponent>()
}