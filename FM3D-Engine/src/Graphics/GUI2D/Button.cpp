#pragma once
#include <Engine.h>

namespace ENGINE_NAME
{
	//"Z" coord, backgroundcolor, x, z, sizex, sizey
	Button::Button(uint p_color, float p_koordx, float p_koordy, float p_sizex, float p_sizey, float p_z) {
		m_box.SetPosition0(p_koordx, p_koordy, p_z);
		m_box.SetPosition1(p_koordx + p_sizex, p_koordy + p_sizey);
		m_box.SetColor(p_color);
		animation = false;
	}

	Button::Button(uint p_color, Texture *p_texture, float p_koordx, float p_koordy, float p_sizex, float p_sizey, float p_z ) {
		m_box.SetTexture(p_texture);
		m_box.SetPosition0(p_koordx, p_koordy, p_z);
		m_box.SetPosition1(p_koordx + p_sizex, p_koordy + p_sizey);

		m_box.SetUV0(p_koordx, p_koordy);
		m_box.SetUV1(p_koordx + p_sizex, p_koordy + p_sizey);

		m_box.SetColor(p_color);
		animation = false;
	}

	Button::Button(uint p_color, Texture *p_texture, Vector2f p_koord, Vector2f p_size, float p_z)
	{
		m_box.SetTexture(p_texture);
		m_box.SetPosition0(p_koord.x, p_koord.y, p_z);
		m_box.SetPosition1(p_koord.x + p_size.x, p_koord.y + p_size.y);

		m_box.SetUV0(p_koord.x, p_koord.y);
		m_box.SetUV1(p_koord.x + p_size.x, p_koord.y + p_size.y);

		m_box.SetColor(p_color);
		animation = false;
	}

	Button::Button(Texture* p_texture, Vector2f koord ) {
		m_box.SetColor(0xffffffff);
		m_box.SetTexture(p_texture);
		m_box.SetPosition0(koord.x, koord.y, 1);
		AutoSize();
	}

	//void Button::ChangeTexture(Texture *texture);
};

