#include <Engine.h>

namespace FM3D {

	EntityId EntityCollection::s_entityID = 0UL;

	EntityPtr EntityCollection::CreateEntity() {
		EntityPtr entity;

		if (m_reuseableEntities.size() > 0) {
			//Use destroyed Entity
			entity = EntityPtr(m_reuseableEntities.top());
			m_reuseableEntities.pop();
		}
		else {
			entity = EntityPtr(new Entity(this), [](void* entity)
			{
				static_cast<Entity*>(entity)->GetCollection()->OnEntityReleased(static_cast<Entity*>(entity));
			});
		}

		//Set or Reset entity
		entity->SetInstance(entity);
		entity->SetEntityId(s_entityID++);
		entity->SetAlive(true);

		entity->OnComponentAdded   += std::bind(&EntityCollection::OnEntityComponentChanged, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		entity->OnComponentRemoved += std::bind(&EntityCollection::OnEntityComponentChanged, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

		m_entities.insert(entity);
		m_entityVector.clear();

		OnEntityCreated(this, entity);

		return entity;
	}

	bool EntityCollection::HasEntity(const EntityPtr& entity) const {
		return std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end();
	}

	void EntityCollection::DestroyEntity(const EntityPtr& entity) {
		if (!HasEntity(entity)) {
			throw std::runtime_error("Error on destroying entity. EntityCollection does not contain entity.");
		}
		OnEntityWillBeDestroyed(this, entity);
		entity->Destroy();
		m_entities.erase(entity);
		//vector have to change
		m_entityVector.clear();

		if (entity.use_count() == 1) {
			//Entity is not used by smart pointers
			m_reuseableEntities.push(entity.get());
		}
		else {
			//Entity is used by smart pointers
			m_retainedEntities.insert(entity.get());
		}

		OnEntityDestroyed(this, entity);
	}

	void EntityCollection::UpdateGroup(GroupPtr& group) {
		for (const EntityPtr& e : m_entities) {
			group->UpdateEntity(e);
		}
	}

	void EntityCollection::UpdateGroups(const EntityPtr& entity) {
		for (auto& g : m_groups) {
			g.second->UpdateEntity(entity);
		}
	}

	void EntityCollection::OnEntityComponentChanged(EntityPtr entity, ComponentId index, Component * component) {
		UpdateGroups(entity);
	}

	void EntityCollection::OnEntityReleased(Entity* entity) {
		if (entity->m_isAlive) {
			throw std::runtime_error("Error, cannot release entity. Entity is not destroyed yet.");
		}

		size_t erased = m_retainedEntities.erase(entity);
		if (!erased) return;
		m_reuseableEntities.push(entity);
	}

	void EntityCollection::DestroyAllEntities() {
		for (const EntityPtr& e : m_entities) {
			OnEntityWillBeDestroyed(this, e);
			e->Destroy();
			if (e.use_count() == 1) {
				//Entity is not used by smart pointers
				m_reuseableEntities.push(e.get());
			}
			else {
				//Entity is used by smart pointers
				m_retainedEntities.insert(e.get());
			}

			OnEntityDestroyed(this, e);
		}
		m_entities.clear();
		m_entityVector.clear();
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
		size_t result = 0;
		for (const auto& c : m_reusableComponents) {
			result += c.second.size();
		}
		return result;
	}

	size_t EntityCollection::CountOfRetainedEntities() const {
		return m_retainedEntities.size();
	}

	void EntityCollection::DestroyGroup(Group & group) {
		DestroyGroup(group.GetMatcher());
	}

	void EntityCollection::DestroyGroup(const Matcher & matcher) {
		auto iterator = m_groups.find(matcher);
		if (iterator == m_groups.end()) return;

		m_groups.erase(iterator);
		OnGroupDestroyed(this, iterator->second);
	}

	GroupPtr EntityCollection::GetGroup(const Matcher & matcher) {
		GroupPtr group;
		auto iterator = m_groups.find(matcher);
		if (iterator == m_groups.end()) {
			group = GroupPtr(new Group(matcher));
			group->SetInstance(group);
			UpdateGroup(group);
			m_groups[group->GetMatcher()] = group;

			OnGroupCreated(this, group);
		}
		else {
			group = iterator->second;
		}

		return group;
	}
}