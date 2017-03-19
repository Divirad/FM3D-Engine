#pragma once
#include <Engine.h>

namespace FM3D {

	
	bool DragDropper::DragDrop(int keyID) {
		
		FollowMouse(keyID);

		return DROPPED;
	}

	bool DragDropper::FollowMouse(int keyID) {
				
		if (ccRectangle(keyID)== Input::ACTIVATED){
			if (clicked == Input::NOCLICK) {
				clicked = Input::ACTIVATED;
				click = CompCoords::PixelToScreenSpace(Window::GetInstance()->GetInput().GetLastposClick(keyID));
				diff = click.Subtract(m_position0.xy);
			}
			else {
				clicked = Input::NOCLICK;
			}
		}
		else if (Window::GetInstance()->GetInput().CheckMouse(keyID) == Input::RELEASED) {
			
			//Window::GetInstance()->GetInput().SetMKey(keyID, Input::NOCLICK);
			clicked = Input::NOCLICK;
		}

		else if (clicked== Input::ACTIVATED) {
					
			size = m_position1.Subtract(m_position0.xy);
			mousepos = CompCoords::PixelToScreenSpace(Window::GetInstance()->GetInput().GetLastposInst());
			m_position0 = Vector3f(mousepos.Subtract(diff), m_position0.z);
			m_position1 = m_position0.xy + size;
		}
		
	
	return true;
	}

	//Maus+(Mauspos beim click-pos0)

};