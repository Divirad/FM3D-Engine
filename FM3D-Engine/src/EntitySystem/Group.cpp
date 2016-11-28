#include <Engine.h>

namespace FM3D {

	bool Group::HasEntity(const EntityPtr& entity) const {
		return std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end();
	}

	std::vector<EntityPtr> Group::GetEntities() {
		if (m_entityVector.empty()) {
			m_entityVector = std::vector<EntityPtr>(m_entities.begin(), m_entities.end());
		}

		return m_entityVector;
	}

	size_t Group::CountOfEntities() const {
		return m_entities.size();
	}

	const Matcher& Group::GetMatcher() const {
		return m_matcher;
	}
}