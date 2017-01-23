#pragma once
#include "../../pch.h"
#define NO_FM3D
#include "../InternCamera.h"

namespace DesignerLib {

	public ref class Camera {
	private:
		InternCamera* m_camera;
	public:
		Camera(float x, float y, float z, float rx, float ry, float rz, float zoom) {
			m_camera = new InternCamera(x, y, z, rx, ry, rz, zoom);
		}

		~Camera() {
			delete m_camera;
		}

		FM3D::Camera* GetCamera() {
			return m_camera->GetCamera();
		}

		property float X {
			float get() {
				return m_camera->GetX();
			}
			void set(float value) {
				m_camera->SetX(value);
			}
		}
		property float Y {
			float get() {
				return m_camera->GetY();
			}
			void set(float value) {
				m_camera->SetY(value);
			}
		}
		property float Z {
			float get() {
				return m_camera->GetZ();
			}
			void set(float value) {
				m_camera->SetZ(value);
			}
		}

		property float RotX {
			float get() {
				return m_camera->GetRotX();
			}
			void set(float value) {
				m_camera->SetRotX(value);
			}
		}
		property float RotY {
			float get() {
				return m_camera->GetRotY();
			}
			void set(float value) {
				m_camera->SetRotY(value);
			}
		}
		property float RotZ {
			float get() {
				return m_camera->GetZ();
			}
			void set(float value) {
				m_camera->SetRotZ(value);
			}
		}

		property float Zoom {
			float get() {
				return m_camera->GetZoom();
			}
			void set(float value) {
				m_camera->SetZoom(value);
			}
		}
	};
}