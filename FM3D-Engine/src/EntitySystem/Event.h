#pragma once
#include <Engine.h>

namespace FM3D {
	namespace EntitySystem {

		///Eventquelle
		/**
		* Event-Klasse mit nur einem Parameter in dem Rückgabewert und Parameter des Events Kombiniert sind
		* @tparam Funktion Template für Funktionspointer
		*/
		template<class Function>
		class Event;

		///Hilfsklassen für #Event
		/**
		* Beinhaltet alle Hilfsklassen für die Klasse #Event,
		* um zu verhindern, dass sie versehentlich außerhalb
		* von #Event verwendet werden.
		*/
		namespace EventInternal {
			///Hilfsklasse für #Event
			/**
			* Ruft die in #Event gespeicherten Funktionen auf
			* @tparam ReturnType	Rückgabewert des Events
			* @tparam Args			Parameter des Events
			*/
			template <typename ReturnType, typename... Args>
			class Invoker {
			public:
				///Invoke Methode für allgemeinen Rückgabewert
				/**
				* Ruft die in #Event gespeicherten Funktionen auf
				*
				* @param event		Event, welches aktiviert werden soll
				* @param Args		Parameter des Events
				*/
				static std::vector<ReturnType> Invoke(Event<ReturnType(Args...)> &event, Args... params);
			};

			///Hilfsklasse für #Event
			/**
			* Ruft die in #Event gespeicherten Funktionen auf,
			* falls sie den Rückgabewert #void haben.
			* @tparam ReturnType	Rückgabewert des Events
			* @tparam Args			Parameter des Events
			*/
			template <typename... Args>
			class Invoker<void, Args...> {
			public:
				///Invoke Methode für Rückgabewert #void
				/**
				* Ruft die in #Event gespeicherten Funktionen auf
				*
				* @param event		Event, welches aktiviert werden soll
				* @param Args		Parameter des Events
				*/
				static void Invoke(Event<void(Args...)> &event, Args... params);
			};
		}

		///Eventquelle
		/**
		* Speichert Funktionen, die bei einem bestimmten Ereignis im
		* Programm aufgerufen werden. Rückgabewert und Paramterer dieser
		* Funktionen sind frei wählbar. Unterstützt auch Multithreading.
		*
		* @tparam ReturnType	Rückgabewert des Events
		* @tparam Args			Parameter des Events
		*/
		template<class ReturnType, class... Args>
		class Event<ReturnType(Args...)> {
			///Invoker-Type
			/**
			* Invoker mit den Templateparametern des Events.
			*/
			using Invoker = EventInternal::Invoker<ReturnType, Args...>;

			friend class Invoker;

			///Funktions-Type
			/**
			* Funktion mit den Templateparametern des Events.
			*/
			using function = std::function<ReturnType(Args...)>;
		private:
			///Mutex für Multithreading
			/**
			* Die Event-Klasse besitzt ein std::mutex um Multithreading zu
			* unterstützen. Jedesmal bevor eine Funktion hinzugefügt
			* oder gespeichert wird, wird die Methode std::mutex::lock ausgeführt.
			*/
			std::mutex m_mutex;
			///Alle gespeicherten Funktionen
			/**
			* Eine Liste von Funktionspointern, welche aufgerufen werden kann.
			* Es wird std::list und nicht std::vector verwendet um schnelles Hinzufügen
			* und Entfernen zu ermöglichen.
			*/
			std::list<std::shared_ptr<function>> m_functions;
		public:
			///Standard Konstruktor
			/**
			* Initialisiert alle Werte mit den Standardwerten.
			*/
			Event() {};
			///Standard Destruktor
			~Event() {};

			//Keine Notwendigkeit Events zu kopieren
			Event(const Event&) = delete;
			const Event& operator=(const Event&) = delete;

			///Fügt eine neue Funktion hinzu
			/**
			* Dem Container #m_functions wird der neue Funktionspointer hinzugefügt.
			* Hierbei wartet die Methode solange bis der aktuelle Thread dieses
			* Objekt vewenden kann und sperrt es dann für die Dauer der Methode.
			*
			* @param func	Funktion, welche hinzugefügt werden soll
			*/
			Event& Add(const function &func) {
				std::lock_guard<std::mutex> lock(m_mutex);

				m_functions.push_back(std::make_shared<function>(func));

				return *this;
			}

			///Entfernt eine neue Funktion
			/**
			* Aus dem Container #m_functions wird der übergebene Funktionspointer entfernt.
			* Hierbei wartet die Methode solange bis der aktuelle Thread dieses
			* Objekt vewenden kann und sperrt es dann für die Dauer der Methode.
			*
			* @param func	Funktion, welche erntfernt werden soll
			*/
			Event& Remove(const function &func) {
				std::lock_guard<std::mutex> lock(m_mutex);

				m_functions.remove_if([&](std::shared_ptr<function>&functionPtr)
				{
					return func.target_type().hash_code() == functionPtr->target_type().hash_code();
				});

				return *this;
			}

			///Entfernt alle Funktionen
			/**
			* Aus dem Container #m_functions werden alle Funktionen gelöscht.
			* Hierbei wartet die Methode solange bis der aktuelle Thread dieses
			* Objekt vewenden kann und sperrt es dann für die Dauer der Methode.
			*/
			Event& Clear() {
				std::lock_guard<std::mutex> lock(this->m_mutex);

				this->m_functions.clear();

				return *this;
			}

			//Short operators
			///Fügt eine neue Funktion hinzu
			/**
			* Operator um einfaches Verwenden der Event-Klasse zu ermöglichen.
			* Ruft nur die Methode Add() auf.
			*
			* @param func	Funktion, welche hinzugefügt werden soll und daher an Add() übergeben wird
			*/
			inline Event& operator+=(const function &func) {
				return Add(func);
			}

			///Entfernt eine Funktion
			/**
			* Operator um einfaches Verwenden der Event-Klasse zu ermöglichen.
			* Ruft nur die Methode Remove() auf.
			*
			* @param func	Funktion, welche erntfernt werden soll und daher an Remove() übergeben wird
			*/
			inline Event& operator-=(const function &func) {
				return Remove(func);
			}

			///Aktiviert das Event
			/**
			* Operator um einfaches Verwenden der Event-Klasse zu ermöglichen.
			* Er aktiviert das Event, was bedeutet, dass jede gespeicherte
			* Funktion aufgerufen wird. Verwendet wird hierzu die Hilfsklasse Invoker
			*
			* @param args	Parameter welche verwendet werden, um die Funktionen aufzurufen
			*/
			inline ReturnType operator()(Args... args) {
				return Invoker::Invoke(*this, args...);
			}

			///Aktiviert das Event
			/**
			* Jede gespeicherte Funktion wird aufgerufen.
			* Verwendet wird hierzu die Hilfsklasse Invoker
			*
			* @param args	Parameter welche verwendet werden, um die Funktionen aufzurufen
			*/
			inline ReturnType Invoke(Args... args) {
				return Invoker::Invoke(*this, args...);
			}
		};

		//Invoker method definitions
		template <typename ReturnType, typename... Args>
		std::vector<ReturnType> EventInternal::Invoker<ReturnType, Args...>::Invoke(Event<ReturnType(Args...)> &event, Args... params) {
			std::lock_guard<std::mutex> lock(event.m_mutex);
			ReturnTypes returnValues;

			for (const auto &functionPtr : event.m_functionList) {
				returnValues.push_back((*functionPtr)(params...));
			}

			return returnValues;
		}

		template <typename... Args>
		void EventInternal::Invoker<void, Args...>::Invoke(Event<void(Args...)> &event, Args... params) {
			std::lock_guard<std::mutex> lock(event.m_mutex);

			for (const auto& functionPtr : event.m_functions) {
				(*functionPtr)(params...);
			}
		}
	}
}