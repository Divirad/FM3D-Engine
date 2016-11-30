#include <Engine.h>

namespace FM3D {
	Matcher::Matcher() {
		CalcHash();
	}

	Matcher::Matcher(const Matcher& other):
	m_allOfIds(other.m_allOfIds), m_noneOfIds(other.m_noneOfIds), m_anyOfIds(other.m_anyOfIds) {
		CalcHash();
	}

	static void SortIds(ComponentIdList& list) {
		std::sort(list.begin(), list.end());
		list.erase(std::unique(list.begin(), list.end()), list.end());	//Löscht alle mehrfach vorkommenden Elemente
	}

	Matcher& Matcher::AllOf(ComponentIdList ids) {
		SortIds(ids);
		this->m_allOfIds = ids;
		CalcHash();
		OnMatcherChangedEvent(this);
		return *this;
	}

	//Matcher& Matcher::AllOf(ComponentIdList&& ids) {
	//	SortIds(ids);
	//	this->m_allOfIds = ids;
	//	CalcHash();
	//	OnMatcherChangedEvent(this);
	//	return *this;
	//}

	Matcher& Matcher::NoneOf(ComponentIdList ids) {
		SortIds(ids);
		this->m_noneOfIds = ids;
		CalcHash();
		OnMatcherChangedEvent(this);
		return *this;
	}

	//Matcher& Matcher::NoneOf(ComponentIdList&& ids) {
	//	SortIds(ids);
	//	this->m_noneOfIds = ids;
	//	CalcHash();
	//	OnMatcherChangedEvent(this);
	//	return *this;
	//}

	Matcher& Matcher::AnyOf(ComponentIdList ids) {
		SortIds(ids);
		this->m_anyOfIds.push_back(ids);
		CalcHash();
		OnMatcherChangedEvent(this);
		return *this;
	}

	//Matcher& Matcher::AnyOf(ComponentIdList&& ids) {
	//	SortIds(ids);
	//	this->m_anyOfIds.push_back(ids);
	//	CalcHash();
	//	OnMatcherChangedEvent(this);
	//	return *this;
	//}

	bool Matcher::IsEmpty() const {
		return m_allOfIds.empty() && m_noneOfIds.empty() && m_anyOfIds.empty();
	}

	bool Matcher::Matches(const EntityPtr& entity) {
		if (!m_allOfIds.empty() && !entity->HasComponents(m_allOfIds)) return false;
		if (!m_noneOfIds.empty() && entity->HasAnyComponent(m_noneOfIds)) return false;
		for (auto& ids : m_anyOfIds) {
			if (!entity->HasAnyComponent(ids)) return false;
		}
		return true;
	}

	const ComponentIdList& Matcher::GetAllOfIndices() const {
		return m_allOfIds;
	}

	const ComponentIdList& Matcher::GetNoneOfIndices() const {
		return m_noneOfIds;
	}

	const std::vector<ComponentIdList>& Matcher::GetAnyOfIndices() const {
		return m_anyOfIds;
	}

	bool Matcher::operator==(const Matcher& right) const {
		if (this->m_hash != right.m_hash) return false;
		if (this->m_allOfIds.size() != right.m_allOfIds.size()) return false;
		if (this->m_noneOfIds.size() != right.m_noneOfIds.size()) return false;
		if (this->m_anyOfIds.size() != right.m_anyOfIds.size()) return false;

		for (size_t i = 0, s = this->m_allOfIds.size(); i < s; i++) {
			if (this->m_allOfIds[i] != right.m_allOfIds[i]) return false;
		}
		for (size_t i = 0, s = this->m_noneOfIds.size(); i < s; i++) {
			if (this->m_noneOfIds[i] != right.m_noneOfIds[i]) return false;
		}
		for (size_t i = 0, s = this->m_anyOfIds.size(); i < s; i++) {
			if (this->m_anyOfIds[i].size() != right.m_anyOfIds[i].size()) return false;
			for (size_t i2 = 0, s2 = this->m_anyOfIds[i].size(); i2 < s2; i2++) {
				if (this->m_anyOfIds[i][i2] != right.m_anyOfIds[i][i2]) return false;
			}
		}
		return true;
	}

	size_t Matcher::GetHash() const {
		return m_hash;
	}

	//using boost::hash_combine
	template <class T>
	static inline void hash_combine(size_t& seed, T const& v) {
		seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	void Matcher::CalcHash() {
		size_t seed = m_allOfIds.size() ^ m_noneOfIds.size() ^ m_anyOfIds.size();
		for (const ComponentId& i : m_allOfIds) {
			hash_combine(seed, i);
		}
		for (const ComponentId& i : m_noneOfIds) {
			hash_combine(seed, i);
		}
		for (const ComponentIdList& l : m_anyOfIds) {
			for (const ComponentId& i : l) {
				hash_combine(seed, i);
			}
		}
		this->m_hash = seed;
	}

	void Matcher::ClearIds() {
		m_allOfIds.clear();
		m_noneOfIds.clear();
		m_anyOfIds.clear();
		CalcHash();
		OnMatcherChangedEvent(this);
	}
}