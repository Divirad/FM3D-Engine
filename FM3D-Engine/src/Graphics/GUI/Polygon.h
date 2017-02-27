#pragma once
#include <Engine.h>

namespace FM3D {

	class Polygon {
	protected:
		Vector3f m_position;
	
		Polygon(const Vector3f& position);
	public:
		virtual std::vector<Vector2f> GetVertices(const Matrix3f& matrix) const = 0;
		virtual std::vector<uint> GetIndices() const = 0;
		virtual bool IsPointInside(const Vector2f& point)const  = 0;

		virtual void Translate(const Vector2f& trans) = 0;
		virtual void Rotate(float angle) = 0;
		virtual void Scale(float factor) = 0;
	};

	class Triangle : public Polygon {
	protected:
		Vector2f m_pos1;
		Vector2f m_pos2;
	public:
		Triangle(const Vector3f& pos0, const Vector2f& pos1, const Vector2f& pos2);

		std::vector<Vector2f> GetVertices(const Matrix3f& matrix) const override;
		std::vector<uint> GetIndices() const override;
		bool IsPointInside(const Vector2f& point) const override;

		void Translate(const Vector2f& trans) override;
		void Rotate(float angle) override;
		void Scale(float factor) override;
	};

	class QQuad : public Polygon {
	protected:
		Vector2f m_pos1;
		Vector2f m_pos2;
		Vector2f m_pos3;
	public:
		QQuad(const Vector3f& pos0, const Vector2f& pos1, const Vector2f& pos2, const Vector2f& pos3);

		std::vector<Vector2f> GetVertices(const Matrix3f& matrix) const override;
		std::vector<uint> GetIndices() const override;
		bool IsPointInside(const Vector2f& point) const override;

		void Translate(const Vector2f& trans) override;
		void Rotate(float angle) override;
		void Scale(float factor) override;
	};

	class Rectangle : public Polygon {
	protected:
		float m_width;
		float m_height;
		float m_rotation;
	public:
		Rectangle(const Vector3f& pos, float width, float height, float rotation = 0.0f);

		std::vector<Vector2f> GetVertices(const Matrix3f& matrix) const override;
		std::vector<uint> GetIndices() const override;
		bool IsPointInside(const Vector2f& point) const override;

		void Translate(const Vector2f& trans) override;
		void Rotate(float angle) override;
		void Scale(float factor) override;
	};

	class Isogon : public Polygon {
	protected:
		float m_length;
		uint m_verticesCount;
		float m_rotation;
	public:
		Isogon(const Vector3f& pos, float length, uint vertCount, float rotation);

		std::vector<Vector2f> GetVertices(const Matrix3f& matrix) const override;
		std::vector<uint> GetIndices() const override;
		bool IsPointInside(const Vector2f& point) const override;

		void Translate(const Vector2f& trans) override;
		void Rotate(float angle) override;
		void Scale(float factor) override;
	};
}