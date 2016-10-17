#pragma once
#include <Engine.h>


namespace ENGINE_NAME {

	bool BasicItem2D::Click(int keyID) {

		//CompCoords::Initialize(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());

		ccresult = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastpos());

		if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(keyID) == true &&
			GetPos0().y <= ccresult.y &&
			GetPos0().x <= ccresult.x &&
			GetPos1().x >= ccresult.x &&
			GetPos1().y >= ccresult.y) {

			std::cout << "INPUT:: BUT:: /w ID >>" << GetPos0().z << "<< was pressed" << std::endl;
			Inputsystem::GetInstance()->setKey(keyID, false);
			return true;
		}

		return 0;
	}

	void BasicItem2D::AutoSize(){
		
		Vector2f pos0px = CompCoords::ScreenSpaceToPixel(GetPos0().xy);
		//SetSize(CompCoords::PixelToScreenSpace(Vector2f(GetTextureWidth()+ pos0px.x, GetTextureHeight() + pos0px.y).Subtract(GetPos0().xy)));

		SetSize(GetTextureWidth() + pos0px.x, GetTextureHeight() + pos0px.y);

		std::cout << "\nAUTOSIZE\nPos 0: " << GetPos0() << "\nPos1: " << GetPos1() << "\nUV0: " << GetUV0() << "\nUV1: " << GetUV1();
	}

	void BasicItem2D::AutoDock(AUTODOCK ad){
		switch (ad)
		{
		case Engine::BasicItem2D::VERTICAL_TOP:
			VTop();
			break;
		case Engine::BasicItem2D::VERTICAL_BOTTOM:
			VBottom();
			break;
		case Engine::BasicItem2D::VERTICAL_STRETCH:
			VStretch();
			break;
		case Engine::BasicItem2D::VERTICAL_CENTER:
			VCenter();
			break;
		case Engine::BasicItem2D::HORIZONTAL_TOP:
			HTop();
			break;
		case Engine::BasicItem2D::HORIZONTAL_BOTTOM:
			HBottom();
			break;
		case Engine::BasicItem2D::HORIZONTAL_STRETCH:
			HStretch();
			break;
		case Engine::BasicItem2D::HORIZONTAL_CENTER:
			HCenter();
			break;
		case Engine::BasicItem2D::STRETCH:
			Stretch();
			break;
		default:
			break;
		}

	}

	void BasicItem2D::VTop(){}
	void BasicItem2D::VBottom() {}
	void BasicItem2D::VStretch(){
		SetPosition0(GetPos0().x, -1.0f, GetPos0().z);
		SetPosition1(Vector2f(GetPos1().x, 1.0f));
	}
	void BasicItem2D::VCenter(){}

	void BasicItem2D::HTop(){}
	void BasicItem2D::HBottom(){}
	void BasicItem2D::HStretch(){
		SetPosition0(-1.0f, GetPos0().y, GetPos0().z);
		SetPosition1(1.0f, GetPos1().y);
	}
	void BasicItem2D::HCenter(){
		float texturecoord = CompCoords::PixelToScreenSpace(Vector2f(GetTextureWidth(), 0.0f)).x /2 ;
		//float texturecoord = CompCoords::PixelToScreenSpace(Vector2f(GetTextureWidth(), 0.0f)).x / 2;
		SetPosition1(-texturecoord, GetPosition1().y);
		SetPosition0(+texturecoord, GetPosition0().y,GetPosition0().z);

	}

	void BasicItem2D::Stretch() {
		SetPosition0(GetPos0().x, GetPos0().y, GetPos0().z);
		SetPosition1(Vector2f(GetPos1().x, GetPos1().y));
	}

	void BasicItem2D::PicVisibility(float pro){}
	void BasicItem2D::TextVisibility(float pro){}
	bool BasicItem2D::ccRectangle() { return 0; }
	bool BasicItem2D::ccEllipse(){ return 0; }
	bool BasicItem2D::Render(){ return 0; }
	bool BasicItem2D::Update(){ return 0; }


	
}