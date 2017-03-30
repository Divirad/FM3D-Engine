#pragma once
#include <Engine.h>

namespace FM3D {

#define FILE_UNDEFINED	  0
#define FILE_TEXTURE	  1
#define FILE_FONT		  2
#define FILE_STATIC_MODEL 3

#define PAD_TOP 0
#define PAD_LEFT 2
#define PAD_BOTTOM 2
#define PAD_RIGHT 3

	class ENGINE_DLL FileManager {
	private:
		friend class ExternFileManager;

		static std::string resourcePath;
		static std::string enginePath;
		static std::string fileEnding;
	public:
		/*static void readStaticModelFile(std::string path, StaticModel::VertexData** data, uint** indices, int* indicesCount);

		static char* readTextureFile(std::string path, uint* width, uint* height, uint* bits);


		static Font* readFontFile(std::string path, const Renderer* renderer);
		*/
		static std::string ReadShaderFile(std::string filepath, const std::vector<std::string>& defines);

		static std::pair<uint, Mesh*> ReadMeshFile(std::string filepath, RenderSystem* renderSystem, const std::map<unsigned int, FM3D::Skeleton*>& map);

		static std::vector<std::vector<float>> ReadTerrainFile(std::string filepath);

		static void Initialize(std::string resourcePath, std::string enginePath, std::string fileEnding);
	private:
		/*static void readStaticModelFile(std::ifstream* file, StaticModel::VertexData** data, uint** indices, int* indicesCount);
		static char* readTextureFile(std::ifstream* file, uint* width, uint* height, uint* bits);
		static Font* readFontFile(std::ifstream* file, const Renderer* renderer);

		static Character loadCharacter(std::ifstream* file, int imageSize);


		static bool openFile(std::string path, int fileTypeInt, std::string fileTypename, std::ifstream* file);
		*/
	};
}