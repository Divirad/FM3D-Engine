#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL Quad {
	protected:
		Vector3f m_position0;
		Vector2f m_position1;
		uint m_color;
		Texture* m_texture;
		Vector2f m_uv0;
		Vector2f m_uv1;
	public:
		Quad(Vector3f position, Vector2f size, uint color, Texture* tex, Vector2f uvposition, Vector2f uvsize) :
			m_position0(position), m_position1(Vector2f(position.x + size.x, position.y + size.y)), m_color(color), m_texture(tex), m_uv0(uvposition), m_uv1(uvposition + uvsize) {};
			Quad(Vector3f position, Vector2f size, uint color, Texture* tex) :
				m_position0(position), m_position1(Vector2f(position.x + size.x, position.y + size.y)), m_color(color), m_texture(tex), m_uv0(Vector2f(0.0f, 0.0f)), m_uv1(Vector2f(1.0f, 1.0f)) {};

			Quad() {}; 

#pragma region GET

			inline Vector3f GetPosition0() { return m_position0; }
			inline Vector3f GetPosition1() { return Vector3f(m_position1.x, m_position1.y, m_position0.z); }
			inline Vector3f GetPosition2() { return Vector3f(m_position0.x, m_position1.y, m_position0.z); }
			inline Vector3f GetPosition3() { return Vector3f(m_position1.x, m_position0.y, m_position0.z); }

			inline Vector3f GetPos0() { return m_position0; }
			inline Vector3f GetPos1() { return Vector3f(m_position1, m_position0.z); }

			inline uint GetColor() { return m_color; }
			inline Texture* GetTexture() { return m_texture; }

			inline Vector2f GetUV0() { return m_uv0; }
			inline Vector2f GetUV1() { return m_uv1; }
			inline Vector2f GetUV2() { return Vector2f(m_uv0.x, m_uv1.y); }
			inline Vector2f GetUV3() { return Vector2f(m_uv1.x, m_uv0.y); }

			inline uint GetTextureWidth() { return m_texture->GetWidth(); }
			inline uint GetTextureHeight() { return m_texture->GetHeight(); }

#pragma endregion


#pragma region Set
			inline void SetZ(float z) { m_position0.z = z; }

			inline void SetPosition0(Vector3f vec) { m_position0 = vec; }
			inline void SetPosition0(float x, float y, float z) { m_position0.x = x; m_position0.y = y; m_position0.z = y; }

			inline void SetPosition1(Vector2f vec) { m_position1 = vec; }
			inline void SetPosition1(float x, float y) { m_position1.x = x; m_position1.y = y; }

			void SetSize(const Vector2f &vec);
			void SetSize(int x, int y);

			inline void SetColor(uint color) { m_color = color; }
			inline void SetTexture(Texture* tex) { m_texture = tex; }

			inline void SetUV0(Vector2f vec) { m_uv0 = vec; }
			inline void SetUV0(float x, float y) { m_uv0.x = x; m_uv0.y = y; }
			inline void SetUV1(Vector2f vec) { m_uv1 = vec; }
			inline void SetUV1(float x, float y) { m_uv1.x = x; m_uv1.y = y; }
#pragma endregion
		
	};
}