#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	template<class T>
	class DynamicArray : public DynamicArrayBase<T> {
	public:
		DynamicArray(uint count);
		DynamicArray(const std::initializer_list<T>& data);
		DynamicArray(RawArray<T>& rawArray);

		DynamicArray(const DynamicArray<T>&) = delete;
		DynamicArray(DynamicArray<T>&&) = delete;
		DynamicArray<T>& operator=(const DynamicArray<T>&) = delete;
		~DynamicArray() { free(m_data); }
	};

	template<class T>
	DynamicArray<T>::DynamicArray(RawArray<T>& rawArray) : DynamicArrayBase<T>(&rawArray[0], rawArray.Size(), rawArray.Size()) {
		if (rawArray.IsCreated()) throw new std::exception("You can't create an Array from a already created RawArray!");
		rawArray.m_isCreated = true;
	}

	template<class T>
	DynamicArray<T>::DynamicArray(uint count) : DynamicArrayBase<T>((T*)malloc(sizeof(T) * count), count, count) {
	}

	template<class T>
	DynamicArray<T>::DynamicArray(const std::initializer_list<T>& data) : DynamicArrayBase<T>((T*)malloc(sizeof(T) * data.size()), (uint)data.size(), (uint)data.size()) {
		memcpy((void*)m_data, data.begin(), m_size * sizeof(T));
	}
}