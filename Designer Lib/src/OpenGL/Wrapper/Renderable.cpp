#include "Renderable.h"

namespace DesignerLib {

	FM3D::Model* Renderable::GetModel() {
		if (this->m_entity == nullptr)
			throw gcnew System::InvalidOperationException();
		return static_cast<FM3D::RenderableComponent*>(m_entity->GetComponent(RenderableComponentId))->GetModel();
	}

	Vec3^ Renderable::GetPosition() {
		if (this->m_entity == nullptr)
			throw gcnew System::InvalidOperationException();
		return gcnew Vec3(static_cast<FM3D::PositionComponent*>(m_entity->GetComponent(PositionComponentId))->GetPosition());
	}

	Vec3^ Renderable::GetRotation() {
		if (this->m_entity == nullptr)
			throw gcnew System::InvalidOperationException();
		return gcnew Vec3(static_cast<FM3D::RotationComponent*>(m_entity->GetComponent(RotationComponentId))->GetRotation());
	}

	Vec3^ Renderable::GetScale() {
		if (this->m_entity == nullptr)
			throw gcnew System::InvalidOperationException();
		return gcnew Vec3(static_cast<FM3D::ScaleComponent*>(m_entity->GetComponent(ScaleComponentId))->GetScale());
	}

	void Renderable::SetPosition(Vec3^ pos) {
		if (this->m_entity == nullptr)
			throw gcnew System::InvalidOperationException();
		static_cast<FM3D::PositionComponent*>(m_entity->GetComponent(PositionComponentId))->SetPosition(pos->Convert());
	}

	void Renderable::SetRotation(Vec3^ rot) {
		if (this->m_entity == nullptr)
			throw gcnew System::InvalidOperationException();
		static_cast<FM3D::RotationComponent*>(m_entity->GetComponent(RotationComponentId))->SetRotation(rot->Convert());
	}

	void Renderable::SetScale(Vec3^ scale) {
		if (this->m_entity == nullptr)
			throw gcnew System::InvalidOperationException();
		static_cast<FM3D::ScaleComponent*>(m_entity->GetComponent(ScaleComponentId))->SetScale(scale->Convert());
	}

	FM3D::Entity * Renderable::GetEntity() {
		return m_entity;
	}

	void Renderable::SetEntity(FM3D::Entity * e) {
		m_entity = e;
	}
}