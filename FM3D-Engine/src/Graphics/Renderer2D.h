#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL Renderer2D {
	protected:
		Matrix4f m_transformationMatrix = Matrix4f::Identity();
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

		virtual void Initialize(Matrix4f projectionMatrix) = 0;
		virtual void SetProjectionMatrix(const Matrix4f& projectionMatrix) = 0;
		virtual void Shutdown() = 0;
	};
}