#pragma once
#include <Engine.h>

namespace ENGINE_NAME {
	class ENGINE_DLL BasicItem2D : public Quad {

	public:

		enum AUTODOCK
		{
			VERTICAL_TOP,
			VERTICAL_BOTTOM,
			VERTICAL_STRETCH,
			VERTICAL_CENTER,

			HORIZONTAL_TOP,
			HORIZONTAL_BOTTOM,
			HORIZONTAL_STRETCH,
			HORIZONTAL_CENTER,
			STRETCH
		};
		
	protected:
		//Quad m_box;		
						//4 Clickcheck
		Vector2f ccresult;
						//visibility 
		float visquad;
		float visfloat;

	public:

		bool Click(int keyID);	//done
		void AutoSize();		//done
		void AutoDock(AUTODOCK ad);//d
		void VTop();
		void VBottom();
		void VStretch();
		void VCenter();

		void HTop();
		void HBottom();
		void HStretch();		//d
		void HCenter();

		void Stretch();			//done

		void PicVisibility(float);
		void TextVisibility(float);
		bool ccRectangle();
		bool ccEllipse();
		bool Render();
		bool Update();


	};
}