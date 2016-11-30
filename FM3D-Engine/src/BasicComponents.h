#pragma once
#include <Engine.h>

namespace FM3D {

	class PositionComponent : public Component {
		Vector3f m_position;
	public:
		void Construct(const Vector3f position) {
			m_position = position;
		}
		void Destruct() {}

		inline const Vector3f& GetPosition() const { return m_position; }
		inline void SetPosition(const Vector3f& position) { m_position = position; }
	};
#define PositionComponentId ComponentIds::Get<PositionComponent>()

	class RotationComponent : public Component {
		Vector3f m_rotation;
	public:
		void Construct(const Vector3f rotation) {
			m_rotation = rotation;
		}
		void Destruct() {}

		inline const Vector3f& GetRotation() const { return m_rotation; }
		inline void SetRotation(const Vector3f& rotation) { m_rotation = rotation; }

		inline float GetPitch() const { return m_rotation.x; }
		inline float GetYaw() const { return m_rotation.y; }
		inline float GetRoll() const { return m_rotation.z; }

		inline void SetPitch(float pitch) { m_rotation.x = pitch; }
		inline void SetYaw(float yaw) { m_rotation.y = yaw; }
		inline void SetRoll(float roll) { m_rotation.z = roll; }
	};
#define RotationComponentId ComponentIds::Get<RotationComponent>()

	class ScaleComponent : public Component {
		Vector3f m_scale;
	public:
		void Construct(const Vector3f scale) {
			m_scale = scale;
		}
		void Destruct() {}

		inline const Vector3f& GetScale() const { return m_scale; }
		inline void SetScale(const Vector3f& scale) { m_scale = scale; }
	};
#define ScaleComponentId ComponentIds::Get<ScaleComponent>()
}