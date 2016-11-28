#pragma once
#include <Engine.h>
namespace FM3D {

		PictureQuad::PictureQuad(Texture* txt, Vector3f pos0) {
			SetTexture(txt);
			m_uv0 = { 0.0f, 0.0f };
			m_uv1 = { 1.0f,1.0f };
			m_position0 = pos0;
			AutoSize();
			SetColor(0xffffffff);
		}
		PictureQuad::PictureQuad(Texture* txt, Vector3f pos0, Vector2f pos1) {
			SetTexture(txt);
			m_uv0 = { 0.0f, 0.0f };
			m_uv1 = { 1.0f,1.0f };
			m_position0 = pos0;
			m_position1 = pos1;
			SetColor(0xffffffff);
		}
		PictureQuad::PictureQuad(Texture* txt, Vector3f pos0, Vector2f pos1, uint color) {
			SetTexture(txt);
			m_position0 = pos0;
			m_uv0 = { 0.0f, 0.0f };
			m_uv1 = { 1.0f,1.0f };
			m_position1 = pos1;
			SetColor(color);
		}

}