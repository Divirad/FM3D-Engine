#pragma once
#include <fstream>
#include <string>
#include "Dll.h"

namespace DesignerLib {

	template<typename T>
	void WriteRawToFile(std::ofstream& file, const T& t) {
		file.write(reinterpret_cast<const char*>(&t), sizeof(T));
	}

	template<typename T>
	T ReadRawFromFile(std::ifstream& file) {
		char buffer[sizeof(T)];
		file.read(buffer, sizeof(T));
		return *reinterpret_cast<T*>(buffer);
	}

	template<>
	inline std::string ReadRawFromFile<std::string>(std::ifstream& file) {
		int length = ReadRawFromFile<int>(file);
		char* buffer = new char[length+1];
		file.read(buffer, length);
		buffer[length] = 0; //Set Nullbyte
		std::string result = buffer;
		delete buffer;
		return result;
	}

}