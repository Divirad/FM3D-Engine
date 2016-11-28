#pragma once
#include <Engine.h>

namespace FM3D {
	class ENGINE_DLL BasicItem2D : public Quad {

	public:

		enum ANCHOR
		{
			LEFT_CENTER,
			RIGHT_CENTER,
			STRETCH_VERTICAL,
			CENTER_VERTICAL,

			TOP_CENTER,
			BOTTOM_CENTER,
			STRETCH_HORIZONTAL,
			CENTER_HORIZONTAL,

			STRETCH,
			CENTER,
			LEFT,
			RIGHT,
			BOTTOM,
			TOP
		};
		enum FIELDCHECK {
			INFIELD,
			ALREADY_INFIELD,
			OUTFIELD,
			ALREADY_OUTFIELD
		};


	protected:
		//4 Clickcheck
		Vector2f ccresult;
		//float visquad;
		//float visfloat;

		void VLeft();			//DONE
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

	public:
		
		bool Click(int keyID);
		void AutoSize();		//DONE
		void Anchor(ANCHOR ad);	//DONE

		void PicVisibility(float pro);
		Inputsystem::KEYCLICK ccRectangle(int keyID);	//DONE

		FIELDCHECK FieldCecker();
		bool Collision(Quad &quad);

	};
}