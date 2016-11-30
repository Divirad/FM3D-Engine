#pragma once
#include <Engine.h>

namespace FM3D {

	class Group;
	using GroupPtr = std::shared_ptr<Group>;



	///Id eines FM3D::Entity
	/**
	* 64-Bit gro�e Id.
	* Jedes Objekt der FM3D::Entity-Klasse hat eine eigene Id.
	* Diese kann verwendet werden um verschiedene Entities zu
	* vergleichen oder zu indentifizieren.
	*/
	using EntityId = unsigned long;

	class ENGINE_DLL EntityCollection {
		friend class Entity;
	public:
#pragma region Events
		///Event f�r eine Entity-Ver�nderung
		/**
		* Wird ausgel�st wenn sich ein FM3D::Entity in der FM3D::EntityCollection ver�ndert.
		* Das Event besitzt keinen R�ckgabewert (void) und als Parameter
		* einen Pointer auf die FM3D::EntityCollection, welche das Event
		* ausgel�st hat und einen Pointer auf das FM3D::Entity, welches sich
		* ver�ndert hat.
		*/
		using EntityCollectionChangedEvent = Event<void(EntityCollection* collection, EntityPtr entity)>;

		///Event f�r eine Group-Ver�nderung
		/**
		* Wird ausgel�st wenn sich eine FM3D::Group in der FM3D::EntityCollection
		* ver�ndert. Das Event besitzt keinen R�ckgabewert (void) und als Parameter
		* einen Pointer auf die FM3D::EntityCollection, welche das Event
		* ausgel�st hat und einen Pointer auf die FM3D::Group, welche sich
		* ver�ndert hat.
		*/
		using GroupChangedEvent = Event<void(EntityCollection* collection, std::shared_ptr<Group> group)>;

		///Event f�r die Erstellung eines FM3d::Entity
		/**
		* Wird ausgel�st, wenn der FM3D::EntityCollection ein neues
		* FM3D::Entity hinzugef�gt wird.
		*/
		EntityCollectionChangedEvent OnEntityCreated;
		///Event bevor ein FM3d::Entity gel�scht wird.
		/**
		* Wird ausgel�st, bevor ein FM3D::Entity aus der
		* FM3D::EntityCollection gel�scht wird.
		*/
		EntityCollectionChangedEvent OnEntityWillBeDestroyed;
		///Event f�r die L�schung eines FM3d::Entity.
		/**
		* Wird ausgel�st, wenn ein FM3D::Entity aus der
		* FM3D::EntityCollection gel�scht wird.
		*/
		EntityCollectionChangedEvent OnEntityDestroyed;
		///Event f�r die Erstellung einer FM3d::Group
		/**
		* Wird ausgel�st, wenn in der FM3D::EntityCollection eine neue
		* FM3D::Group erstellt wird.
		*/
		GroupChangedEvent OnGroupCreated;
		///Event f�r die Entfernung einer FM3d::Group
		/**
		* Wird ausgel�st, wenn eine FM3D::Group gel�scht
		* und aus der FM3D::EntityCollection entfernt wird.
		*/
		GroupChangedEvent OnGroupDestroyed;

		static EntityId s_entityID;
#pragma endregion
	private:
		///Container f�r alle FM3D::Entity
		/**
		* Speichert alle FM3D::Entity, die in der FM3D::Collection
		* enthalten sind. Es wird ein std::unordered_set verwendet,
		* damit schnell Entities hinzugef�gt und entfernt werden
		* k�nnen.
		*/
		std::unordered_set<EntityPtr> m_entities;

		///Alle ungenutzten FM3D::Entity
		/**
		* Speichert alle FM3D::Entity, die zerst�rt wurden,
		* sich aber immernoch im Speicher befinden und daher
		* erneut genutzt werden k�nnen um die Performance zu
		* erh�hen. Verwendet wird hierzu ein std::stack, da
		* nur schnell hinzugef�gt und entfernt werden muss,
		* aber nicht auf bestimmte Elemente zugegriffen werden
		* muss.
		*/
		std::stack<Entity*> m_reuseableEntities;

		///Alle gel�schten aber noch aktiven Entities
		/**
		* Speichert alle FM3D::Entity, die zerst�rt wurden,
		* aber noch immer von einem smart pointer verwendet
		* werden. Hierzu wird ein std::unordered_set verwendet
		* um schnelles Hinzuf�gen und Entfernen zu erm�glichen.
		*/
		std::unordered_set<Entity*> m_retainedEntities;

		///Alle ungenutzen FM3D::Component
		/**
		* Speichert alle FM3D::Component, die zerst�rt wurden,
		* sich aber immernoch im Speicher befindet und daher
		* erneut genutzt werden k�nnen um die Performance zu
		* erh�hen. Verwendet wird hierzu eine std::map, da
		* die Komponenten nach Id sortiert sein m�ssen und
		* als Templateparameter wird std::stack verwendet, da
		* man Komponenten nur schnell Hinzuf�gen und Entfernen
		* muss und nicht darauf zugreifen muss.
		*/
		std::map<ComponentId, std::stack<Component*>> m_reusableComponents;

		///Alle FM3D::Entity als std::vector
		/**
		* Alle Entities werden auch als std::vector gespeichert, damit nicht
		* bei jedem Aufruf von GetEntities() der Vektor neu erstellt werden muss.
		* Wird gel�scht, wenn die Methode CreateEntity() oder DestroyEntity()
		* aufgerufen wird.
		*/
		std::vector<EntityPtr> m_entityVector;

		std::unordered_map<Matcher, std::shared_ptr<Group>> m_groups;

		std::function<void(Entity*)> m_entityReleasedMethod;
	public:

		///Erstellt ein neues FM3D::Entity
		/**
		* #m_entities wird ein neues FM3D::Entity hinzugef�gt.
		* Dieses wird entweder neu im Heap erstellt oder ein
		* bereits gel�schtes FM3D::Entity wird erneut genutzt.
		*
		* @returns Pointer auf das erstellte FM3D::Entity
		*/
		EntityPtr CreateEntity();

		///Testet ob Collection Entity enth�lt
		/**
		* Durchsucht die Collection nach dem �bergebenen Entity
		* 
		* @param entity	Referenz auch einen Pointer, der auf das zu suchende
		*				FM3D::Entity zeigt. Es wird eine Referenz aus
		*				Performance-Gr�nden verwendet.
		* @returns		true wenn das FM3D::Entity gefunden wurde, andernfalls false
		*/
		bool HasEntity(const EntityPtr& entity) const;

		///L�scht alle Entities
		/**
		* L�scht alle aktiven FM3D::Entity. Falls gel�schte Entities noch von einem
		* smart Pointer irgendwo im Programm verwendet werden, k�nnen sie nocht gel�scht
		* werden und es k�nnten Memory Leaks entstehen.
		*/
		void DestroyAllEntities();

		///Gibt alle Entities
		/**
		* Kopiert alle Entities in einen std::vector und gibt diesen dann zur�ck. Zur
		* Performanceerh�hung wird der std::vector gespeichert, solange bis ein FM3D::Entity
		* hinzugefg�gt oder entfernt wurde. Dieser std::vector kann dann zur�ck gegeben werden
		* falls die Methode erneut aufgerufen wird.
		*
		* @returns std::vector, welcher alle Entities enth�lt
		*/
		std::vector<EntityPtr> GetEntities();

		///Gibt erneut nutzbare Komponenten
		/**
		* Verwendet id als key f�r die std::map #m_reusableComponents,
		* sodass alle ungenutzten FM3D::Component, die mit der Id �bereinstimmen,
		* zur�ckgegeben werden.
		*
		* @param id	Die id der FM3D::Component
		* @returns Den std::stack, welcher alle ungenutzten FM3D::Component enth�lt
		*/
		std::stack<Component*>& GetReuseableComponents(ComponentId id);

		size_t CountOfEntities() const;
		size_t CountOfResuseableEntities() const;
		size_t CountOfResuseableComponents() const;
		size_t CountOfRetainedEntities() const;

		void DestroyGroup(Group& group);
		void DestroyGroup(const Matcher& matcher);

		GroupPtr GetGroup(const Matcher& matcher);

		///L�scht Entity
		/**
		* L�scht �bergebenes FM3D::Entity aus der FM3D::Collection. Das Entity wird
		* gegebenenfalls im Speicher behalten um es sp�ter erneut zu verwenden.
		*
		* @param entity	Pointer auf das zu l�schende Entity
		*/
		void DestroyEntity(const EntityPtr& entity);

		private:


			void UpdateGroup(GroupPtr& group);
			void UpdateGroups(const EntityPtr& entity);
			void OnEntityComponentChanged(EntityPtr entity, ComponentId index, Component* component);
			void OnEntityReleased(Entity* entity);
	};
}