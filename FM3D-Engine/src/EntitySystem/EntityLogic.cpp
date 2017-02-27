#include <Engine.h>

namespace FM3D {
	namespace EntitySystem {

		EntityLogic::EntityLogic(GroupPtr group) : m_group(group) {

		}

		void EntityLogic::ExecuteForAll() {
			auto entities = m_group->GetEntities();
			for (const EntityPtr e : entities) {
				Execute(e);
			}
		}

		void EntityLogicCollection::Initialize() {
			for (const auto& m : m_manager) {
				m->Initialize();
			}
		}

		void EntityLogicCollection::Terminate() {
			for (const auto& m : m_manager) {
				m->Terminate();
			}
		}

		void EntityLogicCollection::Execute() {
			for (const auto& m : m_manager) {
				m->ExecuteForAll();
			}
		}

		void EntityLogicCollection::Add(const EntityLogicPtr& manager) {
			m_manager.insert(manager);
		}

		void EntityLogicCollection::Remove(const EntityLogicPtr& manager) {
			m_manager.erase(manager);
		}
	}
}