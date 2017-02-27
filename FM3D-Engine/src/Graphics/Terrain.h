#pragma once
#include <Engine.h>

namespace FM3D {

	class Terrain {
	public:
		struct HeightMapInfo {
			int16*	data;
			int	xOrigin, zOrigin;
			int	xSize, zSize;
			int	rowWidth;
			int	scale;

		};

		class Square;

		///Ecken eines Vierecks des Terrains
		struct Corner {
			const Corner* m_parent;
			int m_childIndex;
			int m_level;
			int m_xorg, m_zorg;
			uint16 m_edgeHeights[4]; // ne, nw, sw, se
			Square* m_square;
		};

		///Viereck des Terrains
		class Square {
		private:
			Square* m_childs[4];
			uint16 m_heights[5]; // center, e, n, w, s

			byte m_enabledFlags;	// bits 0-7: e, n, w, s, ne, nw, sw, se
			byte m_subEnabledCount[2];	// e, s enabled reference counts.

		public:
			Square(const Corner* corner);
		private:
			///Initialisiert ein Child-Corner
			/**
			* Initialisiert die Eckpunkte des gegebenen Child-corners in Abhängigkeit
			* der Eckpunkte dieses Squares, sowie Level, Childindex und die Beziehung
			* zu diesem Square.
			*
			* @param child Das Child-Corner, welches initialisiertw erden soll
			* @param corner Das Corner-Objekt, welches zu diesem Square-Objekt gehört
			* @param childIndex Gibt an in welcher Ecke sich das Child-Corner befindet
			*/
			void InitChild(Corner* child, const Corner& corner, int childIndex);

			///Erstellt ein neues Child-Corner
			/**
			* Erstellt für dieses Square-Objekt ein neues Child-Square-Objekt
			*
			* @param childIndex Gibt an in welcher Ecke sich das Child-Corner befindet
			* @param corner Das Corner-Objekt, welches zu diesem Square-Objekt gehört
			*/
			void CreateChild(int childIndex, const Corner& corner);

			///Gibt ein Nachbar-Square zurück
			/**
			* Sucht rekursiv nach dem Nachbar-Square, welches direkt an diesem anliegt und
			* sich in einer bestimmten Richtung befindet.
			*
			* @param direction Gibt die Richtung an, in der sich das Nachbar-Objekt befindet.
			* Die Werte 0 - 3 Stehen für die Himmelksrichtungen: { O, N, W, S }
			* @param corner Das Corner-Objekt, welches zu diesem Square-Objekt gehört
			* @returns Das gesuchte Nachbar-Square. NULL wenn es keinen Nachbar gibt.
			*/
			Square* GetNeighbor(int direction, const Corner& corner);
		};


	};

}