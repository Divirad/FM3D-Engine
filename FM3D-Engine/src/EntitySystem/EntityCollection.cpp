#include <Engine.h>

namespace FM3D {

	EntityPtr EntityCollection::CreateEntity() {
		EntityPtr entity;

		if (m_reuseableEntities.size() > 0) {
			//Use destroyed Entity
			entity = EntityPtr(m_reuseableEntities.top());
			m_reuseableEntities.pop();
		}
		else {
			//TODO Create Entity
		}

		//TODO Initialize Entity

		OnEntityCreated(this, entity);

		return entity;
	}

	bool EntityCollection::HasEntity(const EntityPtr& entity) const {
		return std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end();
	}

	void EntityCollection::DestroyEntity(EntityPtr entity) {
		size_t removed = m_entities.erase(entity);

		if (!removed) {
			throw std::runtime_error("Error on destroying entity. EntityCollection does not contain entity.");
		}

		//vector have to change
		m_entityVector.clear();

		OnEntityWillBeDestroyed(this, entity);
		entity->Destroy();
		OnEntityDestroyed(this, entity);

		if (entity.use_count() == 1) {
			//Entity is not used by smart pointers
			entity->OnEntityReleased -= mOnEntityReleasedCache;
			m_reuseableEntities.push(entity.get());
		}
		else {
			//Entity is used by smart pointers
			m_retainedEntities.insert(entity.get());
		}
	}

	void EntityCollection::DestroyAllEntities() {
	}

	std::vector<EntityPtr> EntityCollection::GetEntities() {
		if (m_entityVector.empty()) {
			m_entityVector = std::vector<EntityPtr>(m_entities.begin(), m_entities.end());
		}

		return m_entityVector;
	}

	std::stack<Component*>& EntityCollection::GetReuseableComponents(ComponentId id) {
		return m_reusableComponents[id];
	}

	size_t EntityCollection::CountOfEntities() const {
		return m_entities.size();
	}
	size_t EntityCollection::CountOfResuseableEntities() const {
		return m_reuseableEntities.size();
	}
	size_t EntityCollection::CountOfResuseableComponents() const {
		return m_reusableComponents.size();
	}
	size_t EntityCollection::CountOfRetainedEntities() const {
		return m_retainedEntities.size();
	}
}