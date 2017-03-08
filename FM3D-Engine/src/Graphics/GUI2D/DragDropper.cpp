#pragma once
#include <Engine.h>

namespace FM3D {

	
	bool DragDropper::DragDrop(int keyID) {
		
		FollowMouse(keyID);

		return DROPPED;
	}

	bool DragDropper::FollowMouse(int keyID) {
				
		if (ccRectangle(keyID)==Inputsystem::ACTIVATED){
			if (clicked == Inputsystem::NOCLICK) {
				clicked = Inputsystem::ACTIVATED;
				click = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastposClick(keyID));
				diff = click.Subtract(m_position0.xy);
			}
			else {
				clicked = Inputsystem::NOCLICK;
			}
		}
		else if (Inputsystem::GetInstance()->CheckMouse(keyID) == Inputsystem::RELEASED) {
			
			Inputsystem::GetInstance()->setMKey(keyID, Inputsystem::NOCLICK);
			clicked = Inputsystem::NOCLICK;
		}

		else if (clicked== Inputsystem::ACTIVATED) {
					
			size = m_position1.Subtract(m_position0.xy);
			mousepos = CompCoords::PixelToScreenSpace(Inputsystem::GetInstance()->GetLastposInst());
			m_position0 = Vector3f(mousepos.Subtract(diff), m_position0.z);
			m_position1 = m_position0.xy + size;
		}
		
	
	return true;
	}

	//Maus+(Mauspos beim click-pos0)

};