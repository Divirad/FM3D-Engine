#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Renderer2D {
	protected:
		Matrix4f m_transformationMatrix = Matrix4f::Identity();
		const RenderTarget2D* m_renderTarget;

		Renderer2D(const RenderTarget2D* renderTarget);
	public:
		virtual void Begin() = 0;
		virtual void Submit(Quad* quad) = 0;
		virtual void End() = 0;
		virtual void Flush() = 0;

		virtual void DrawString(const Text& text, const Vector3f& position) = 0;

		void SetTransformationMatrix(const Matrix4f& mat, bool override = false) {
			if (override) {
				m_transformationMatrix = mat;
			} else {
				m_transformationMatrix *= mat;
			}
		}
	};
}