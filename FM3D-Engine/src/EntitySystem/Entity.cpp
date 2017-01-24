#include <Engine.h>

namespace FM3D {
	namespace EntitySystem {

		EntityPtr Entity::AddComponent(const ComponentId index, Component* component) {
			if (!m_isAlive) {
				throw std::runtime_error("Error, cannot add component to entity, entity has already been destroyed.");
			}

			if (HasComponent(index)) {
				throw std::runtime_error("Error, cannot add component to entity, component already exists");
			}

			m_components[index] = component;

			OnComponentAdded(m_this.lock(), index, component);

			return m_this.lock();
		}

		EntityPtr Entity::RemoveComponent(const ComponentId index) {
			if (!m_isAlive) {
				throw std::runtime_error("Error, cannot remove component to entity, entity has already been destroyed.");
			}

			if (!HasComponent(index)) {
				throw std::runtime_error("Error, cannot remove component to entity, component not exists");
			}

			Replace(index, nullptr);

			return m_this.lock();
		}

		EntityPtr Entity::ReplaceComponent(const ComponentId index, Component* component) {
			if (!m_isAlive) {
				throw std::runtime_error("Error, cannot replace component to entity, entity has already been destroyed.");
			}

			if (HasComponent(index)) {
				Replace(index, component);
			}
			else if (component != nullptr) {
				AddComponent(index, component);
			}

			return m_this.lock();
		}

		Component* Entity::GetComponent(const ComponentId index) const {
			if (!HasComponent(index)) {
				throw std::runtime_error("Error, cannot get component from entity, component not exists");
			}

			return m_components.at(index);
		}

		bool Entity::HasComponent(const ComponentId index) const {
			return (m_components.find(index) != m_components.end());
		}

		bool Entity::HasComponents(const std::vector<ComponentId>& indices) const {
			for (const ComponentId &index : indices) {
				if (!HasComponent(index)) {
					return false;
				}
			}

			return true;
		}

		bool Entity::HasAnyComponent(const std::vector<ComponentId>& indices) const {
			for (const ComponentId &index : indices) {
				if (HasComponent(index)) {
					return true;
				}
			}

			return false;
		}

		uint Entity::GetComponentsCount() const {
			return m_components.size();
		}

		void Entity::RemoveAllComponents() {
			{
				auto componentsIdTemp = std::vector<ComponentId>(m_components.size());

				for (const auto& pair : m_components) {
					componentsIdTemp.push_back(pair.first);
				}

				while (!m_components.empty()) {
					Replace(componentsIdTemp.back(), nullptr);
					componentsIdTemp.pop_back();
				}
			}
		}

		EntityId Entity::GetID() const {
			return m_id;
		}

		bool Entity::IsAlive() const {
			return m_isAlive;
		}

		bool Entity::operator ==(const Entity& other) const {
			return this->m_id == other.m_id;
		}

		void Entity::Destroy() {
			OnEntityWillBeDestroyed(this);
			RemoveAllComponents();
			OnEntityWillBeDestroyed.Clear();
			OnComponentAdded.Clear();
			OnComponentReplaced.Clear();
			OnComponentRemoved.Clear();
			m_isAlive = false;
			OnEntityDestroyed(this);
			OnEntityDestroyed.Clear();
		}

		void Entity::Replace(const ComponentId index, Component* replacement) {
			auto previousComponent = GetComponent(index);

			if (previousComponent == replacement) {
				OnComponentReplaced(m_this.lock(), index, previousComponent, replacement);
			}
			else {
				m_collection->GetReuseableComponents(index).push(previousComponent);

				if (replacement == nullptr) {
					m_components.erase(index);
					OnComponentRemoved(m_this.lock(), index, previousComponent);
				}
				else {
					m_components[index] = replacement;
					OnComponentReplaced(m_this.lock(), index, previousComponent, replacement);
				}
			}
		}

		Entity::Entity(EntityCollection* collection) :
			m_collection(collection) {

		}

		void Entity::SetInstance(EntityPtr& ptr) {
			this->m_this = std::weak_ptr<Entity>(ptr);
		}

		void Entity::SetEntityId(EntityId id) {
			this->m_id = id;
		}

		void Entity::SetAlive(bool alive) {
			this->m_isAlive = alive;
		}

		EntityCollection* Entity::GetCollection() {
			return m_collection;
		}
	}
}