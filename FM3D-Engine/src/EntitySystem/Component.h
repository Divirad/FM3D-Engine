#pragma once

namespace FM3D {

	///Basisklasse für alle Komponenten
	/**
	* Leere Struktur von der alle Komponenten
	* des Entitysystems erben.
	*/
	struct ENGINE_DLL Component {
	protected:
		///Standard Konstruktor
		Component() = default;
	public:
		template<class C>
		static void Destruct(Component* component) {
			static_assert((std::is_base_of<Component, C>::value && !std::is_same<Component, C>::value), "Class type must be derived from Component");
			C* c = static_cast<C*>(component);
			c->Destruct();
		}
	};

	class PositionComponent;
	class RotationComponent;
	class ScaleComponent;
	class RenderableComponent;

	///Id eines Komponenten
	/**
	* 32-Bit Wert, der alle verschiedenen Komponenten
	* eindeutig identifiziert.
	*/
	using ComponentId = unsigned int;

	///Container von #ComponentId
	/**
	* Kurzschreibweise für ein std::vector mit
	* dem Templateparameter FM3D::ComponentId
	*/
	using ComponentIdList = std::vector<ComponentId>;

	///Erstellt und Verwaltet FM3D::ComponentId
	/**
	* Statische Klasse, die jedem Komponenten
	* eine eindeutige Id zuschreibt
	*/
	class ENGINE_DLL ComponentIds {
		typedef void(*DestructPtr)(Component*);

		///Alle Methoden eines FM3D::Component
		/**
		* Ein FM3D::Component besitzt keine virtuellen Methoden, die
		* vererbt und überschrieben werden können. Um trotzdem auf
		* Methoden zuzugreifen werden für jede Klasse, die von FM3D::Component
		* erbt, alle Adressen dieser Methoden gespeichert.
		*/
		struct ComponentMethods {
			///Pointer auf die Destruct Methode
			DestructPtr destruct;
		};
	public:
		///Erstellt Id eines #Component
		/**
		* Falls nicht vorhanden wird eine Id für den
		* FM3D::Component erstellt und dann zurück gegeben
		*
		* @tparam T	FM3D::Component, dessen Id zurück gegeben werden soll;
					wenn die Klasse nicht von FM3D::Component erbt, wird ein
					Compiletime-Error ausgegeben
		* @returns	Id des FM3D::Component
		*/
		template<typename T>
		static const ComponentId Get()
		{
			static_assert((std::is_base_of<Component, T>::value && !std::is_same<Component, T>::value), "Class T must be derived from Component");

			static ComponentId id = InitComponent<T>();
			return id;
		}

		template<> static const ComponentId Get<PositionComponent>();
		template<> static const ComponentId Get<RotationComponent>();
		template<> static const ComponentId Get<ScaleComponent>();
		template<> static const ComponentId Get<RenderableComponent>();

		template<typename T>
		static ComponentId InitComponent() {
			ComponentMethods methods;
			methods.destruct = Component::Destruct<T>;
			s_methods.push_back(methods);
			return s_counter++;
		}

		///Anzahl aller Komponenten
		/**
		* Get-Methode für #m_counter
		* 
		* @returns Anzahl aller Komponenten
		*/
		static unsigned int Count()
		{
			return s_counter;
		}

		static void Destruct(ComponentId id, Component* component) {
			typedef void(*ptr)(Component*);
			s_methods[id].destruct(component);
		}

	private:
		///Anzahl aller Komponenten
		/**
		* Beschreibt die Anzahl aller Komponenten.
		* Wird bei der erstmaligen Erstellung einer
		* Id um eins erhöht.
		*/
		static unsigned int s_counter;
		static std::vector<ComponentMethods> s_methods;
	};
}