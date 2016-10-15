#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	template<class T>
	class Array;

	template<class T>
	class SharedArray {
	private:
		friend class Array<T>;

		T* m_data;
		uint m_size;
		Array<T>* m_mainArray;
		SharedArray(T* data, uint count, Array<T>* mainArray);
		void SetMainArray(Array<T>* value);
	public:
		SharedArray(uint count);
		SharedArray(T* data, uint count);
		SharedArray(std::initializer_list<T> data);
		SharedArray(std::vector<T>& vec);
		SharedArray(const std::vector<T>& vec);

		T& operator[](uint i);
		const T& operator[](uint i) const;

		SharedArray<T>& operator=(const std::vector<T>& vec);
		SharedArray<T>& operator=(std::initializer_list<T> data);

		uint Size();

		const T* begin() const { return m_data; }
		const T* end() const { return m_data + m_size; }
		T* begin() { return m_data; }
		T* end() { return m_data + m_size; }

		SharedArray<T> Share();
		bool HasMainArray();
		Array<T>* GetMainArray();
	};

	template<class T>				//using a byte array to prevent using standard constructor
	SharedArray<T>::SharedArray(uint count) : m_data((T*) new byte[sizeof(T) * count]), m_size(count), m_mainArray(nullptr) {

	}

	template<class T>
	SharedArray<T>::SharedArray(T* data, uint count) : m_data(data), m_size(count), m_mainArray(nullptr) {
	}

	template<class T>				//using a byte array to prevent using standard constructor
	SharedArray<T>::SharedArray(std::initializer_list<T> data) : m_data((T*) new byte[sizeof(T) * data.size()]), m_size((uint)data.size()), m_mainArray(nullptr) {
		memcpy(m_data, data.begin(), m_size * sizeof(T));
	}

	template<class T>
	SharedArray<T>::SharedArray(std::vector<T>& vec) : m_data(&vec[0]), m_size((uint)vec.size()), m_mainArray(nullptr) {
	}

	template<class T>
	SharedArray<T>::SharedArray(const std::vector<T>& vec) : m_data(&vec[0]), m_size((uint)vec.size()), m_mainArray(nullptr) {
	}

	template<class T>
	SharedArray<T>::SharedArray(T* data, uint count, Array<T>* mainArray) : m_data(data), m_size(count), m_mainArray(mainArray) {

	}

	template<class T>
	T& SharedArray<T>::operator[](uint i) {
		return m_data[i];
	}

	template<class T>
	const T& SharedArray<T>::operator[](uint i) const {
		return m_data[i];
	}

	template<class T>
	SharedArray<T>& SharedArray<T>::operator=(const std::vector<T>& vec) {
		this->m_data = vec[0];
		this->m_size = (uint)vec.size();
		return (*this);
	}

	template<class T>
	SharedArray<T>& SharedArray<T>::operator=(std::initializer_list<T> data) {
		this->m_data = data.begin();
		this->m_size = (uint)data.size();
		return (*this);
	}

	template<class T>
	inline uint SharedArray<T>::Size() {
		return m_size;
	}

	template<class T>
	SharedArray<T> SharedArray<T>::Share() {
		return m_data, m_size, m_mainArray;
	}

	template<class T>
	bool SharedArray<T>::HasMainArray() {
		return m_mainArray != nullptr;
	}

	template<class T>
	Array<T>* SharedArray<T>::GetMainArray() {
		return m_mainArray;
	}

	template<class T>
	void SharedArray<T>::SetMainArray(Array<T>* value) {
		m_mainArray = value;
	}
}