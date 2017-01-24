#include "Renderable.h"

using namespace System::Threading;

namespace DesignerLib {

	Renderable::Renderable() {
		m_position = gcnew Vec3(0.0f, 0.0f, 0.0f);
		m_rotation = gcnew Vec3(0.0f, 0.0f, 0.0f);
		m_scale = gcnew Vec3(1.0f, 1.0f, 1.0f);

	}

	Renderable::Renderable(Vec3 ^ pos, Vec3 ^ rot, Vec3 ^ scale) {
		m_position = pos;
		m_rotation = rot;
		m_scale = scale;
	}

}