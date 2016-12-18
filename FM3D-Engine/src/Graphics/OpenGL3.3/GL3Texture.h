#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL GL3Texture : public Texture {
	private:
		friend class ExternFileManager;
		friend class GL3RenderTarget2D;
		friend class GL3RenderSystem;
		uint m_tID;

		GL3Texture(uint id, uint width, uint height, uint bits);
		GL3Texture();
	public:
		void Initialize(uint width, uint height, FilterMode filterMode, WrapMode wrapMode, MipMapMode mipMapMode, float* pixels, uint bits) override;
		void Initialize(uint width, uint height, FilterMode filterMode, WrapMode wrapMode, MipMapMode mipMapMode, char* pixels, uint bits) override;

		void Shutdown() override;

		void Bind() const;
		static void Unbind();

		inline const uint GetID() const { return m_tID; }
	private:
		GLint GetGLFilterMode(FilterMode& filter, MipMapMode mipMap);
		GLint GetGLWrapMode(WrapMode& wrap);
		void SetParameters(FilterMode& filter, WrapMode& wrap, MipMapMode mipMapMode);
	};
}