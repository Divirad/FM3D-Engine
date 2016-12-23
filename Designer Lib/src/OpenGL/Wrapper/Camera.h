#pragma once
#include "../../pch.h"

namespace DesignerLib {

	public ref class Camera {
	private:
		FM3D::Camera* m_camera;
	public:
		Camera(float x, float y, float z, float rx, float ry, float rz, float zoom) {
			m_camera = new FM3D::Camera(FM3D::Vector3f(x, y, z), FM3D::Vector3f(rx, ry, rz), zoom);
		}
		Camera() {
			m_camera = new FM3D::Camera();
		}
		~Camera() {
			delete m_camera;
		}

		FM3D::Camera* GetCamera() {
			return m_camera;
		}

		property float X {
			float get() {
				return m_camera->GetPosition().x;
			}
			void set(float value) {
				m_camera->GetPosition().x = value;
			}
		}
		property float Y {
			float get() {
				return m_camera->GetPosition().y;
			}
			void set(float value) {
				m_camera->GetPosition().y = value;
			}
		}
		property float Z {
			float get() {
				return m_camera->GetPosition().z;
			}
			void set(float value) {
				m_camera->GetPosition().z = value;
			}
		}

		property float RotX {
			float get() {
				return m_camera->GetRotation().x;
			}
			void set(float value) {
				m_camera->GetRotation().x = value;
			}
		}
		property float RotY {
			float get() {
				return m_camera->GetRotation().y;
			}
			void set(float value) {
				m_camera->GetRotation().y = value;
			}
		}
		property float RotZ {
			float get() {
				return m_camera->GetRotation().z;
			}
			void set(float value) {
				m_camera->GetRotation().z = value;
			}
		}

		property float Zoom {
			float get() {
				return m_camera->GetZoom();
			}
			void set(float value) {
				m_camera->GetZoom() = value;
			}
		}
	};
}