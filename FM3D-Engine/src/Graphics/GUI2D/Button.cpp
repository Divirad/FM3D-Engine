#pragma once
#include <Engine.h>

namespace FM3D
{
	Button::Button(Texture* txt, Vector3f pos0)
	{
		SetTexture(txt);
		m_uv0 = { 0.0f, 0.0f };
		m_uv1 = { 1.0f,1.0f };
		m_position0 = pos0;
		AutoSize();
		SetColor(0xffffffff);
		ifinfield = ALREADY_OUTFIELD;
		clicked = Input::NOCLICK;
		animate = true;
	}

	Button::Button(Texture* txt, Vector3f pos0, Vector2f pos1) {
		SetTexture(txt);
		m_uv0 = { 0.0f, 0.0f };
		m_uv1 = { 1.0f,1.0f };
		m_position0 = pos0;
		m_position1 = pos1;
		SetColor(0xffffffff);
		ifinfield = ALREADY_OUTFIELD; 
		clicked = Input::NOCLICK;
		animate = true;
	}

	Button::Button(Texture* txt, Vector3f pos0, Vector2f pos1, uint color) {
		SetTexture(txt);
		m_position0 = pos0;
		m_uv0 = { 0.0f, 0.0f };
		m_uv1 = { 1.0f,1.0f };
		m_position1 = pos1;
		SetColor(color); 
		ifinfield = ALREADY_OUTFIELD;
		clicked = Input::NOCLICK;
		animate = true;
	}

	Button::Button(Texture* txt, Vector3f pos0, Vector2f pos1, uint color, bool animation) {
		SetTexture(txt);
		m_position0 = pos0;
		m_uv0 = { 0.0f, 0.0f };
		m_uv1 = { 1.0f,1.0f };
		m_position1 = pos1;
		SetColor(color);
		ifinfield = ALREADY_OUTFIELD;
		clicked = Input::NOCLICK;
		animate = animation;
	}

	void Button::Animation(bool in, float animsize) {
		if (in == true)
		{
			m_uv0 = Vector2f(m_uv0.x - animsize, m_uv0.y - animsize);
			m_uv1 = Vector2f(m_uv1.x + animsize, m_uv1.y + animsize);
		}
		else if (in == false) {
			m_uv0 = Vector2f(m_uv0.x + animsize, m_uv0.y + animsize);
			m_uv1 = Vector2f(m_uv1.x - animsize, m_uv1.y - animsize);
		}

	}

	bool Button::InFieldAnimation() {
		
		//ccresult = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastpos());
		///
		///INTO FIELD
		///
		if (FieldCecker()==INFIELD && ifinfield == ALREADY_OUTFIELD) {

			ifinfield = INFIELD;
			if(animate==true){ Animation(true, INFIELDANIM); }
			return MOUSE_INFIELD;
		}

		///
		///IN FIELD
		///
		else if (FieldCecker() == INFIELD && ifinfield == INFIELD) {

			ifinfield = ALREADY_INFIELD;
		}

		///
		///OUT OF FIELD
		///
		else if	(FieldCecker()==OUTFIELD && ifinfield == ALREADY_INFIELD) {

			ifinfield = OUTFIELD;
			if (animate == true) { Animation(false, INFIELDANIM); }
		}
		else if(FieldCecker() == OUTFIELD && ifinfield == INFIELD) {

			ifinfield = OUTFIELD;
			if (animate == true) {Animation(false, INFIELDANIM);}
			return MOUSE_OUTOFFIELD;
		}

		///
		///ALREADY OUT OF FIELD
		///
		else if	(FieldCecker()==OUTFIELD &&	ifinfield == OUTFIELD) {

			ifinfield = ALREADY_OUTFIELD;
		}
		return MOUSE_OUTOFFIELD;
	}

	bool Button::InFieldAnimation(float animsize) {

		//ccresult = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastpos());
		///
		///INTO FIELD
		///
		if (FieldCecker() == INFIELD && ifinfield == ALREADY_OUTFIELD) {

			ifinfield = INFIELD;
			if (animate == true) { Animation(true, animsize); }
			return MOUSE_INFIELD;
		}

		///
		///IN FIELD
		///
		else if (FieldCecker() == INFIELD && ifinfield == INFIELD) {

			ifinfield = ALREADY_INFIELD;
		}

		///
		///OUT OF FIELD
		///
		else if (FieldCecker() == OUTFIELD && ifinfield == ALREADY_INFIELD) {

			ifinfield = OUTFIELD;
			if (animate == true) { Animation(false, animsize); }
		}
		else if (FieldCecker() == OUTFIELD && ifinfield == INFIELD) {

			ifinfield = OUTFIELD;
			if (animate == true) { Animation(false, INFIELDANIM); }
			return MOUSE_OUTOFFIELD;
		}

		///
		///ALREADY OUT OF FIELD
		///
		else if (FieldCecker() == OUTFIELD &&	ifinfield == OUTFIELD) {

			ifinfield = ALREADY_OUTFIELD;
		}
		return MOUSE_OUTOFFIELD;
	}

	bool Button::ClickAnimation(int keyID) {

		if (ccRectangle(keyID) == Input::ACTIVATED /*&& clicked==false*/) {

			/*clicked = true;*/
			if (animate == true) { Animation(true, INFIELDANIM); }

			std::cout << "INPUT:: BUT:: CLICKED";
			return true;
		}

		else if (ccRectangle(keyID) == Input::RELEASED /*&& clicked == true*/) {
			//clicked = false;
			if (animate == true) { Animation(false, INFIELDANIM); }
			std::cout << "INPUT:: BUT:: RELEASED";
			//Window::GetInstance()->GetInput().SetMKey(keyID, Input::NOCLICK);
			return false;
		}
		return MOUSE_OUTOFFIELD;

	}

}

