#pragma once
#define NO_FM3D
#include "Mesh.h"
#include "Skeleton.h"

using namespace System::Collections::Generic;

namespace DesignerLib {

	public ref class ResourceReferences abstract sealed { //Static class
	private:
		generic<class T>
			static unsigned int GetNewID(SortedDictionary<unsigned int, T>^ dic) {
				unsigned int i = 0;
				for each(auto k in dic) {
					if (i < k.Key) break;
					i++;
				}
				return i;
			}
			//MESHES
	private:
		static SortedDictionary<unsigned int, RefMesh^>^ m_meshes = gcnew SortedDictionary<unsigned int, RefMesh^>();
	public:
		static RefMesh^ GetMesh(unsigned int id) {
			if (m_meshes->ContainsKey(id)) {
				return m_meshes[id];
			}
			else {
				throw gcnew System::ArgumentException("Not a valid id", "id");
			}
		}
		static RefMesh^ AddMesh(System::String^ path) {
			auto mesh = gcnew RefMesh(path);
			if (!m_meshes->ContainsKey(mesh->ID)) {
				m_meshes->Add(mesh->ID, mesh);
				return mesh;
			}
			else {
				return m_meshes[mesh->ID];
			}
		}
		static RefMesh^ NewMesh(Mesh^ mesh) {
			mesh->Id = GetNewID(m_meshes);
			auto result = gcnew RefMesh(mesh);
			m_meshes->Add(mesh->Id, result);
			return result;
		}
		//SKELETONS
	private:
		static SortedDictionary<unsigned int, RefSkeleton^>^ m_skeletons = gcnew SortedDictionary<unsigned int, RefSkeleton^>();
	public:
		static RefSkeleton^ GetSkeleton(unsigned int id) {
			if (m_skeletons->ContainsKey(id)) {
				return m_skeletons[id];
			}
			else {
				throw gcnew System::ArgumentException("Not a valid id", "id");
			}
		}
		static RefSkeleton^ AddSkeleton(System::String^ path) {
			auto skeleton = gcnew RefSkeleton(path);
			if (!m_skeletons->ContainsKey(skeleton->ID)) {
				m_skeletons->Add(skeleton->ID, skeleton);
				return skeleton;
			}				
			else {
				return m_skeletons[skeleton->ID];
			}
		}
		static RefSkeleton^ NewSkeleton(Skeleton^ skeleton) {
			skeleton->Id = GetNewID(m_skeletons);
			auto result = gcnew RefSkeleton(skeleton);
			m_skeletons->Add(skeleton->Id, result);
			return result;
		}
	};
}