#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	
	bool DragDropper::DragDrop(int keyID) {
		
		FollowMouse();

		return DROPPED;
	}

	bool DragDropper::FollowMouse() {
		

		std::cout << std::endl << "FUKKU";
		
		if (Click(MOUSE_LEFT)==true){
			if (clicked == false) {
				click = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastposClick());
				diff = click.Subtract(m_position0.xy);
				clicked = true;
			}
			else {
				clicked = false;
			}
		}
		else if (clicked==true) {
					
			size = m_position1.Subtract(m_position0.xy);
			mousepos = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastposInst());
			m_position0 = Vector3f(mousepos.Subtract(diff), m_position0.z);
			m_position1 = m_position0.xy + size;
		}
		return true;
	}

	//Maus+(Mauspos beim click-pos0)

};