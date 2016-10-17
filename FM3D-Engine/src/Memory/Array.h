#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	template<class T>
	class Array : public ArrayBase<T> {
	public:
		Array(uint count);
		Array(const std::initializer_list<T>& data);
		Array(RawArray<T>& rawArray);

		Array(const Array<T>&) = delete;
		Array(Array<T>&&) = delete;
		Array<T>& operator=(const Array<T>&) = delete;
		~Array() { free(m_data); }
	};

	template<class T>
	Array<T>::Array(RawArray<T>& rawArray) : ArrayBase<T>(&rawArray[0], rawArray.Size()) {
		if (rawArray.IsCreated()) throw new std::exception("You can't create an Array from a already created RawArray!");
		rawArray.m_isCreated = true;
	}

	template<class T>
	Array<T>::Array(uint count) : ArrayBase<T>((T*)malloc(sizeof(T) * count), count) {
	}

	template<class T>
	Array<T>::Array(const std::initializer_list<T>& data) : ArrayBase<T>((T*)malloc(sizeof(T) * data.size()), (uint)data.size()) {
		memcpy((void*)m_data, data.begin(), m_size * sizeof(T));
	}
}