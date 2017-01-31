#include "Renderable.h"

using namespace System::Threading;

namespace DesignerLib {

	Renderable::Renderable(const FM3D::Model* model) {
		m_position = gcnew Vec3(0.0f, 0.0f, 0.0f);
		m_rotation = gcnew Vec3(0.0f, 0.0f, 0.0f);
		m_scale = gcnew Vec3(1.0f, 1.0f, 1.0f);
		m_model = model;
	}

}