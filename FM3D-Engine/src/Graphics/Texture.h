//#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL Texture {
	public:
		enum WrapMode {
			REPEAT,
			CLAMP,
			MIRRORED_REPEAT,
			CLAMP_TO_EDGE,
			CLAMP_TO_BORDER
		};
		enum FilterMode {
			LINEAR,
			NEAREST
		};
	protected:
		uint m_width;
		uint m_height;
		uint m_bits;
	public:
		virtual void Initialize(uint width, uint height, FilterMode filterMode, WrapMode wrapMode, float* pixels, uint bits) = 0;
		virtual void Initialize(uint width, uint height, FilterMode filterMode, WrapMode wrapMode, char* pixels, uint bits) = 0;
		virtual void Shutdown() = 0;

		uint GetBits() const { return m_bits; };
		uint GetWidth() const { return m_width; };
		uint GetHeight() const { return m_height; };
	};
}