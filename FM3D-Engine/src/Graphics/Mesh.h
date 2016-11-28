#pragma once
#include <Engine.h>

namespace FM3D {

	///<summary>
	///Collection of polygons for presenting a game object on the screen
	///</summary>
	class ENGINE_DLL Mesh {
	public:

		///<summary>
		///Data for each instance
		///</summary>
		struct InstanceData {
			Matrix4f modelMatrix;
			uint color;
		};
		
		struct ENGINE_DLL Part {
			uint indicesCount;
			void* indices;
			Vertices vertices;
			uint indexSize;
			bool supportsInstancing;

			Part(uint indicesCount, void* indices, Vertices vertices, uint indexSize, bool supportsInstancing);
		};

	private:
		///<summary>
		///Pointer to the skeleton, null if it has none
		///</summary>
		const Skeleton* m_skeleton;

		///<summary>
		///True if the mesh supports instancing and contains an instancing buffer
		///</summary>
		bool m_supportsInstancing;

		///<summary>
		///Number of supported materials
		///</summary>
		uint m_partsCount;
	protected:
		///<summary>
		///Basic constructor with a parameter for each member variable
		///</summary>
		///<param name = 'skeleton'>Pointer to the skeleton, null if the mesh is not animated</param>
		///<param name = 'supportsInstancing'>Indicates if the mesh supports instancing</param>
		///<param name = 'partsCount'>Number of materials the mesh supports</param>
		Mesh(const Skeleton* skeleton, bool supportsInstancing, int partsCount);
	public:
		///<summary>
		///Tests if the mesh supports animations
		///</summary>
		///<returns>Returns true if the mesh is animated and contains bone data in the vertices.</returns>
		inline bool IsAnimated() const { return m_skeleton != nullptr; }

		///<summary>
		///Inline getting method for <paramref name="m_skeleton"/>
		///</summary>
		///<returns>Returns a pointer to the skeleton</returns>
		inline const Skeleton* GetSkeleton() const { return m_skeleton; }

		///<summary>
		///Inline getting method for <paramref name="m_supportsInstancing"/>
		///</summary>
		///<returns>Returns true if the mesh supports instancing and contains an instancing buffer.</returns>
		inline bool SupportInstancing() { return m_supportsInstancing; }

		inline uint GetCountOfParts() const { return m_partsCount; }
	};
}