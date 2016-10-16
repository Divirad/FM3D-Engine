#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	template<class T>
	class DynamicArrayBase : public ArrayBase<T> {
	protected:
		uint m_capacity;
	public:
		DynamicArrayBase(T* data, uint count, uint capacity);

		inline uint Capacity() const { return m_capacity; }
		inline uint UnusedMem() const { return m_capacity - m_size; }
		void FreeUnusedMem() { m_data = (T*)realloc(m_data, m_size); m_capacity = 0u; }

		void AdvanceCapBy(uint size) { 
			m_capacity = m_capacity + size;
			m_data = (T*)realloc(m_data, m_capacity * sizeof(T));
		}
		void AdvanceCapTo(uint size) {
			if (size < m_size) 
				m_size = size;
			m_capacity = size;
			m_data = (T*)realloc(m_data, m_capacity * sizeof(T));
		}

		void AdvanceBy(uint size) {
			m_size += size;
			if (m_size > m_capacity) {
				m_capacity = m_size;
				m_data = (T*)realloc(m_data, m_capacity * sizeof(T));
			}
		}
		void AdvanceTo(uint size) {
			m_size = size;
			if (m_size > m_capacity)
				m_capacity = m_size;
				m_data = (T*)realloc(m_data, m_capacity * sizeof(T));
		}

		void Push_Back(const T& other) {
			AdvanceBy(1);
			m_data[m_size - 1] = other;
		}
	};

	template<class T>
	DynamicArrayBase<T>::DynamicArrayBase(T* data, uint count, uint capacity) : ArrayBase<T>(data, count), m_capacity(capacity) {
	}
}