#pragma once
#include "../../pch.h"
#include "../../Vec3.h"

namespace DesignerLib {

	public ref class Renderable {
	protected:
		FM3D::Entity* m_entity;
	public:
		FM3D::Model* GetModel();

		Vec3^ GetPosition();
		Vec3^ GetRotation();
		Vec3^ GetScale();

		void SetPosition(Vec3^ pos);
		void SetRotation(Vec3^ rot);
		void SetScale(Vec3^ scale);

		FM3D::Entity* GetEntity();
		void SetEntity(FM3D::Entity* e);
	};
}