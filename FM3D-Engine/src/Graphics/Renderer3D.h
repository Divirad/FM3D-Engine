#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Renderer3D {
	protected:
		friend class RenderSystem;

		RenderTarget2D* m_target;

		Renderer3D(RenderTarget2D* target): m_target(target) {};
	public:
		virtual void Submit(const EntitySystem::Entity* e) = 0;
		virtual void Flush(const Matrix4f& viewMatrix, const Vector3f& cameraPos) = 0;
		virtual void SetProjectionMatrix(const Matrix4f& projectionMatrix) = 0;
	};
}