#include "InternCamera.h"

using namespace FM3D;

namespace DesignerLib {

	InternCamera::InternCamera(float x, float y, float z, float rx, float ry, float rz, float zoom) :
		m_camera(new Camera(Vector3f(x, y, z), Vector3f(rx, ry, rz), zoom)) {

	}

	FM3D::Camera * InternCamera::GetCamera() const { return m_camera; }

	float InternCamera::GetX() { return m_camera->GetPosition().x; }
	float InternCamera::GetY() { return m_camera->GetPosition().y; }
	float InternCamera::GetZ() { return m_camera->GetPosition().z; }

	float InternCamera::GetRotX() { return m_camera->GetRotation().x; }
	float InternCamera::GetRotY() { return m_camera->GetRotation().y; }
	float InternCamera::GetRotZ() { return m_camera->GetRotation().z; }

	float InternCamera::GetZoom() { return m_camera->GetZoom(); }

	void InternCamera::SetX(float value) { m_camera->GetPosition().x = value; }
	void InternCamera::SetY(float value) { m_camera->GetPosition().y = value; }
	void InternCamera::SetZ(float value) { m_camera->GetPosition().z = value; }

	void InternCamera::SetRotX(float value) { m_camera->GetRotation().x = value; }
	void InternCamera::SetRotY(float value) { m_camera->GetRotation().y = value; }
	void InternCamera::SetRotZ(float value) { m_camera->GetRotation().z = value; }

	void InternCamera::SetZoom(float value) { m_camera->GetZoom() = value; }

}