#pragma once
#include <Engine.h>

namespace ENGINE_NAME {
	class ENGINE_DLL BasicItem2D : public Quad {

	public:
		BasicItem2D(Texture *txt, int i) {
			
			//SetPosition0(Vector3f(0.0f, 0.0f),0);
			m_position0 = { -0.3f,-0.5f };
			m_position1 = { 0.5f,0.0f };

			/*m_position0 = { 0.0f,0.5f };
			m_position1 = { 0.5f,1.0f };*/

			SetTexture(txt);
			m_uv0 = { 0.0f, 0.0f };
			m_uv1 = { 1.0f,1.0f };
			SetColor(0xffffffff);
		}

		BasicItem2D(Texture *txt) {

			//SetPosition0(Vector3f(0.0f, 0.0f),0);
			m_position0 = { 0.0f,0.0f };
			m_position1 = { 0.5f,0.5f };
			SetTexture(txt);
			m_uv0 = { 0.0f, 0.0f };
			m_uv1 = { 1.0f,1.0f };
			SetColor(0xffffffff);
		}

		enum ANCHOR
		{
			VERTICAL_LEFT,
			VERTICAL_RIGHT,
			VERTICAL_STRETCH,
			VERTICAL_CENTER,

			HORIZONTAL_TOP,
			HORIZONTAL_BOTTOM,
			HORIZONTAL_STRETCH,
			HORIZONTAL_CENTER,

			STRETCH,
			CENTER,
			LEFT,
			RIGHT,
			BOTTOM,
			TOP
		};

	protected:
		//Quad m_box;		
		//4 Clickcheck
		Vector2f ccresult;
		//visibility 
		float visquad;
		float visfloat;

	public:
		
		bool Click(int keyID);	//DONE
		void AutoSize();
		void Anchor(ANCHOR ad);	//DONE

		void VLeft();
		void VRight();			//DONE
		void VStretch();		//DONE
		void VCenter();			//DONE

		void HTop();			//DONE
		void HBottom();			//DONE
		void HStretch();		//DONE
		void HCenter();			//DONE

		void Stretch();			//DONE
		void Center();			//DONE
		void Left();			//DONE
		void Right();			//DONE
		void Top();				//DONE
		void Bottom();			//DONE

		void PicVisibility(float pro);
		bool ccRectangle(int keyID);	//DONE
		bool ccEllipse();


	};
}