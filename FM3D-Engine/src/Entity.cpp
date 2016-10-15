#include <Engine.h>

namespace ENGINE_NAME {

	Entity::Entity(Vector3f position, Vector3f rotation, Vector3f scale, const Model* model) :
	m_position(position), m_rotation(rotation), m_scale(scale), m_model(model), m_animations() {

	}
}