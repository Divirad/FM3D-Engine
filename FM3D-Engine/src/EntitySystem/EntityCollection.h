#pragma once
#include <Engine.h>

namespace FM3D {

	class Group;
	using GroupPtr = std::shared_ptr<Group>;



	///Id eines FM3D::Entity
	/**
	* 64-Bit große Id.
	* Jedes Objekt der FM3D::Entity-Klasse hat eine eigene Id.
	* Diese kann verwendet werden um verschiedene Entities zu
	* vergleichen oder zu indentifizieren.
	*/
	using EntityId = unsigned long;

	class ENGINE_DLL EntityCollection {
		friend class Entity;
	public:
#pragma region Events
		///Event für eine Entity-Veränderung
		/**
		* Wird ausgelöst wenn sich ein FM3D::Entity in der FM3D::EntityCollection verändert.
		* Das Event besitzt keinen Rückgabewert (void) und als Parameter
		* einen Pointer auf die FM3D::EntityCollection, welche das Event
		* ausgelöst hat und einen Pointer auf das FM3D::Entity, welches sich
		* verändert hat.
		*/
		using EntityCollectionChangedEvent = Event<void(EntityCollection* collection, EntityPtr entity)>;

		///Event für eine Group-Veränderung
		/**
		* Wird ausgelöst wenn sich eine FM3D::Group in der FM3D::EntityCollection
		* verändert. Das Event besitzt keinen Rückgabewert (void) und als Parameter
		* einen Pointer auf die FM3D::EntityCollection, welche das Event
		* ausgelöst hat und einen Pointer auf die FM3D::Group, welche sich
		* verändert hat.
		*/
		using GroupChangedEvent = Event<void(EntityCollection* collection, std::shared_ptr<Group> group)>;

		///Event für die Erstellung eines FM3d::Entity
		/**
		* Wird ausgelöst, wenn der FM3D::EntityCollection ein neues
		* FM3D::Entity hinzugefügt wird.
		*/
		EntityCollectionChangedEvent OnEntityCreated;
		///Event bevor ein FM3d::Entity gelöscht wird.
		/**
		* Wird ausgelöst, bevor ein FM3D::Entity aus der
		* FM3D::EntityCollection gelöscht wird.
		*/
		EntityCollectionChangedEvent OnEntityWillBeDestroyed;
		///Event für die Löschung eines FM3d::Entity.
		/**
		* Wird ausgelöst, wenn ein FM3D::Entity aus der
		* FM3D::EntityCollection gelöscht wird.
		*/
		EntityCollectionChangedEvent OnEntityDestroyed;
		///Event für die Erstellung einer FM3d::Group
		/**
		* Wird ausgelöst, wenn in der FM3D::EntityCollection eine neue
		* FM3D::Group erstellt wird.
		*/
		GroupChangedEvent OnGroupCreated;
		///Event für die Entfernung einer FM3d::Group
		/**
		* Wird ausgelöst, wenn eine FM3D::Group gelöscht
		* und aus der FM3D::EntityCollection entfernt wird.
		*/
		GroupChangedEvent OnGroupDestroyed;

		static EntityId s_entityID;
#pragma endregion
	private:
		///Container für alle FM3D::Entity
		/**
		* Speichert alle FM3D::Entity, die in der FM3D::Collection
		* enthalten sind. Es wird ein std::unordered_set verwendet,
		* damit schnell Entities hinzugefügt und entfernt werden
		* können.
		*/
		std::unordered_set<EntityPtr> m_entities;

		///Alle ungenutzten FM3D::Entity
		/**
		* Speichert alle FM3D::Entity, die zerstört wurden,
		* sich aber immernoch im Speicher befinden und daher
		* erneut genutzt werden können um die Performance zu
		* erhöhen. Verwendet wird hierzu ein std::stack, da
		* nur schnell hinzugefügt und entfernt werden muss,
		* aber nicht auf bestimmte Elemente zugegriffen werden
		* muss.
		*/
		std::stack<Entity*> m_reuseableEntities;

		///Alle gelöschten aber noch aktiven Entities
		/**
		* Speichert alle FM3D::Entity, die zerstört wurden,
		* aber noch immer von einem smart pointer verwendet
		* werden. Hierzu wird ein std::unordered_set verwendet
		* um schnelles Hinzufügen und Entfernen zu ermöglichen.
		*/
		std::unordered_set<Entity*> m_retainedEntities;

		///Alle ungenutzen FM3D::Component
		/**
		* Speichert alle FM3D::Component, die zerstört wurden,
		* sich aber immernoch im Speicher befindet und daher
		* erneut genutzt werden können um die Performance zu
		* erhöhen. Verwendet wird hierzu eine std::map, da
		* die Komponenten nach Id sortiert sein müssen und
		* als Templateparameter wird std::stack verwendet, da
		* man Komponenten nur schnell Hinzufügen und Entfernen
		* muss und nicht darauf zugreifen muss.
		*/
		std::map<ComponentId, std::stack<Component*>> m_reusableComponents;

		///Alle FM3D::Entity als std::vector
		/**
		* Alle Entities werden auch als std::vector gespeichert, damit nicht
		* bei jedem Aufruf von GetEntities() der Vektor neu erstellt werden muss.
		* Wird gelöscht, wenn die Methode CreateEntity() oder DestroyEntity()
		* aufgerufen wird.
		*/
		std::vector<EntityPtr> m_entityVector;

		std::unordered_map<Matcher, std::shared_ptr<Group>> m_groups;

		std::function<void(Entity*)> m_entityReleasedMethod;
	public:

		///Erstellt ein neues FM3D::Entity
		/**
		* #m_entities wird ein neues FM3D::Entity hinzugefügt.
		* Dieses wird entweder neu im Heap erstellt oder ein
		* bereits gelöschtes FM3D::Entity wird erneut genutzt.
		*
		* @returns Pointer auf das erstellte FM3D::Entity
		*/
		EntityPtr CreateEntity();

		///Testet ob Collection Entity enthält
		/**
		* Durchsucht die Collection nach dem Übergebenen Entity
		* 
		* @param entity	Referenz auch einen Pointer, der auf das zu suchende
		*				FM3D::Entity zeigt. Es wird eine Referenz aus
		*				Performance-Gründen verwendet.
		* @returns		true wenn das FM3D::Entity gefunden wurde, andernfalls false
		*/
		bool HasEntity(const EntityPtr& entity) const;

		///Löscht alle Entities
		/**
		* Löscht alle aktiven FM3D::Entity. Falls gelöschte Entities noch von einem
		* smart Pointer irgendwo im Programm verwendet werden, können sie nocht gelöscht
		* werden und es könnten Memory Leaks entstehen.
		*/
		void DestroyAllEntities();

		///Gibt alle Entities
		/**
		* Kopiert alle Entities in einen std::vector und gibt diesen dann zurück. Zur
		* Performanceerhöhung wird der std::vector gespeichert, solange bis ein FM3D::Entity
		* hinzugefgügt oder entfernt wurde. Dieser std::vector kann dann zurück gegeben werden
		* falls die Methode erneut aufgerufen wird.
		*
		* @returns std::vector, welcher alle Entities enthält
		*/
		std::vector<EntityPtr> GetEntities();

		///Gibt erneut nutzbare Komponenten
		/**
		* Verwendet id als key für die std::map #m_reusableComponents,
		* sodass alle ungenutzten FM3D::Component, die mit der Id übereinstimmen,
		* zurückgegeben werden.
		*
		* @param id	Die id der FM3D::Component
		* @returns Den std::stack, welcher alle ungenutzten FM3D::Component enthält
		*/
		std::stack<Component*>& GetReuseableComponents(ComponentId id);

		size_t CountOfEntities() const;
		size_t CountOfResuseableEntities() const;
		size_t CountOfResuseableComponents() const;
		size_t CountOfRetainedEntities() const;

		void DestroyGroup(Group& group);
		void DestroyGroup(const Matcher& matcher);

		GroupPtr GetGroup(const Matcher& matcher);

		///Löscht Entity
		/**
		* Löscht übergebenes FM3D::Entity aus der FM3D::Collection. Das Entity wird
		* gegebenenfalls im Speicher behalten um es später erneut zu verwenden.
		*
		* @param entity	Pointer auf das zu löschende Entity
		*/
		void DestroyEntity(const EntityPtr& entity);

		private:


			void UpdateGroup(GroupPtr& group);
			void UpdateGroups(const EntityPtr& entity);
			void OnEntityComponentChanged(EntityPtr entity, ComponentId index, Component* component);
			void OnEntityReleased(Entity* entity);
	};
}