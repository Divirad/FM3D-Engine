#pragma once
#include <Engine.h>

namespace ENGINE_NAME {
	class ENGINE_DLL BasicItem2D : public Quad {

	public:

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

		void Stretch();		
		void Center();
		void Left();
		void Right();
		void Top();
		void Bottom();

		void PicVisibility(float);
		void TextVisibility(float);
		bool ccRectangle();
		bool ccEllipse();
		bool Render();
		bool Update();


	};
}