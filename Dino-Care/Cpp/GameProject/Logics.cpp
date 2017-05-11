#include "Logics.h"

Dino_Care::RenderLogic::RenderLogic(Renderer3D* renderer, EntityCollection& scene):
	EntityLogic(scene.GetGroup(Matcher().AllOf({ PositionComponentId, RenderableComponentId }))), m_renderer(renderer) {
}

void Dino_Care::RenderLogic::Execute(EntityPtr entity) {
	m_renderer->Submit(entity.get());
}
