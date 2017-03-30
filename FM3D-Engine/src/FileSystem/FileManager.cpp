#include <Engine.h>

namespace FM3D {

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
		char* buffer = new char[length + 1];
		file.read(buffer, length);
		buffer[length] = 0; //Set Nullbyte
		std::string result = buffer;
		delete buffer;
		return result;
	}

	using namespace std;

	string FileManager::resourcePath;
	string FileManager::enginePath;
	string FileManager::fileEnding;
	
	void FileManager::Initialize(std::string resourcePath, std::string enginePath, std::string fileEnding) {
		FileManager::resourcePath = resourcePath;
		FileManager::enginePath = enginePath;
		FileManager::fileEnding = fileEnding;
	}

	static string ReadShader(ifstream& f, const vector<string>& defines) {
		static const string d_if = "#if ";
		static const string d_else = "#else";
		static const string d_end = "#end";

		string str = "";
		string line;
		while (f && getline(f, line)) {
			if (line.substr(0, d_if.length()) == d_if) {	//If occured
				string def = line.substr(d_if.length());
				if (find(defines.begin(), defines.end(), def) != defines.end()) {
					str += ReadShader(f, defines);	//Read if
				}
				else {
					uint ifBlocks = 0;
					while (f && getline(f, line)) {
						if (line.substr(0, d_else.length()) == d_else) {
							if (ifBlocks == 0) {
								str += ReadShader(f, defines);	//Read else
								break;
							}
						}
						else if (line.substr(0, d_end.length()) == d_end) {
							if(ifBlocks == 0) break; //Jumped to end
							else ifBlocks--;
						}
						else if (line.substr(0, d_if.length()) == d_if) { //If occured
							ifBlocks++;
						}
					}
				}
			} 
			else if (line.substr(0, d_else.length()) == d_else) { //Else occured
				while (f && getline(f, line)) {
					if (line.substr(0, d_end.length()) == d_end) {
						break; //Jumped to end
					}
				}
			}
			else if (line.substr(0, d_end.length()) == d_end) { //End occured
				break; //Block ended
			}
			else { //Nomal line
				str += line + '\n';
			}
		}
		return str;
	}

	std::string FileManager::ReadShaderFile(std::string filepath, const vector<string>& defines) {
		filepath = enginePath + filepath;
		string result;
		ifstream file(filepath);
		if (file.is_open()) {
			string result = ReadShader(file, defines);
			file.close();
			return result;
		}
		else {
			throw std::runtime_error("Can not open shader file " + filepath);
		}
	}

	std::pair<uint, Mesh*> FileManager::ReadMeshFile(std::string filepath, RenderSystem* renderSystem, const std::map<unsigned int, FM3D::Skeleton*>& map) {
		std::ifstream file(filepath);
		if (!file.is_open()) throw std::runtime_error("Cant open mesh file");

		bool isDesignerFile = false;
		byte type = ReadRawFromFile<byte>(file);	//File type
		if (type == 5) isDesignerFile = true;
		else if (type != 3) throw std::runtime_error("File is not a mesh file!");
		unsigned int resourceId = ReadRawFromFile<unsigned int>(file); //Resource ID
		std::string name = "Unknown";
		if (isDesignerFile)
			name = ReadRawFromFile<std::string>(file);	//Name
		unsigned int skeletonId = ReadRawFromFile<unsigned int>(file); //Skeleton ID
		bool supportsInstancing = ReadRawFromFile<bool>(file);	//Supports instancing
		int partsCount = ReadRawFromFile<int>(file); //Parts Count
		std::vector<MeshPart> parts;
		for (int i = 0; i < partsCount; i++) {
			std::string pname = "Unknown";
			if (isDesignerFile)
				pname = ReadRawFromFile<std::string>(file);	//Part Name

			uint indicesCount = ReadRawFromFile<uint>(file);
			uint indexSize = ReadRawFromFile<uint>(file);
			char* indices = new char[indicesCount * indexSize];
			file.read(indices, indicesCount * indexSize); //Indices
			uint vertexCount = ReadRawFromFile<uint>(file);
			uint vertexData = ReadRawFromFile<uint>(file);

			Vertices vertices(vertexCount, vertexData);
			char* verticesData = new char[vertexCount * vertices.GetVertexSize()];
			file.read(verticesData, vertexCount * vertices.GetVertexSize()); //Vertices
			vertices.SetData(reinterpret_cast<FM3D::byte*>(verticesData));

			bool psupportsInstancing = ReadRawFromFile<bool>(file);

			parts.emplace_back(indicesCount, (void*)indices, std::move(vertices), indexSize, psupportsInstancing);
		}

		return std::make_pair(resourceId, renderSystem->CreateMesh(map.at(skeletonId), supportsInstancing, parts));
	}

	std::vector<std::vector<float>> FileManager::ReadTerrainFile(std::string filepath) {
		string path = FileManager::resourcePath + filepath;

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = nullptr;
		fif = FreeImage_GetFileType(path.c_str(), 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(path.c_str());
		if (fif == FIF_UNKNOWN) {
			OUTPUT_ERROR(1, "Filemanager Error", filepath + " has unknown image format");
			return std::vector<std::vector<float>>();
		}

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, path.c_str());

		//MessageBox(hWnd, filename, "Could not load image '", MB_OK);

		BYTE* pixels = FreeImage_GetBits(dib);
		uint width = FreeImage_GetWidth(dib);
		uint height = FreeImage_GetHeight(dib);
		uint bits = FreeImage_GetBPP(dib);

		uint size = width * height * (bits / 8);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(dib);

		if (result == NULL) {
			OUTPUT_ERROR(1, "Filemanager Error", "can't read "+ filepath);
			return std::vector<std::vector<float>>();
		}

		std::vector<std::vector<float>> heights(width, std::vector<float>(height));

		for (size_t i = 0U; i < size; i += 4) {
			float* f = reinterpret_cast<float*>(result + i);
			heights[i / width][i % width] = *f;
		}

		return heights;
	}

	/*
	void FileManager::readStaticModelFile(string path, StaticModel::VertexData** data, uint** indices, int* indicesCount) {
		path = resourcePath + path;
		ifstream* file = new ifstream();
		file->open(path, ios::in);
		//if (!openFile(path, FILE_STATIC_MODEL, "Static Model", file)) return;
		readStaticModelFile(file, data, indices, indicesCount);
		file->close();
		return;
	}

	void FileManager::readStaticModelFile(ifstream* file, StaticModel::VertexData** data, uint** indices, int* indicesCount) {
		vector<Vector3f> vVertices;
		vector<Vector2f> vTexCoords;
		vector<Vector3f> vNormals;
		vector<int> vIndices;

		string line;
		while (getline(*file, line)) {
			if (line.substr(0, 2) == "v ") {
				istringstream s(line.substr(2));
				Vector3f v;
				s >> v.x;
				s >> v.y;
				s >> v.z;
				vVertices.push_back(v);
			} else if (line.substr(0, 3) == "vt ") {
				istringstream s(line.substr(2));
				Vector2f v;
				s >> v.x;
				s >> v.y;
				vTexCoords.push_back(v);
			} else if (line.substr(0, 3) == "vn ") {
				istringstream s(line.substr(2));
				Vector3f v;
				s >> v.x;
				s >> v.y;
				s >> v.z;
				vNormals.push_back(v);
			} else if (line.substr(0, 2) == "f ") {
				*data = new StaticModel::VertexData[vVertices.size()];
				break;
			}
		}

		do {
			if (!(line.substr(0, 2) == "f ")) {
				continue;
			}
			istringstream s(line.substr(2));
			istringstream s2;
			for (int i = 0; i < 3; i++) {
				int vertexPointer, texturePointer, normalPointer;
				s >> vertexPointer;
				s.ignore(s.str().length(), '/');
				s >> texturePointer;
				s.ignore(s.str().length(), '/');
				s >> normalPointer;

				vertexPointer--;
				texturePointer--;
				normalPointer--;

				vIndices.push_back(vertexPointer);
				((*data)[vertexPointer]).uv = vTexCoords[texturePointer];
				((*data)[vertexPointer]).normal = vNormals[normalPointer];
			}
		} while (getline(*file, line));

		*indices = new uint[vIndices.size()];

		int vertexPointer = 0;
		for (Vector3f vertex : vVertices) {
			((*data)[vertexPointer++]).position = vertex;
		}

		for (int i = 0; i < (int)vIndices.size(); i++) {
			(*indices)[i] = vIndices[i];
		}

		*indicesCount = vIndices.size();
	}

	string FileManager::readShaderFile(string path) {
		path = enginePath + path;
		FILE* file;
		fopen_s(&file, path.c_str(), "rt");
		if (file == nullptr) {
			wchar_t* wtext = new wchar_t[path.length()];
			mbstowcs(wtext, path.c_str(), path.length());
			MessageBox(NULL, wtext, L"Error", MB_OK | MB_ICONERROR);
		}
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		string result(data);
		delete[] data;
		return result;
	}

	char* FileManager::readTextureFile(string path, uint* width, uint* height, uint* bits) {
		path = resourcePath + path;
		ifstream* file = new ifstream();
		file->open(path, ios::in | ios::binary);
		if (!openFile(path, FILE_TEXTURE, "Texture", file)) {
			file->close();
			return 0;
		}
		char* result = readTextureFile(file, width, height, bits);
		file->close();
		return result;
	}

	char* FileManager::readTextureFile(ifstream* file, uint* width, uint* height, uint* bits) {
		char* tmp = new char[4];
		file->read((char*)width, 4);
		file->read((char*)height, 4);
		file->read((char*)bits, 4);

		int size = *width * *height * (*bits / 8);
		char* result = new char[size];
		if (!file->read(result, size)) cout << "Error on reading!" << endl;

		delete[] tmp;

		return result;
	}

	//Font* FileManager::readFontFile(string path, const basic::Renderer* renderer) {
	//	path = resourcePath + path;
	//	ifstream* file = new ifstream();
	//	file->open(path, ios::in | ios::binary);
	//	if (!openFile(path, FILE_FONT, "Font", file)) return 0;
	//	Font* result = readFontFile(file, renderer);
	//	file->close();
	//	return result;
	//}

	//Font* FileManager::readFontFile(ifstream* file, RendererSystem* renderer) {
	//	char* tmp = new char[4];

	//	float x, y;
	//	file->read(tmp, 4);
	//	TypeConverter::charsToFloat(tmp, &x);
	//	file->read(tmp, 4);
	//	TypeConverter::charsToFloat(tmp, &y);
	//	Vector2f scale(x, y);

	//	Character* chars = new Character[CHARACTER_COUNT];
	//	for (int i = 0; i < CHARACTER_COUNT; i++) {
	//		float offsetX, advanceX, advanceY, left, top, width, height;
	//		file->read(tmp, 4);
	//		TypeConverter::charsToFloat(tmp, &advanceY);
	//		file->read(tmp, 4);
	//		TypeConverter::charsToFloat(tmp, &advanceX);
	//		file->read(tmp, 4);
	//		TypeConverter::charsToFloat(tmp, &height);
	//		file->read(tmp, 4);
	//		TypeConverter::charsToFloat(tmp, &width);
	//		file->read(tmp, 4);
	//		TypeConverter::charsToFloat(tmp, &left);
	//		file->read(tmp, 4);
	//		TypeConverter::charsToFloat(tmp, &top);
	//		file->read(tmp, 4);
	//		TypeConverter::charsToFloat(tmp, &offsetX);
	//		chars[i] = { advanceX, advanceY, width, height, left, top, offsetX, };
	//	}
	//	uint width, height, bits;
	//	file->read(tmp, 4);
	//	TypeConverter::charsToUint(tmp, &width);
	//	file->read(tmp, 4);
	//	TypeConverter::charsToUint(tmp, &height);
	//	file->read(tmp, 4);
	//	TypeConverter::charsToUint(tmp, &bits);
	//	int size = width * height * (bits / 8);
	//	char* pixels = new char[size];
	//	file->read(pixels, size);
	//	bTexture* tex = renderer->createTexture(width, height, CLAMP, NEAREST, pixels, bits);

	//	delete[] tmp;

	//	return new Font(chars, scale, tex);
	//}

	Character FileManager::loadCharacter(ifstream* file, int imageSize) {
		char* tmp = new char[8];

		delete[] tmp;
		return Character();
	}

	bool FileManager::openFile(string path, int fileTypeInt, string fileTypeName, ifstream* file) {
		if (path.find(fileEnding) != string::npos) {
			if (file->is_open()) {
				file->seekg(0, ios::beg);
				int filetype = 0;
				if (!file->read((char*)&filetype, 4)) cout << "Error on reading!" << endl;
				if (filetype == fileTypeInt) {
					return true;
				} else {
					cout << fileTypeName << " file is no Engine-" << fileTypeName << "- File! Type:" << filetype << endl;
					file->close();
					return false;
				}
			} else {
				cout << "Unable to open " << fileTypeName << " file!" << endl;
				return false;
			}
		} else {
			cout << fileTypeName << " file is no Engine-File!" << endl;
			return false;
		}
	}
	*/
}