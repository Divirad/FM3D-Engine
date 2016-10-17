#pragma once
#include <Engine.h>

namespace ENGINE_NAME
{
	//"Z" coord, backgroundcolor, x, z, sizex, sizey
	Button::Button(uint p_color, float p_koordx, float p_koordy, float p_sizex, float p_sizey, float p_z) {
		SetPosition0(p_koordx, p_koordy, p_z);
		SetPosition1(p_koordx + p_sizex, p_koordy + p_sizey);
		SetColor(p_color);
		animation = false;
	}

	Button::Button(uint p_color, Texture *p_texture, float p_koordx, float p_koordy, float p_sizex, float p_sizey, float p_z ) {
		SetTexture(p_texture);
		SetPosition0(p_koordx, p_koordy, p_z);
		SetPosition1(p_koordx + p_sizex, p_koordy + p_sizey);
		
		SetUV0(p_koordx, p_koordy);
		SetUV1(p_koordx + p_sizex, p_koordy + p_sizey);

		SetColor(p_color);
	}

	Button::Button(uint p_color, Texture *p_texture, Vector3f p_koord, Vector2f p_size)	//Rischdisch
	{
		SetTexture(p_texture);
		SetPosition0(p_koord.x, p_koord.y, 0.0f);
		SetPosition1(p_koord.x - p_size.x, p_koord.y + p_size.y);

		m_uv0.x = 0.0f;
		m_uv0.y = 0.0f;
		m_uv1.x = 1.0f;
		m_uv1.y = 1.0f;

		SetColor(p_color);
	}

	Button::Button(Texture* p_texture, Vector2f p_koord ) {
		SetColor(0xffffffff);
		SetTexture(p_texture);
		SetPosition0(p_koord.x, p_koord.y, 0.0f);
		AutoSize();
	}

	//void Button::ChangeTexture(Texture *texture);
};

