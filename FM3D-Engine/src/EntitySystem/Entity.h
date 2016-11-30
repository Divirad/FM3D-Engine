#pragma once

namespace FM3D {

	class ENGINE_DLL Entity {
		friend class EntityCollection;
	public:
#pragma region Events
		///Event f�r eine Component-Ver�nderung
		/**
		* Wird ausgel�st wenn sich ein FM3D::Component des FM3D::Entity ver�ndert.
		* Das Event besitzt keinen R�ckgabewert (void) und als Parameter einen
		* Pointer auf das ver�nderte FM3D::Entity, die Id und Adresse des FM3D::Component;
		*/
		using ComponentChangedEvent = Event<void(EntityPtr entity, ComponentId index, Component* component)>;
		
		///Event f�r eine Component-�berschreibung
		/**
		* Wird ausgel�st wenn ein FM3D::Component des FM3D::Entity durch
		* ein anderes FM3D::Component ausgetauscht wird. Das Event besitzt
		* keinen R�ckgabewert (void) und als Parameter einen Pointer auf
		* das ver�nderte FM3D::Entity, die Id des FM3D::Component und einen
		* Pointer auf den neuen und den alten FM3D::Component.
		*/
		using ComponentReplacedEvent = Event<void(EntityPtr entity, ComponentId index, Component* previousComponent, Component* newComponent)>;
		
		///Event f�r eine Entity-Ver�nderung
		/**
		* Wird ausgel�st wenn sich das FM3D::Entity ver�ndert.
		* Das Event besitzt keinen R�ckgabewert (void) und als Parameter
		* einen Pointer auf das ver�nderte FM3D::Entity;
		*/
		using EntityChangedEvent = Event<void(Entity* entity)>;

		///Eventquelle f�r das Hinzuf�gen eines FM3D::Component
		/**
		* Wird ausgel�st wenn ein neues FM3D::Component dem FM3D::Entity hinzugef�gt wird.
		*/
		ComponentChangedEvent OnComponentAdded;

		///Eventquelle f�r das Austauschen eines FM3D::Component
		/**
		* Wird ausgel�st wenn ein FM3D::Component des FM3D::Entity mit einem neues
		* ausgetauscht wird.
		*/
		ComponentReplacedEvent OnComponentReplaced;

		///Eventquelle f�r das Entfernen eines FM3D::Component
		/**
		* Wird ausgel�st wenn ein FM3D::Component des FM3D::Entity entfernt wird.
		*/
		ComponentChangedEvent OnComponentRemoved;

		///Eventquelle f�r das zuk�nftige L�schen des Entities
		/**
		* Wird ausgel�st wenn das Entity kurz davor ist gel�scht zu werden.
		*/
		EntityChangedEvent OnEntityWillBeDestroyed;

		///Eventquelle f�r das L�schen des Entities
		/**
		* Wird ausgel�st nachdem das Entity gel�scht wurde.
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
		* False wenn das FM3D::Entity zerst�rt wurde.
		*/
		bool m_isAlive = true;

		///Id des Entitiy-Objekts
		/**
		* Jedes Objekt der FM3D::Entity-Klasse hat eine eigene Id.
		* Diese kann verwendet werden um verschiedene Entities zu
		* vergleichen oder zu indentifizieren.
		*/
		EntityId m_id;

		///Collection, die das Entity enth�lt
		/**
		* Pointer zu der FM3D::EntityCollection, welche das
		* FM3D::Entity erstellt hat.
		*/
		EntityCollection* m_collection;

		std::weak_ptr<Entity> m_this;
	public:
		///Testet ob das Entity alle Komponenten besitzt
		/**
		* Durchsucht das FM3D::Entity nach den �bergebenen FM3D::Component.
		*
		* @param indices  Ids der Komponenten, auf die das Entity �berpr�ft werden soll
		* @returns true wenn das Entity ALLE �bergebene Komponenten besitzt
		*/
		bool HasComponents(const std::vector<ComponentId>& indices) const;

		///Testet ob das Entity mindestens einen Komponenten besitzt
		/**
		* Durchsucht das FM3D::Entity nach den �bergebenen FM3D::Component.
		*
		* @param indices  Ids der Komponenten, auf die das Entity �berpr�ft werden soll
		* @returns true wenn das Entity mindestens einen der �bergebenen Komponenten besitzt
		*/
		bool HasAnyComponent(const std::vector<ComponentId>& indices) const;

		///Anzahl Komponenten
		/**
		* Get-Methode f�r die Gr��e der std::map #m_components.
		*
		* @returns Anzahl der Komponenten die das FM3D::Entity besitzt
		*/
		uint GetComponentsCount() const;

		///Entfernt alle Komponenten
		/**
		* Leert die std::map #m_components und l�scht damit alle FM3D::Component,
		* die das FM3D::Entity besitzt.
		*/
		void RemoveAllComponents();

		///Zustand des Entities
		/**
		* Get-Methode f�r #m_isAlive.
		*
		* @returns true wenn das FM3D::Entity aktiv ist und
		*		   false wenn das FM3D::Entity zerst�rt wurde.
		*/
		bool IsAlive() const;

		///Id des Entitiy-Objekts
		/**
		* Get-Methode f�r #m_id.
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
		* Initialisiert alle nicht �bergebenben Werte mit ihrem Standard-Konstuktor.
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

		///Zerst�rt das Entity
		/**
		* L�scht das Entity und macht es damit nicht mehr nutzbar.
		* Das FM3D::Entity bleibt weiterhin im Speicher um erneut
		* genutzt zu werden. Hierbei werden die Eventquellen
		* #OnEntityDestroyed und #OnEntityWillBeDestroyed ausgel�st.
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