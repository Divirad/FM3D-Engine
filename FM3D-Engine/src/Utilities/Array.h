#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	template<class T>
	class Array {
	public:
	private:
		T* m_data;
		uint m_size;

	public:
		Array(uint count);
		Array(T* data, uint count);
		Array(std::initializer_list<T> data);
		Array(std::vector<T>& vec);
		Array(const std::vector<T>& vec);
		Array(const Array&) = delete;
		Array(SharedArray<T>&);
		~Array();

		T& operator[](uint i);
		const T& operator[](uint i) const;

		Array<T>& operator=(const std::vector<T>& vec);
		Array<T>& operator=(std::initializer_list<T> data);

		uint Size() const;

		const T* begin() const { return m_data; }
		const T* end() const { return m_data + m_size; }
		T* begin() { return m_data; }
		T* end() { return m_data + m_size; }

		SharedArray<T> Share();
		Array<T> CreateCopy();
		Array<T> CopyAndReset();
	};

	template<class T>				//using a byte array to prevent using standard constructor
	Array<T>::Array(uint count): m_data((T*) malloc(sizeof(T) * count)), m_size(count) {
	}

	template<class T>
	Array<T>::Array(T* data, uint count) : m_data(data), m_size(count) {
	}

	template<class T>				//using a byte array to prevent using standard constructor
	Array<T>::Array(std::initializer_list<T> data) : m_data((T*)malloc(sizeof(T) * count)), m_size((uint)data.size()) {
		memcpy(m_data, data.begin(), m_size * sizeof(T));
	}

	template<class T>
	Array<T>::Array(std::vector<T>& vec) : m_data(&vec[0]), m_size((uint)vec.size()) {
	}

	template<class T>
	Array<T>::Array(const std::vector<T>& vec) : m_data(&vec[0]), m_size((uint)vec.size()) {
	}

	template<class T>
	Array<T>::Array(SharedArray<T>& sa): m_data(sa.m_data), m_size(sa.m_size) {
		if (sa.m_mainArray != nullptr) throw std::exception("Created MainArray but is already existing");
		sa.m_mainArray = this;
	}

	template<class T>
	Array<T>::~Array() {
		if(m_data != nullptr) free(m_data);
	}

	template<class T>
	T& Array<T>::operator[](uint i) {
		return m_data[i];
	}

	template<class T>
	const T& Array<T>::operator[](uint i) const {
		return m_data[i];
	}

	template<class T>
	Array<T>& Array<T>::operator=(const std::vector<T>& vec) {
		this->m_data = vec[0];
		this->m_size = (uint)vec.size();
		return (*this);
	}

	template<class T>
	Array<T>& Array<T>::operator=(std::initializer_list<T> data) {
		this->m_data = data.begin();
		this->m_size = (uint)data.size();
		return (*this);
	}

	template<class T>
	inline uint Array<T>::Size() const {
		return m_size;
	}

	template<class T>
	SharedArray<T> Array<T>::Share() {
		return SharedArray<T>(m_data, m_size, this);
	}

	template<class T>
	Array<T> Array<T>::CreateCopy() {
		T* newData = newT[m_size * sizeof(T)];
		memcpy(newData, m_data, m_size * sizeof(T));
		return newData, m_size;
	}

	template<class T>
	Array<T> Array<T>::CopyAndReset() {
		T* oldData = m_data;
		m_data = nullptr;
		m_size = 0;
		return oldData, m_size;
	}
}