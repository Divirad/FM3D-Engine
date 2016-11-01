#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	template<class T>
	class RawArray;

	template<class T>
	class DynamicRawArray : public DynamicArrayBase<T> {
		friend class RawArray<T>;
	private:
		bool m_isCreated;
	public:
		DynamicRawArray(uint count);
		DynamicRawArray(const std::initializer_list<T>& data);

		DynamicRawArray(const DynamicRawArray<T>&) = delete;
		DynamicRawArray(DynamicRawArray<T>&&) = delete;
		DynamicRawArray<T>& operator=(const DynamicRawArray<T>&) = delete;
		~DynamicRawArray() { 
			if (!m_isCreated) {
				std::cout << "DynamicRawArray never was created!" << std::endl;
			}
		}

		bool IsCreated() const { return m_isCreated; }

		void Delete() {
			if (!m_isCreated) {
				free(m_data);
				m_isCreated = true;
			}
		}
	};

	template<class T>
	DynamicRawArray<T>::DynamicRawArray(uint count) : DynamicArrayBase<T>((T*)malloc(sizeof(T) * count), count, count), m_isCreated(false) {
	}

	template<class T>
	DynamicRawArray<T>::DynamicRawArray(const std::initializer_list<T>& data) : DynamicArrayBase<T>((T*)malloc(sizeof(T) * data.size()), (uint)data.size(), (uint)data.size()), m_isCreated(false) {
		memcpy((void*)m_data, data.begin(), m_size * sizeof(T));
	}
}