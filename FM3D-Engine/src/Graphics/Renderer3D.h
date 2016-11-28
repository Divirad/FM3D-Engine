#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Renderer3D {
	protected:
		friend class RenderSystem;
		Renderer3D() {};
	public:
		virtual void Submit(const Entity* e) = 0;
		virtual void Flush(const Matrix4f& viewMatrix, const Vector3f& cameraPos) = 0;
		virtual void SetProjectionMatrix(const Matrix4f& projectionMatrix) = 0;
	};
}