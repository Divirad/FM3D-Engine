#pragma once
#include <Engine.h>

namespace FM3D {

	class ManagerCollection;

	class Manager {
		friend class ManagerCollection;
	protected:
		GroupPtr m_group;

		Manager(GroupPtr group);
	protected:
		virtual void Initialize() {};
		virtual void Execute(EntityPtr entity) = 0;
		virtual void Terminate() {};
	public:
		virtual void ExecuteForAll();
	};

	using ManagerPtr = std::shared_ptr<Manager>;

	class ManagerCollection {
	private:
		std::unordered_set<ManagerPtr> m_manager;
	public:
		ManagerCollection() = default;

		void Initialize();
		void Terminate();
		void Execute();

		void Add(const ManagerPtr& manager);
		void Remove(const ManagerPtr& manager);
	};
}