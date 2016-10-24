#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	
	bool DragDropper::DragDrop(int keyID) {
		
		FollowMouse();

		return DROPPED;
	}

	/*bool DragDropper::FollowMouse() {
		if (boolswitch == false) {
			mousebefore = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastposInst());
			std::cout << "Before" << mousebefore << std::endl;
			boolswitch = true;
			return DRAGGING;
		}
		else {
			mouseafter = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastposInst());
			boolswitch = false;
			mouseresult = mouseafter.Subtract(mousebefore);
			std::cout << "After" << mouseafter << std::endl;
			m_position0 = Vector3f(m_position0.xy + mouseresult, GetPosition0().z);
			std::cout << "pos0" << m_position0 << std::endl;
			m_position1 = Vector2f(m_position1 + mouseresult);
			std::cout << m_position0 << std::endl;
			mouseresult = Vector2f(NULL,NULL);
			mouseafter = Vector2f(NULL, NULL);
			mousebefore = Vector2f(NULL, NULL);
			return DRAGGING;
		}
		return DROPPED;
	}*/
	

	bool DragDropper::FollowMouse() {
		

		std::cout << std::endl << "FUKKU";
		
		

		if (Click(MOUSE_LEFT)==true){
			if (dragging == false) {
				click = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastposClick());
				diff = click.Subtract(m_position0.xy);
				dragging = true;
			}
			else {
				dragging = false;
			}
		}
		else if (dragging==true) {
					
			size = m_position1.Subtract(m_position0.xy);
			mousepos = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastposInst());
			m_position0 = Vector3f(mousepos.Subtract(diff), m_position0.z);
			m_position1 = m_position0.xy + size;
		}
		return true;
	}

	//Maus+(Mauspos beim click-pos0)

};