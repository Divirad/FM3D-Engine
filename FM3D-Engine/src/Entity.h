//#pragma once
//#include <Engine.h>
//
//#pragma warning(push)
//#pragma warning(disable:4005)
//
//namespace FM3D {
//
//	class Model;
//
//	struct ActiveAnimation {
//		uint animationIndex;
//		double time;
//	};
//
//	class ENGINE_DLL Entity {
//	protected:
//		Vector3f m_position;
//		Vector3f m_rotation;
//		Vector3f m_scale;
//		const Model* m_model;
//		uint m_animation;
//		double m_animationTime;
//		std::vector<ActiveAnimation> m_animations;
//	public:
//		Entity(Vector3f position, Vector3f rotation, Vector3f scale, const Model* model);
//
//		inline const Vector3f& GetPosition() const { return m_position; }
//		inline const Vector3f& GetRotation() const { return m_rotation; }
//		inline const Vector3f& GetScale() const { return m_scale; }
//
//		inline Vector3f& GetPosition() { return m_position; }
//		inline Vector3f& GetRotation() { return m_rotation; }
//		inline Vector3f& GetScale() { return m_scale; }
//
//		inline const Model* GetModel() const { return m_model; }
//		inline Matrix4f GetModelMatrix() const { return Matrix4f::Transformation(m_position, m_scale, m_rotation); }
//		inline const std::vector<ActiveAnimation>& GetAnimations() const { return m_animations; }
//		inline std::vector<ActiveAnimation>& GetAnimations() { return m_animations; }
//	};
//
//}