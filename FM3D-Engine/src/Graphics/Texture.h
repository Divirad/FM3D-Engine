//#pragma once
#include <Engine.h>

namespace FM3D {

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
		enum MipMapMode {
			NONE,
			MIPMAP_NEAREST,
			MIPMAP_LINEAR
		};
	protected:
		uint m_width;
		uint m_height;
		uint m_bits;

		Texture() {};
		Texture(uint width, uint height, uint bits);
	public:
		virtual void Shutdown() = 0;

		uint GetBits() const { return m_bits; };
		uint GetWidth() const { return m_width; };
		uint GetHeight() const { return m_height; };

		virtual void BindForEditing() = 0;
		virtual void Unbind() const = 0;
		virtual void SetPixels(int level, int x, int y, int width, int height, unsigned char* pixels) = 0;
	};
}