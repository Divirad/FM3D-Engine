#include "Polygon.h"

namespace FM3D {

	Polygon::Polygon(const Vector3f & position):
	m_position(position) {
	}

	Triangle::Triangle(const Vector3f & pos0, const Vector2f & pos1, const Vector2f & pos2):
	Polygon(pos0), m_pos1(pos1), m_pos2(pos2) {
	}

	std::vector<Vector2f> Triangle::GetVertices(const Matrix3f & matrix) const {
		return std::vector<Vector2f>({ m_position.xy, m_pos1, m_pos2 });
	}

	std::vector<uint> Triangle::GetIndices() const {
		return std::vector<uint>();
	}

	bool Triangle::IsPointInside(const Vector2f & point) const {
		return false;
	}

	void Triangle::Translate(const Vector2f & trans) {
	}

	void Triangle::Rotate(float angle) {
	}

	void Triangle::Scale(float factor) {
	}

	Rectangle::Rectangle(const Vector3f & pos, float width, float height, float rotation):
	Polygon(pos), m_width(width), m_height(height), m_rotation(rotation) {
	}

	std::vector<Vector2f> Rectangle::GetVertices(const Matrix3f & matrix) const {
		return std::vector<Vector2f>();
	}

	std::vector<uint> Rectangle::GetIndices() const {
		return std::vector<uint>();
	}

	bool Rectangle::IsPointInside(const Vector2f & point) const {
		return false;
	}

	void Rectangle::Translate(const Vector2f & trans) {
	}

	void Rectangle::Rotate(float angle) {
	}

	void Rectangle::Scale(float factor) {
	}

	QQuad::QQuad(const Vector3f & pos0, const Vector2f & pos1, const Vector2f & pos2, const Vector2f & pos3):
	Polygon(pos0), m_pos1(pos1), m_pos2(pos2), m_pos3(pos3) {
	}

	std::vector<Vector2f> QQuad::GetVertices(const Matrix3f & matrix) const {
		return std::vector<Vector2f>();
	}

	std::vector<uint> QQuad::GetIndices() const {
		return std::vector<uint>();
	}

	bool QQuad::IsPointInside(const Vector2f & point) const {
		return false;
	}

	void QQuad::Translate(const Vector2f & trans) {
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

	bool Isogon::IsPointInside(const Vector2f & point) const {
		return false;
	}

	void Isogon::Translate(const Vector2f & trans) {
	}

	void Isogon::Rotate(float angle) {
	}

	void Isogon::Scale(float factor) {
	}

}