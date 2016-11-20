#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	//Forward declaration with one parameter for functionpointer
	template<class>
	class Event;

	namespace EventInternal {
		//Invoker class for different Invoke Method with return type void
		template <typename ReturnType, typename... Args>
		class Invoker {
		public:
			static std::vector<ReturnType> Invoke(Event<ReturnType(Args...)> &event, Args... params);
		};

		template <typename... Args>
		class Invoker<void, Args...> {
		public:
			static void Invoke(Event<void(Args...)> &event, Args... params);
		};
	}

	template<class ReturnType, class... Args>
	class Event {
		typedef EventInternal::Invoker<ReturnType, Args> Invoker;
		friend Invoker;
		typedef std::function<ReturnType(Args...)> function;
	private:
		std::mutex m_mutex;
		std::list<std::shared_ptr<function>> m_functions;
	public:
		Event() {};
		~Event() {};

		Event(const Event&) = delete;
		const Event& operator=(const Event&) = delete;

		Event& Add(const function &func) {
			std::lock_guard<std::mutex> lock(m_mutex);

			m_functions.push_back(std::make_shared<function>(func));

			return *this;
		}

		Event& Remove(const function &func) {
			std::lock_guard<std::mutex> lock(m_mutex);

			m_functions.remove_if([&](std::shared_ptr<function> &functionPtr)
			{
				return func.target_type().hash_code() == functionPtr->target_type().hash_code();
			});

			return *this;
		}

		//Short operators
		inline Event& operator+=(const function &func) {
			return Add(func);
		}

		inline Event& operator-=(const function &func) {
			return Remove(func);
		}
	};

	template <typename ReturnType, typename... Args>
	std::vector<ReturnType> EventInternal::Invoker<ReturnType, Args>::Invoke(Event<ReturnType(Args...)> &event, Args... params) {
		std::lock_guard<std::mutex> lock(event.m_mutex);
		ReturnTypes returnValues;

		for (const auto &functionPtr : event.m_functionList) {
			returnValues.push_back((*functionPtr)(params...));
		}

		return returnValues;
	}

	template <typename... Args>
	void EventInternal::Invoker<void, Args>::Invoke(Event<void(Args...)> &event, Args... params) {
		std::lock_guard<std::mutex> lock(event.m_mutex);

		for (const auto &functionPtr : event.m_functionList) {
			(*functionPtr)(params...);
		}
	}
}