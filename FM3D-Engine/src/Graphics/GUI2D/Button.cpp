#pragma once
#include <Engine.h>

namespace ENGINE_NAME
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
		animate = animation;
	}

	void Button::Animation(FieldCheck isin, float animsize) {
		if (isin == INFIELD)
		{
			m_uv0 = Vector2f(m_uv0.x - animsize, m_uv0.y - animsize);
			m_uv1 = Vector2f(m_uv1.x + animsize, m_uv1.y + animsize);
		}
		else if (isin == OUTFIELD) {
			m_uv0 = Vector2f(m_uv0.x + animsize, m_uv0.y + animsize);
			m_uv1 = Vector2f(m_uv1.x - animsize, m_uv1.y - animsize);
		}

	}

	bool Button::InFieldAnimation() {
		
		ccresult = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastpos());
		///
		///INTO FIELD
		///
		if (GetPosition0().xy <= ccresult &&
			   GetPosition1() >= ccresult &&
			ifinfield == ALREADY_OUTFIELD) {

			ifinfield = INFIELD;
			if(animate==true){ Animation(ifinfield, INFIELDANIM); }
			
			std::cout << "INPUT:: QUD:: IN FIELD\n";
			return MOUSE_INFIELD;
		}

		///
		///IN FIELD
		///
		else if 
			(GetPosition0().xy < ccresult &&
			    GetPosition1() > ccresult &&
			ifinfield == INFIELD) {

			ifinfield = ALREADY_INFIELD;
			std::cout << "INPUT:: QUD:: ALREADY IN FIELD\n";
		}

		///
		///OUT OF FIELD
		///
		else if
			(!(GetPosition0().xy < ccresult &&
				GetPosition1() > ccresult) &&
				ifinfield == ALREADY_INFIELD) {

			ifinfield = OUTFIELD;
			if (animate == true) { Animation(ifinfield, INFIELDANIM); }
			std::cout << "INPUT:: QUD:: OUT OF FIELD\n";
		}
		else if
			(!(GetPosition0().xy < ccresult &&
				GetPosition1() > ccresult) &&
				ifinfield == INFIELD) {

			ifinfield = OUTFIELD;
			Animation(ifinfield, INFIELDANIM);
			std::cout << "INPUT:: QUD:: OUT OF FIELD\n";
			return MOUSE_OUTOFFIELD;
		}

		///
		///ALREADY OUT OF FIELD
		///
		else if
			(!(GetPosition0().xy < ccresult &&
				GetPosition1() > ccresult) &&
				ifinfield == OUTFIELD) {

			ifinfield = ALREADY_OUTFIELD;
			std::cout << "INPUT:: QUD:: ALREADY OUT OF FIELD\n";
		}
	}
	bool Button::InFieldAnimation(float animsize) {

		ccresult = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastpos());
		///
		///INTO FIELD
		///
		if (GetPosition0().xy <= ccresult &&
			GetPosition1() >= ccresult &&
			ifinfield == ALREADY_OUTFIELD) {

			ifinfield = INFIELD;
			if (animate == true) { Animation(ifinfield, animsize); }

			std::cout << "INPUT:: QUD:: IN FIELD\n";
			return MOUSE_INFIELD;
		}

		///
		///IN FIELD
		///
		else if
			(GetPosition0().xy < ccresult &&
				GetPosition1() > ccresult &&
				ifinfield == INFIELD) {

			ifinfield = ALREADY_INFIELD;
			std::cout << "INPUT:: QUD:: ALREADY IN FIELD\n";
		}

		///
		///OUT OF FIELD
		///
		else if
			(!(GetPosition0().xy < ccresult &&
				GetPosition1() > ccresult) &&
				ifinfield == ALREADY_INFIELD) {

			ifinfield = OUTFIELD;
			if (animate == true) { Animation(ifinfield, animsize); }
			std::cout << "INPUT:: QUD:: OUT OF FIELD\n";
		}
		else if
			(!(GetPosition0().xy < ccresult &&
				GetPosition1() > ccresult) &&
				ifinfield == INFIELD) {

			ifinfield = OUTFIELD;
			Animation(ifinfield, animsize);
			std::cout << "INPUT:: QUD:: OUT OF FIELD\n";
			return MOUSE_OUTOFFIELD;
		}

		///
		///ALREADY OUT OF FIELD
		///
		else if
			(!(GetPosition0().xy < ccresult &&
				GetPosition1() > ccresult) &&
				ifinfield == OUTFIELD) {

			ifinfield = ALREADY_OUTFIELD;
			std::cout << "INPUT:: QUD:: ALREADY OUT OF FIELD\n";
		}
	}

}

