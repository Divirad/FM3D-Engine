#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Quad {
	protected:
		Vector3f m_position0;
		Vector2f m_position1;
		uint m_color;
		Texture* m_texture;
		Vector2f m_uv0;	
		Vector2f m_uv1;

	public:
		Quad(Vector3f position, Vector2f size, uint color, Texture* tex) :
			m_position0(position), m_position1(Vector2f(position.x + size.x, position.y + size.y)), m_color(color), m_texture(tex), m_uv0(Vector2f(0.0f, 0.0f)), m_uv1(Vector2f(1.0f, 1.0f)) {};

		Quad(Vector3f position, Vector2f size, uint color, Texture* tex, Vector2f uvposition, Vector2f uvsize) :
			m_position0(position), m_position1(Vector2f(position.x + size.x, position.y + size.y)), m_color(color), m_texture(tex), m_uv0(uvposition), m_uv1(uvposition + uvsize) {};
		
		Quad() {}; 

#pragma region GET

			inline Vector3f GetPosition0() { return m_position0; }
			inline Vector2f GetPosition1() { return m_position1; }

			inline uint GetColor() { return m_color; }
			inline Texture* GetTexture() { return m_texture; }

			inline Vector2f GetUV0() { return m_uv0; }
			inline Vector2f GetUV1() { return m_uv1; }

			inline uint GetTextureWidth() { return m_texture->GetWidth(); }
			inline uint GetTextureHeight() { return m_texture->GetHeight(); }

#pragma endregion


#pragma region Set
			inline void SetPosition0(Vector3f vec) { m_position0 = vec; }

			inline void SetPosition1(Vector2f vec) { m_position1.x = vec.x; m_position1.y = vec.y;}

			void SetSize(const Vector2f &vec);

			inline void SetColor(uint color) { m_color = color; }
			inline void SetTexture(Texture* tex) { m_texture = tex; }

			inline void SetUV0(Vector2f vec) { m_uv0 = vec; }
			inline void SetUV1(Vector2f vec) { m_uv1 = vec; }
#pragma endregion
	};
}