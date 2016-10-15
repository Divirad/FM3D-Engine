#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL GL3Texture : public Texture {
	private:
		friend class ExternFileManager;
		uint m_tID;
	public:
		void Initialize(uint width, uint height, FilterMode filterMode, WrapMode wrapMode, float* pixels, uint bits) override;
		void Initialize(uint width, uint height, FilterMode filterMode, WrapMode wrapMode, char* pixels, uint bits) override;

		void Shutdown() override;

		void Bind() const;
		static void Unbind();

		inline const uint GetID() const { return m_tID; }
	private:
		GLint GetGLFilterMode(FilterMode& filter);
		GLint GetGLWrapMode(WrapMode& wrap);
	};
}