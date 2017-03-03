#include "Polygon.h"

namespace FM3D {

	static bool IsPointInsideTriangle(const Vector2f& p0, Vector2f p1, Vector2f p2, Vector2f x) {
		p1 -= p0;
		p2 -= p0;
		x -= p0;

		float tmp = ((x.y * p2.x) - (x.x * p2.y)) / (p1.y * p2.y);
		float r = tmp / p1.x;
		float s = (x.y - tmp) / p2.y;

		return s <= 1 && r <= 1 && s >= 0 && r >= 0;
	}

	Polygon::Polygon(const Vector3f & position):
	m_position(position) {
	}

	Triangle::Triangle(const Vector3f & pos0, const Vector2f& pos1, const Vector2f& pos2):
	Polygon(pos0), m_pos1(pos1), m_pos2(pos2) {
	}

	std::vector<Vector2f> Triangle::GetVertices(const Matrix3f& matrix) const {
		return std::vector<Vector2f>({ m_position.xy, m_pos1, m_pos2 });
	}

	std::vector<uint> Triangle::GetIndices() const {
		return std::vector<uint>({ 0, 1, 2 });
	}

	bool Triangle::IsPointInside(const Vector2f& point) const {
		return IsPointInsideTriangle(m_position.xy, m_pos1, m_pos2, point);
	}

	void Triangle::Translate(const Vector2f& trans) {
		m_position.xy += trans;
		m_pos1 += trans;
		m_pos2 += trans;
	}

	void Triangle::Rotate(float angle) {
		auto m = Matrix2f::Rotation(angle);
		m_position.xy = m * m_position.xy;
		m_pos1 = m * m_pos1;
		m_pos2 = m * m_pos2;
	}

	void Triangle::Scale(float factor) {
		m_pos1 = (m_pos1 - m_position.xy) * factor;
		m_pos2 = (m_pos2 - m_position.xy) * factor;
	}

	Rectangle::Rectangle(const Vector3f & pos, float width, float height, float rotation):
	Polygon(pos), m_width(width), m_height(height), m_rotation(rotation) {
	}

	std::vector<Vector2f> Rectangle::GetVertices(const Matrix3f& matrix) const {
		return std::vector<Vector2f>();
	}

	std::vector<uint> Rectangle::GetIndices() const {
		return std::vector<uint>();
	}

	bool Rectangle::IsPointInside(const Vector2f& point) const {
		return false;
	}

	void Rectangle::Translate(const Vector2f& trans) {
	}

	void Rectangle::Rotate(float angle) {
	}

	void Rectangle::Scale(float factor) {
	}

	QQuad::QQuad(const Vector3f & pos0, const Vector2f& pos1, const Vector2f& pos2, const Vector2f& pos3):
	Polygon(pos0), m_pos1(pos1), m_pos2(pos2), m_pos3(pos3) {
	}

	std::vector<Vector2f> QQuad::GetVertices(const Matrix3f & matrix) const {
		return std::vector<Vector2f>();
	}

	std::vector<uint> QQuad::GetIndices() const {
		return std::vector<uint>();
	}

	bool QQuad::IsPointInside(const Vector2f& point) const {
		return false;
	}

	void QQuad::Translate(const Vector2f& trans) {
	}

	void QQuad::Rotate(float angle) {
	}

	void QQuad::Scale(float factor) {
	}

	Isogon::Isogon(const Vector3f& pos, float length, uint vertCount, float rotation):
	Polygon(pos), m_length(length), m_verticesCount(vertCount), m_rotation(rotation) {
	}

	std::vector<Vector2f> Isogon::GetVertices(const Matrix3f & matrix) const {
		return std::vector<Vector2f>();
	}

	std::vector<uint> Isogon::GetIndices() const {
		return std::vector<uint>();
	}

	bool Isogon::IsPointInside(const Vector2f& point) const {
		return false;
	}

	void Isogon::Translate(const Vector2f& trans) {
	}

	void Isogon::Rotate(float angle) {
	}

	void Isogon::Scale(float factor) {
	}

}