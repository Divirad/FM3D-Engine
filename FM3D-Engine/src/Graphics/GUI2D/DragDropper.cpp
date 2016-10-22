#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	
	bool DragDropper::DragDrop(int keyID) {
		

		InFieldAnimation();
		if (Click(keyID)) {
			return FollowMouse();
		}
		return DROPPED;
	}

	bool DragDropper::FollowMouse() {
		if (boolswitch == false) {

			mousebefore = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastpos());
			std::cout << "Before" << mousebefore << std::endl;
			boolswitch = true;
			return DRAGGING;
		}

		else {
			mouseafter = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastpos());

			boolswitch = false;

			mouseresult = mouseafter.Subtract(mousebefore);

			std::cout << "After" << mouseafter << std::endl;
			m_position0 = Vector3f(m_position0.xy + mouseresult, GetPosition0().z);
			std::cout << "pos0" << m_position0 << std::endl;
			m_position1 = Vector2f(m_position1 + mouseresult);
			std::cout << m_position0 << std::endl;
			return DRAGGING;
		}

		return DROPPED;
	}
	

}