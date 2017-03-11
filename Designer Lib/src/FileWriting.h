#pragma once
#include <fstream>

namespace DesignerLib {

	template<typename T>
	void WriteRawToFile(std::ofstream& file, const T& t) {
		file.write(reinterpret_cast<const char*>(&t), sizeof(T));
	}

}