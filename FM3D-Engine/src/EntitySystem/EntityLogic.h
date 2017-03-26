#pragma once
#include <Engine.h>

namespace FM3D {
	namespace EntitySystem {

		class EntityLogicCollection;

		class ENGINE_DLL EntityLogic {
			friend class EntityLogicCollection;
		protected:
			GroupPtr m_group;

			EntityLogic(GroupPtr group);
		protected:
			virtual void Initialize() {};
			virtual void Execute(EntityPtr entity) = 0;
			virtual void Terminate() {};
		public:
			virtual void ExecuteForAll();
		};

		using EntityLogicPtr = std::shared_ptr<EntityLogic>;

		class ENGINE_DLL EntityLogicCollection {
		private:
			std::unordered_set<EntityLogicPtr> m_manager;
		public:
			EntityLogicCollection() = default;

			void Initialize();
			void Terminate();
			void Execute();

			void Add(const EntityLogicPtr& manager);
			void Remove(const EntityLogicPtr& manager);
		};
	}
}