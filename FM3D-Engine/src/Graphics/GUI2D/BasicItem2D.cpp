#pragma once
#include <Engine.h>


namespace ENGINE_NAME {

	bool BasicItem2D::Click(int keyID) {

		//CompCoords::Initialize(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());

		ccresult = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastpos());

		if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(keyID) == true &&
			m_box.GetPos0().y <= ccresult.y &&
			m_box.GetPos0().x <= ccresult.x &&
			m_box.GetPos1().x >= ccresult.x &&
			m_box.GetPos1().y >= ccresult.y) {

			std::cout << "INPUT:: BUT:: /w ID >>" << m_box.GetPos0().z << "<< was pressed" << std::endl;
			Inputsystem::GetInstance()->setKey(keyID, false);
			return true;
		}

		return 0;
	}

	void BasicItem2D::AutoSize(){
		Vector2f pos0px = CompCoords::ScreenSpaceToPixel(m_box.GetPos0().xy);
		m_box.SetSize(CompCoords::PixelToScreenSpace(Vector2f(m_box.GetTextureWidth() + pos0px.x, m_box.GetTextureHeight() + pos0px.y).Subtract(m_box.GetPos0().xy)));
		//std::cout << "\n\nAUTOSIZE\nPos 0: " << m_box.GetPos0() << "\nPos1: " << m_box.GetPos1() << "\nUV0: " << m_box.GetUV0() << "\nUV1: " << m_box.GetUV1();
	}

	void BasicItem2D::AutoDock(){
		Vector2f pos0center;
	}

	void BasicItem2D::VTop(){}
	void BasicItem2D::VBottom() {}
	void BasicItem2D::VStretch(){
		m_box.SetPosition0(m_box.GetPos0().x, -1.0f,m_box.GetPos0().z);
		m_box.SetPosition1(Vector2f(m_box.GetPos1().x, 1.0f));
	}
	void BasicItem2D::VCenter(){}

	void BasicItem2D::HTop(){}
	void BasicItem2D::HBottom(){}
	void BasicItem2D::HStretch(){
		m_box.SetPosition0(-1.0f, m_box.GetPos0().y, m_box.GetPos0().z);
		m_box.SetPosition1(1.0f, m_box.GetPos1().y);
	}
	void BasicItem2D::HCenter(){}



	void BasicItem2D::PicVisibility(float pro){}
	void BasicItem2D::TextVisibility(float pro){}
	bool BasicItem2D::ccRectangle() { return 0; }
	bool BasicItem2D::ccEllipse(){ return 0; }
	bool BasicItem2D::Render(){ return 0; }
	bool BasicItem2D::Update(){ return 0; }


	
}