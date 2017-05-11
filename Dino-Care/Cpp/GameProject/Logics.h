#pragma once
#include <Engine.h>
using ALL_FM3D_NAMESPACES;

namespace Dino_Care {

	class RenderLogic : public EntityLogic {
	private:
		Renderer3D* m_renderer;
	public:
		RenderLogic(Renderer3D* renderer, EntityCollection& scene);

		virtual void Execute(EntityPtr entity) override;
	};

}