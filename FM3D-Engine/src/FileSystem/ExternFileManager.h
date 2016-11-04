#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL ExternFileManager {
	private:
		static FT_Library s_ft;
	public:
		static bool Initialize();

		static bool ReadTextureFile(const char* filename, Texture* texture, Texture::FilterMode filterMode = Texture::LINEAR, Texture::WrapMode wrapMode = Texture::CLAMP, Texture::MipMapMode mipMapMode = Texture::NONE);
		static bool ReadFontFile(const char* filename, uint size, Vector2f scale, Texture* inTexture, Font** result);
		static void ReadModelFile(const char* filename, RenderSystem* renderSystem, Model** model, bool supportsInstancing, bool useAnimation = true, const Matrix4f& modelMatrix = Matrix4f::Identity());
		//static void ReadMeshFile(const char* filename, RenderSystem* renderSystem, Model** result);
	private:
		static BYTE* LoadImage(const char* filename, uint* width, uint* height, uint* bits);

		static bool PathName(const std::string in, std::string* name, std::string* end);
		static void ChangeChar(WCHAR* array, uint size, char search, char replace);
	};
}