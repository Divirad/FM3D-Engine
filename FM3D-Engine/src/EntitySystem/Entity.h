#pragma once

namespace FM3D {

	class ENGINE_DLL Entity {
		friend class EntityCollection;
	public:
#pragma region Events
		///Event für eine Component-Veränderung
		/**
		* Wird ausgelöst wenn sich ein FM3D::Component des FM3D::Entity verändert.
		* Das Event besitzt keinen Rückgabewert (void) und als Parameter einen
		* Pointer auf das veränderte FM3D::Entity, die Id und Adresse des FM3D::Component;
		*/
		using ComponentChangedEvent = Event<void(EntityPtr entity, ComponentId index, Component* component)>;
		
		///Event für eine Component-Überschreibung
		/**
		* Wird ausgelöst wenn ein FM3D::Component des FM3D::Entity durch
		* ein anderes FM3D::Component ausgetauscht wird. Das Event besitzt
		* keinen Rückgabewert (void) und als Parameter einen Pointer auf
		* das veränderte FM3D::Entity, die Id des FM3D::Component und einen
		* Pointer auf den neuen und den alten FM3D::Component.
		*/
		using ComponentReplacedEvent = Event<void(EntityPtr entity, ComponentId index, Component* previousComponent, Component* newComponent)>;
		
		///Event für eine Entity-Veränderung
		/**
		* Wird ausgelöst wenn sich das FM3D::Entity verändert.
		* Das Event besitzt keinen Rückgabewert (void) und als Parameter
		* einen Pointer auf das veränderte FM3D::Entity;
		*/
		using EntityChangedEvent = Event<void(Entity* entity)>;

		///Eventquelle für das Hinzufügen eines FM3D::Component
		/**
		* Wird ausgelöst wenn ein neues FM3D::Component dem FM3D::Entity hinzugefügt wird.
		*/
		ComponentChangedEvent OnComponentAdded;

		///Eventquelle für das Austauschen eines FM3D::Component
		/**
		* Wird ausgelöst wenn ein FM3D::Component des FM3D::Entity mit einem neues
		* ausgetauscht wird.
		*/
		ComponentReplacedEvent OnComponentReplaced;

		///Eventquelle für das Entfernen eines FM3D::Component
		/**
		* Wird ausgelöst wenn ein FM3D::Component des FM3D::Entity entfernt wird.
		*/
		ComponentChangedEvent OnComponentRemoved;

		///Eventquelle für das zukünftige Löschen des Entities
		/**
		* Wird ausgelöst wenn das Entity kurz davor ist gelöscht zu werden.
		*/
		EntityChangedEvent OnEntityWillBeDestroyed;

		///Eventquelle für das Löschen des Entities
		/**
		* Wird ausgelöst nachdem das Entity gelöscht wurde.
		*/
		EntityChangedEvent OnEntityDestroyed;
#pragma endregion
	private:
		///Alle FM3D::Component des Entities
		/**
		* Speichert alle FM3D::Component die das FM3D::Entity
		* besitzt. Sie sind in der std::map erreichbar durch
		* ihre Id als Key.
		*/
		std::map<ComponentId, Component*> m_components;

		///Zustand des Entities
		/**
		* True wenn das FM3D::Entity aktiv ist.
		* False wenn das FM3D::Entity zerstört wurde.
		*/
		bool m_isAlive = true;

		///Id des Entitiy-Objekts
		/**
		* Jedes Objekt der FM3D::Entity-Klasse hat eine eigene Id.
		* Diese kann verwendet werden um verschiedene Entities zu
		* vergleichen oder zu indentifizieren.
		*/
		EntityId m_id;

		///Collection, die das Entity enthält
		/**
		* Pointer zu der FM3D::EntityCollection, welche das
		* FM3D::Entity erstellt hat.
		*/
		EntityCollection* m_collection;

		std::weak_ptr<Entity> m_this;
	public:
		///Testet ob das Entity alle Komponenten besitzt
		/**
		* Durchsucht das FM3D::Entity nach den Übergebenen FM3D::Component.
		*
		* @param indices  Ids der Komponenten, auf die das Entity überprüft werden soll
		* @returns true wenn das Entity ALLE übergebene Komponenten besitzt
		*/
		bool HasComponents(const std::vector<ComponentId>& indices) const;

		///Testet ob das Entity mindestens einen Komponenten besitzt
		/**
		* Durchsucht das FM3D::Entity nach den Übergebenen FM3D::Component.
		*
		* @param indices  Ids der Komponenten, auf die das Entity überprüft werden soll
		* @returns true wenn das Entity mindestens einen der übergebenen Komponenten besitzt
		*/
		bool HasAnyComponent(const std::vector<ComponentId>& indices) const;

		///Anzahl Komponenten
		/**
		* Get-Methode für die Größe der std::map #m_components.
		*
		* @returns Anzahl der Komponenten die das FM3D::Entity besitzt
		*/
		uint GetComponentsCount() const;

		///Entfernt alle Komponenten
		/**
		* Leert die std::map #m_components und löscht damit alle FM3D::Component,
		* die das FM3D::Entity besitzt.
		*/
		void RemoveAllComponents();

		///Zustand des Entities
		/**
		* Get-Methode für #m_isAlive.
		*
		* @returns true wenn das FM3D::Entity aktiv ist und
		*		   false wenn das FM3D::Entity zerstört wurde.
		*/
		bool IsAlive() const;

		///Id des Entitiy-Objekts
		/**
		* Get-Methode für #m_id.
		*
		* @returns Die Id des FM3D::Entity-Objekts
		*/
		EntityId GetID() const;

		///Vergleichs-Operator
		/**
		* Vergleicht zwei FM3D::Entity mit Hilfe ihrer Id.
		*
		* @returns true wenn die Entities gleich sind.
		*/
		bool operator==(const Entity& other) const;

		template <typename C, typename... Args>
		EntityPtr Add(Args&&... args);

		template <typename C>
		EntityPtr Remove();

		template <typename C, typename... Args>
		EntityPtr Replace(Args&&... args);

		Component* GetComponent(const ComponentId index) const;
		EntityCollection* GetCollection();
	private:
		///Konstruktor
		/**
		* Initialisiert alle nicht übergebenben Werte mit ihrem Standard-Konstuktor.
		* Der Konstruktor ist privat, da FM3D::Entity-Objekt nur in einer
		* FM3D::EntityCollection erstellt werden sollen.
		*
		* @param collecttion	Pointer auf die FM3D::EntityCollection, die das
								FM3D::Entity erstellt hat. Wird #m_collection zugewiesen.
		* @param id				Id des FM3D::Entity-Objekts. Wird #m_id zugewiesen.
		*/
		Entity(EntityCollection* collection);

		EntityPtr AddComponent(const ComponentId index, Component* component);
		EntityPtr RemoveComponent(const ComponentId index);
		EntityPtr ReplaceComponent(const ComponentId index, Component* component);
		bool HasComponent(const ComponentId index) const;
		void Replace(const ComponentId index, Component* replacement);

		template<class C, class...Args>
		Component* CreateComponent(Args&... args);
		void SetInstance(EntityPtr& ptr);
		void SetEntityId(EntityId id);
		void SetAlive(bool alive);

		///Zerstört das Entity
		/**
		* Löscht das Entity und macht es damit nicht mehr nutzbar.
		* Das FM3D::Entity bleibt weiterhin im Speicher um erneut
		* genutzt zu werden. Hierbei werden die Eventquellen
		* #OnEntityDestroyed und #OnEntityWillBeDestroyed ausgelöst.
		*/
		void Destroy();
	};

	template<class C, class...Args>
	Component* Entity::CreateComponent(Args&... args) {
		std::stack<Component*> unusedComponents = m_collection->GetReuseableComponents(ComponentIds::Get<C>());
		Component* component = nullptr;

		if (unusedComponents.size() > 0) {
			component = unusedComponents.top();
			unusedComponents.pop();
		}
		else {
			component = new C();
		}

		(static_cast<C*>(component))->Construct(std::forward<Args>(args)...);

		return component;
	}

	template <typename C, typename... Args>
	EntityPtr Entity::Add(Args&&... args) {
		//Using std::forward to pass rvalues as rvalues and lvalues as lvalues
		return AddComponent(ComponentIds::Get<C>(), CreateComponent<C>(std::forward<Args>(args)...));
	}

	template <typename C>
	EntityPtr Entity::Remove() {
		return RemoveComponent(ComponentIds::Get<C>());
	}

	template <typename C, typename... Args>
	EntityPtr Entity::Replace(Args&&... args) {
		//Using std::forward to pass rvalues as rvalues and lvalues as lvalues
		return ReplaceComponent(ComponentIds::Get<C>(), CreateComponent<C>(std::forward<Args>(args)...));
	}
}