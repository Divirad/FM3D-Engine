#pragma once
#include <Engine.h>

namespace FM3D {

	class RenderableComponent : public Component {
		Model* m_model;
	public:
		void Construct(Model* model) {
			m_model = model;
		}
		void Destruct() {}

		inline Model* GetModel() const { return m_model; }
	};
#define RenderableComponentId ComponentIds::Get<RenderableComponent>()
}