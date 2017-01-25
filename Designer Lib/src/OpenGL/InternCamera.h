#pragma once
#ifdef NO_FM3D
namespace FM3D {
		class Camera;
}
#else
#include <Engine.h>
#endif


namespace DesignerLib {

	class InternCamera {
		FM3D::Camera* m_camera;
	public:
		InternCamera(float x, float y, float z, float rx, float ry, float rz, float zoom);

		FM3D::Camera* GetCamera() const;

		float GetX();
		float GetY();
		float GetZ();

		float GetRotX();
		float GetRotY();
		float GetRotZ();

		float GetZoom();

		void SetX(float value);
		void SetY(float value);
		void SetZ(float value);

		void SetRotX(float value);
		void SetRotY(float value);
		void SetRotZ(float value);

		void SetZoom(float value);
	};

}