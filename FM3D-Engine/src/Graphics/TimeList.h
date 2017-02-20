#pragma once
#include <Engine.h>

namespace FM3D {

	enum AdvanceRule {
		CLAMP,
		REPEAT
	};
	
	template<class T>
	class TimeList {
	private:
		std::vector<std::pair<double, T>> m_items;
		AdvanceRule m_rule;
		std::function<T(const T&, const T&, double)> m_interpolFunc;
	public:
		TimeList(const std::vector<std::pair<double, T>>& items, AdvanceRule rule);
		TimeList(const std::vector<std::pair<double, T>>& items, AdvanceRule rule, std::function<T(const T&, const T&, double)> interpolFunc);
		TimeList(std::vector<std::pair<double, T>>&& items, AdvanceRule rule);
		TimeList(std::vector<std::pair<double, T>>&& items, AdvanceRule rule, std::function<T(const T&, const T&, double)> interpolFunc);

		inline AdvanceRule GetRule() { return m_rule; }
		inline void SetRule(AdvanceRule value) { m_rule = value; }

		T Get(double time) const;
		inline T operator[](double time) const { return Get(time); }

		inline double Begin() const { return m_items.empty() ? 0.0 : m_items[0].first; }
		inline double End() const { return m_items.empty() ? 0.0 : m_items[m_items.size() - 1].first; }

		void SetEnd(double time);

		inline bool IsEmpty() const { return m_items.empty(); }

		template<class U, class... V>
		void MakeSameEnding(TimeList<U>& other, TimeList<V>&... others);

	private:
		static T StdInterpolFunc(const T& t0, const T& t1, double factor);
		static Quaternionf StdQuatInterpolFunc(const Quaternionf& t0, const Quaternionf& t1, double factor);
	};



	template<class T>
	inline T TimeList<T>::Get(double time) const {
		if (time > End()) {
			if (m_rule == CLAMP) {
				return m_items[m_items.size() - 1].second;
			}
			else {
				time = fmod(time, End());
			}
		}
		//Find times
		for (size_t i = 0, s = m_items.size(); i < s; i++) {
			if (time < m_items[i + 1].first) {
				return m_interpolFunc(m_items[i].second, m_items[i + 1].second, (time - m_items[i].first) / (m_items[i + 1].first - m_items[i].first));
			}
		}
	}

	template<class T>
	inline void TimeList<T>::SetEnd(double time) {
		if(!IsEmpty()) m_items.push_back(std::make_pair(time, m_items[m_items.size() - 1].second));
	}

	template<class T>
	inline T TimeList<T>::StdInterpolFunc(const T& t0, const T& t1, double factor) {
		return (t0 * (1.0 - factor)) + (t1 * factor);
	}

	template<class T>
	inline Quaternionf TimeList<T>::StdQuatInterpolFunc(const Quaternionf& t0, const Quaternionf& t2, double factor) {
		return Quaternionf::Slerp(t0, t2, static_cast<float>(factor));
	}

	template<class T>
	inline TimeList<T>::TimeList(const std::vector<std::pair<double, T>>& items, AdvanceRule rule): TimeList(items, rule, &TimeList::StdInterpolFunc) {
	}

	template<>
	inline TimeList<Quaternionf>::TimeList(const std::vector<std::pair<double, Quaternionf>>& items, AdvanceRule rule): TimeList(items, rule, &TimeList::StdQuatInterpolFunc) {
	}

	template<class T>
	inline TimeList<T>::TimeList(const std::vector<std::pair<double, T>>& items, AdvanceRule rule, std::function<T(const T&, const T&, double)> interpolFunc):
	m_items(items), m_rule(rule), m_interpolFunc(interpolFunc) {
	}

	template<class T>
	inline TimeList<T>::TimeList(std::vector<std::pair<double, T>>&& items, AdvanceRule rule) : TimeList(items, rule, &TimeList::StdInterpolFunc) {
	}

	template<>
	inline TimeList<Quaternionf>::TimeList(std::vector<std::pair<double, Quaternionf>>&& items, AdvanceRule rule) : TimeList(items, rule, &TimeList::StdQuatInterpolFunc) {
	}

	template<class T>
	inline TimeList<T>::TimeList(std::vector<std::pair<double, T>>&& items, AdvanceRule rule, std::function<T(const T&, const T&, double)> interpolFunc) :
		m_items(items), m_rule(rule), m_interpolFunc(interpolFunc) {
	}

	template<class T>
	template<class U, class... V>
	inline void TimeList<T>::MakeSameEnding(TimeList<U>& other, TimeList<V>&... others) {
		double maxTime = std::max({ End(), other.End(), others.End()... });

		if (End() != maxTime) m_items.push_back(std::make_pair(maxTime, m_items[m_items.size() - 1].second));
		if (other.End() != maxTime) other.m_items.push_back(std::make_pair(maxTime, other.m_items[m_items.size() - 1].second));
		(if (others.End() != maxTime) others.m_items.push_back(std::make_pair(maxTime, others.m_items[m_items.size() - 1].second)))...;
	}
}