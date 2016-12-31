#include <Engine.h>

namespace FM3D {

	Manager::Manager(GroupPtr group) : m_group(group) {

	}

	void Manager::ExecuteForAll() {
		auto entities = m_group->GetEntities();
		for (const EntityPtr e : entities) {
			Execute(e);
		}
	}

	void ManagerCollection::Initialize() {
		for (const auto& m : m_manager) {
			m->Initialize();
		}
	}

	void ManagerCollection::Terminate() {
		for (const auto& m : m_manager) {
			m->Terminate();
		}
	}

	void ManagerCollection::Execute() {
		for (const auto& m : m_manager) {
			m->ExecuteForAll();
		}
	}

	void ManagerCollection::Add(const ManagerPtr& manager) {
		m_manager.insert(manager);
	}

	void ManagerCollection::Remove(const ManagerPtr& manager) {
		m_manager.erase(manager);
	}
}