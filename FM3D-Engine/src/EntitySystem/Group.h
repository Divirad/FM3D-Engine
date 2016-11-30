#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Group {
	public:
		enum GroupAction {
			NONE,
			ADDED,
			REMOVED
		};

		using GroupUpdatedEvent = Event<void(Group* sender, EntityPtr entity)>;
		using GroupChangedEvent = Event<void(Group* sender)>;

		GroupUpdatedEvent OnEntityAdded;
		GroupUpdatedEvent OnEntityRemoved;
		GroupChangedEvent OnGroupChanged;
		GroupChangedEvent OnGroupDestroyed;
	private:
		Matcher m_matcher;
		///Container f�r alle FM3D::Entity
		/**
		* Speichert alle FM3D::Entity, die in der FM3D::Group
		* enthalten sind. Es wird ein std::unordered_set verwendet,
		* damit schnell Entities hinzugef�gt und entfernt werden
		* k�nnen.
		*/
		std::unordered_set<EntityPtr> m_entities;

		///Alle FM3D::Entity als std::vector
		/**
		* Alle Entities werden auch als std::vector gespeichert, damit nicht
		* bei jedem Aufruf von GetEntities() der Vektor neu erstellt werden muss.
		* Wird gel�scht, wenn neue FM3D::Entity der FM3D::Group hinzugef�gt werden
		* oder alte FM3D::Entity entfernt werden.
		*/
		std::vector<EntityPtr> m_entityVector;
		std::weak_ptr<Group> m_this;
	public:
		///Testet ob Group Entity enth�lt
		/**
		* Durchsucht die FM3D::Group nach dem �bergebenen Entity
		*
		* @param entity	Referenz auch einen Pointer, der auf das zu suchende
		*				FM3D::Entity zeigt. Es wird eine Referenz aus
		*				Performance-Gr�nden verwendet.
		* @returns		true wenn das FM3D::Entity gefunden wurde, andernfalls false
		*/
		bool HasEntity(const EntityPtr& entity) const;

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

		size_t CountOfEntities() const;

		const Matcher& GetMatcher() const;
		void SetInstance(std::shared_ptr<Group>& ptr);

		GroupAction UpdateEntity(const EntityPtr& entity);
		GroupAction UpdateEntitySilently(const EntityPtr& entity);
		Group(const Matcher& matcher);
		~Group();
	private:
		void ChangeGroup(Matcher* matcher);
	};
}