#include <Engine.h>

namespace FM3D {

	Terrain::Square::Square(const Corner * corner) {
	}

	void Terrain::Square::InitChild(Corner* child, const Corner& corner, int childIndex) {
		int	half = 1 << corner.m_level;

		child->m_parent = &corner;
		child->m_square = m_childs[childIndex];
		child->m_level = corner.m_level - 1;
		child->m_childIndex = childIndex;

		switch (childIndex) {
		default:
		case 0:
			child->m_xorg = corner.m_xorg + half;
			child->m_zorg = corner.m_zorg;
			child->m_edgeHeights[0] = corner.m_edgeHeights[0];
			child->m_edgeHeights[1] = m_heights[2];
			child->m_edgeHeights[2] = m_heights[0];
			child->m_edgeHeights[3] = m_heights[1];
			break;

		case 1:
			child->m_xorg = corner.m_xorg;
			child->m_zorg = corner.m_zorg;
			child->m_edgeHeights[0] = m_heights[2];
			child->m_edgeHeights[1] = corner.m_edgeHeights[1];
			child->m_edgeHeights[2] = m_heights[3];
			child->m_edgeHeights[3] = m_heights[0];
			break;

		case 2:
			child->m_xorg = corner.m_xorg;
			child->m_zorg = corner.m_zorg + half;
			child->m_edgeHeights[0] = m_heights[0];
			child->m_edgeHeights[1] = m_heights[3];
			child->m_edgeHeights[2] = corner.m_edgeHeights[2];
			child->m_edgeHeights[3] = m_heights[4];
			break;

		case 3:
			child->m_xorg = corner.m_xorg + half;
			child->m_zorg = corner.m_zorg + half;
			child->m_edgeHeights[0] = m_heights[1];
			child->m_edgeHeights[1] = m_heights[0];
			child->m_edgeHeights[2] = m_heights[4];
			child->m_edgeHeights[3] = corner.m_edgeHeights[3];
			break;
		}
	}
	
	void Terrain::Square::CreateChild(int childIndex, const Corner& corner) {
		if (m_childs[childIndex] == nullptr) {
			Corner c;
			InitChild(&c, corner, childIndex);

			m_childs[childIndex] = new Square(&c);
		}
	}

	Terrain::Square* Terrain::Square::GetNeighbor(int direction, const Corner& corner) {
		if (corner.m_parent == nullptr) return nullptr;

		Square*	p = nullptr;

		int	index = corner.m_childIndex ^ 1 ^ ((direction & 1) << 1);
		bool sameParent = ((direction - corner.m_childIndex) & 2) ? true : false;

		if (sameParent) {
			p = corner.m_parent->m_square;
		}
		else {
			p = corner.m_parent->m_square->GetNeighbor(direction, *corner.m_parent);

			if (p == 0) return 0;
		}

		Square*	n = p->m_childs[index];

		return n;
	}
}