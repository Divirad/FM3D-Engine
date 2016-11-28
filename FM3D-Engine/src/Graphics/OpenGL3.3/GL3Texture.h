#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL GL3Texture : public Texture {
	private:
		friend class ExternFileManager;
		uint m_tID;
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