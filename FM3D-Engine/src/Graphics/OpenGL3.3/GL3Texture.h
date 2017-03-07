#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL GL3Texture : public Texture {
	private:
		//Classes allowed to directly create Texture
		friend class ExternFileManager;
		friend class GL3RenderTarget2D;
		friend class GL3RenderSystem;
		friend class GL3RenderTarget2D;

		uint m_tID;

		GL3Texture(uint id, uint width, uint height, uint bits);
		GL3Texture(uint width, uint height, FilterMode filterMode, WrapMode wrapMode, MipMapMode mipMapMode, float* pixels, uint bits);
		GL3Texture(uint width, uint height, FilterMode filterMode, WrapMode wrapMode, MipMapMode mipMapMode, char* pixels, uint bits);
	public:
		void Shutdown() override;

		void Bind() const;
		void Unbind() const override;
		static void UnbindAll();

		void BindForEditing() override;
		void BindForReading() override;
		void SetPixels(int level, int x, int y, int width, int height, unsigned char* pixels) override;

		inline const uint GetID() const { return m_tID; }
	private:
		GLint GetGLFilterMode(FilterMode& filter, MipMapMode mipMap);
		GLint GetGLWrapMode(WrapMode& wrap);
		void SetParameters(FilterMode& filter, WrapMode& wrap, MipMapMode mipMapMode);
	};
}