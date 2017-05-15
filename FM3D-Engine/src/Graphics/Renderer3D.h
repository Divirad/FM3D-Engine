#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Renderer3D {
	protected:
		friend class RenderSystem;

		RenderTarget2D* m_target;
		bool m_forceWireFrame;

		Renderer3D(RenderTarget2D* target): m_target(target), m_forceWireFrame(false) {};
	public:
		virtual void Submit(const EntitySystem::Entity* e) = 0;
		virtual void Submit(const Terrain* t) = 0;
		virtual void Flush(const Matrix4f& viewMatrix, const Vector3f& cameraPos) = 0;
		virtual void SetProjectionMatrix(const Matrix4f& projectionMatrix) = 0;

		inline void SetForceWireFrame(bool useWireFrame) { m_forceWireFrame = useWireFrame; }
		inline bool IsForcingWireFrame() { return m_forceWireFrame; }
	};
}