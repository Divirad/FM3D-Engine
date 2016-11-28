#pragma once
#include <Engine.h>

namespace FM3D {

	template<class T>
	class Array;

	template<class T>
	class RawArray : public ArrayBase<T> {
		friend class Array<T>;
	private:
		bool m_isCreated;
	public:
		RawArray(uint count);
		RawArray(std::initializer_list<T>& data);
		RawArray(DynamicRawArray<T>& rawArray);

		RawArray(RawArray<T>& other) : m_isCreated(other.m_isCreated), ArrayBase<T>(other.m_data, other.m_size) {
			other.m_isCreated = true;
		};
		RawArray(RawArray<T>&& other) : m_isCreated(other.m_isCreated), ArrayBase<T>(other.m_data, other.m_size) {
			other.m_isCreated = true;
		};
		RawArray<T>& operator=(const RawArray<T>&) = delete;
		~RawArray() {
			if (!m_isCreated) {
				std::cout << "RawArray never was created!" << std::endl;
			}
		}

		bool IsCreated() const { return m_isCreated; }
	};

	template<class T>
	RawArray<T>::RawArray(uint count) : m_isCreated(false), ArrayBase<T>((T*)malloc(sizeof(T) * count), count) {
	}

	template<class T>
	RawArray<T>::RawArray(DynamicRawArray<T>& rawArray): m_isCreated(false), ArrayBase<T>(&rawArray[0], rawArray.Size()) {
		if (rawArray.IsCreated()) throw new std::exception("You can't create an Array from a already created DynamicRawArray!");
		rawArray.m_isCreated = true;
	}

	template<class T>
	RawArray<T>::RawArray(std::initializer_list<T>& data) : m_isCreated(false), ArrayBase<T>((T*)malloc(sizeof(T) * data.size()), (uint)data.size()) {
		memcpy((void*)m_data, data.begin(), m_size * sizeof(T));
	}
}