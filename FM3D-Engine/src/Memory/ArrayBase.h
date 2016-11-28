#pragma once
#include <Engine.h>

namespace FM3D {

	template<class T>
	class ArrayBase {
	protected:
		T* m_data;
		uint m_size;

		ArrayBase(T* data, uint count)
			: m_data(data), m_size(count) {
		}
	public:
		ArrayBase(uint count)
			: m_data((T*)malloc(sizeof(T) * count)), m_size(count) {
		}

		T& operator[](uint i) { return m_data[i]; }
		const T& operator[](uint i) const { return m_data[i]; }

		uint Size() const { return m_size; }

		const T* begin() const { return m_data; }
		const T* end() const { return m_data + m_size; }
		T* begin() { return m_data; }
		T* end() { return m_data + m_size; }

		void CopyFrom(const std::vector<T>& vec, uint size, uint begin = 0u, uint vecBegin = 0u);
		void CopyFrom(const ArrayBase<T>& array, uint size, uint begin = 0u, uint arrayBegin = 0u);
		void CopyAllFrom(const std::vector<T>& vec, uint begin = 0u) {
			CopyFrom(vec, vec.size(), begin, 0u);
		}
		void CopyAllFrom(const ArrayBase<T>& array, uint begin = 0u) {
			CopyFrom(array, array.Size(), begin, 0u);
		}
	};

	template<class T>
	void ArrayBase<T>::CopyFrom(const std::vector<T>& vec, uint size, uint begin, uint vecBegin) {
		memcpy((void*)m_data + begin, vec[vecBegin], size);
	}

	template<class T>
	void ArrayBase<T>::CopyFrom(const ArrayBase<T>& array, uint size, uint begin, uint arrayBegin) {
		memcpy((void*)m_data + begin, array[arrayBegin], size);
	}

}