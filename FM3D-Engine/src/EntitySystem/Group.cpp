#include <Engine.h>

namespace FM3D {
	namespace EntitySystem {

		Group::Group(const Matcher& matcher) : m_matcher(matcher) {
			m_matcher.OnMatcherChangedEvent += std::bind(&Group::ChangeGroup, this, std::placeholders::_1);
		}

		Group::~Group() {
			OnEntityAdded.Clear();
			OnEntityRemoved.Clear();
			OnGroupChanged.Clear();
			OnGroupDestroyed(this);
			OnGroupDestroyed.Clear();
		}

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

		void Group::SetInstance(std::shared_ptr<Group>& ptr) {
			this->m_this = std::weak_ptr<Group>(ptr);
		}

		Group::GroupAction Group::UpdateEntity(const EntityPtr& entity) {
			auto result = UpdateEntitySilently(entity);
			if (result == ADDED) {
				OnEntityAdded(this, entity);
			}
			else if (result == REMOVED) {
				OnEntityRemoved(this, entity);
			}

			return result;
		}

		Group::GroupAction Group::UpdateEntitySilently(const EntityPtr& entity) {
			if (HasEntity(entity)) {
				if (m_matcher.Matches(entity)) {
					return NONE;
				}
				else {
					m_entities.erase(entity);
					m_entityVector.clear();
					return REMOVED;
				}
			}
			else {
				if (m_matcher.Matches(entity)) {
					m_entities.insert(entity);
					m_entityVector.clear();
					return ADDED;
				}
				else {
					return NONE;
				}
			}
		}

		void Group::ChangeGroup(Matcher* matcher) {
			m_entities.clear();
			m_entityVector.clear();
			OnGroupChanged(this);
		}
	}
}