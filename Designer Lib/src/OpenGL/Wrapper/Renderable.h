#pragma once
#include "../../pch.h"
#include "../../Vec3.h"

namespace FM3D {
	class Model;
}

namespace DesignerLib {

	public ref class Renderable {
	protected:
		Vec3^ m_position;
		Vec3^ m_rotation;
		Vec3^ m_scale;
		const FM3D::Model* m_model = nullptr;
	public:
		Renderable();
		Renderable(Vec3^ pos, Vec3^ rot, Vec3^ scale);

		Vec3^ GetPosition() { return m_position; }
		Vec3^ GetRotation() { return m_rotation; }
		Vec3^ GetScale() { return m_scale; }

		void SetPosition(Vec3^ pos) { m_position = pos; }
		void SetRotation(Vec3^ rot) { m_rotation = rot; }
		void SetScale(Vec3^ scale) { m_scale = scale; }

		const FM3D::Model* GetModel() { return m_model; }
	};
}