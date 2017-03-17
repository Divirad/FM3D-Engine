#include "ResourceLoader.h"


namespace DesignerLib {

	using ALL_FM3D_NAMESPACES;

	//Help functions
	static Matrix4f CreateMatrix4f(const aiMatrix4x4 mat) {
		Matrix4f result = Matrix4f::Identity();
		result.elements[0] = mat.a1;
		result.elements[1] = mat.b1;
		result.elements[2] = mat.c1;
		result.elements[3] = mat.d1;
		result.elements[4] = mat.a2;
		result.elements[5] = mat.b2;
		result.elements[6] = mat.c2;
		result.elements[7] = mat.d2;
		result.elements[8] = mat.a3;
		result.elements[9] = mat.b3;
		result.elements[10] = mat.c3;
		result.elements[11] = mat.d3;
		result.elements[12] = mat.a4;
		result.elements[13] = mat.b4;
		result.elements[14] = mat.c4;
		result.elements[15] = mat.d4;
		result.Transpose();
		return result;
	}

	static Matrix4f CreateMatrix4f(const aiVector3D& position, const aiQuaternion& rotation, const aiVector3D& scaling) {
		Matrix4f m = CreateMatrix4f(aiMatrix4x4(rotation.GetMatrix()));
		return Matrix4f::Translate(Vector3f(position.x, position.y, position.z)) * CreateMatrix4f(aiMatrix4x4(rotation.GetMatrix())) * Matrix4f::Scale(Vector3f(scaling.x, scaling.y, scaling.z));
	}

	static void FindMeshTransformations(std::vector<Matrix4f>& meshmatrix, const Matrix4f& base, const aiNode* node) {
		Matrix4f delta = CreateMatrix4f(node->mTransformation);
		Matrix4f result = base * delta;

		for (unsigned int i = 0; i<node->mNumMeshes; i++) {
			unsigned int m = node->mMeshes[i];
			meshmatrix[m] = result;
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			FindMeshTransformations(meshmatrix, result, node->mChildren[i]);
		}
	}

	static const aiString* GetMeshName(const aiNode* node) {
		if (node->mNumMeshes > 0)
			return &node->mName;
		bool subMeshes = false;
		const aiString* s;
		for (uint i = 0; i < node->mNumChildren; i++) {
			s = GetMeshName(node->mChildren[i]);
			if (s != nullptr) {
				if(subMeshes)
					return &node->mName;
				subMeshes = true;
			}
		}
		return s;
	}

	bool ResourceLoader::Load(const std::string& path, std::string& mesh, std::vector<std::string>& parts, bool& needSkelet, std::vector<bool>& animated) {
		importer = new Assimp::Importer();
		importer->SetPropertyInteger(AI_CONFIG_PP_LBW_MAX_WEIGHTS, 4);
		scene = importer->ReadFile(path.c_str(), aiProcess_LimitBoneWeights | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
		if (!scene) {
			FM3D::OUTPUT_ERROR(1, "Assimp Error", "Failed loading " + path);
			return false;
		}

		//Return Mesh
		auto name = GetMeshName(scene->mRootNode);
		mesh = name ? name->C_Str() : "Unnamed Mesh";
		needSkelet = false;

		for (uint i = 0; i < scene->mNumMeshes; i++) {
			if (scene->mMeshes[i]->mFaces[0].mNumIndices == 3) {
				meshIds.push_back(i);
				if (scene->mMeshes[i]->mNumBones != 0) needSkelet = true;
				animated.push_back(scene->mMeshes[i]->mNumBones != 0);

				//Return Mesh-part
				std::string name = scene->mMeshes[i]->mName.data;
				if (name.length() == 0) {
					name = "Part " + std::to_string(i);
				}
				parts.push_back(name);
			}
		}

		meshMatrices = new std::vector<Matrix4f>(scene->mNumMeshes, Matrix4f::Identity());
		FindMeshTransformations(*meshMatrices, Matrix4f::Identity(), scene->mRootNode);

		globalInverseTransformation = new Matrix4f(Matrix4f::Identity());
		*globalInverseTransformation = Matrix4f::Invert(CreateMatrix4f(scene->mRootNode->mTransformation));
		boneOffsetMatrices = new std::vector<Matrix4f>();
		animations = new std::vector<Animation>();
		return true;
	}

	MeshPart* ResourceLoader::GetMeshPart(uint id) {
		aiMesh* mesh = scene->mMeshes[meshIds[id]];

		for (unsigned int j = 0; j < mesh->mNumBones; j++) {
			aiBone *bone = mesh->mBones[j];
			std::map<std::string, unsigned int>::iterator it = boneIndex.find(bone->mName.data);
			unsigned int jointIndex = boneIndex.size();
			if (it == boneIndex.end()) {
				boneIndex[bone->mName.data] = jointIndex;
				boneOffsetMatrices->push_back(CreateMatrix4f(bone->mOffsetMatrix));
			}
			else {
				jointIndex = it->second;
				if ((*boneOffsetMatrices)[jointIndex] != CreateMatrix4f(bone->mOffsetMatrix)) {
					std::cout << "FATAL PROGRAMMING ERROR: Same Bones have different Matrices!" << std::endl;
				}
			}
		}

		bool isAnimated = mesh->mNumBones != 0;

		uint vertexData = Vertices::POSITION | Vertices::TEXCOORD | Vertices::NORMAL;
		if (isAnimated) vertexData = vertexData | Vertices::BONE_DATA;
		auto result = new MeshPart(mesh->mNumFaces * 3, nullptr, Vertices(mesh->mNumVertices, vertexData), sizeof(uint), false);
		uint* indices = new uint[result->indicesCount];
		Vertices& vertices = result->vertices;

		for (uint i = 0; i < mesh->mNumFaces; i++) {
			indices[(i * 3) + 0] = mesh->mFaces[i].mIndices[0];
			indices[(i * 3) + 1] = mesh->mFaces[i].mIndices[1];
			indices[(i * 3) + 2] = mesh->mFaces[i].mIndices[2];
		}

		for (uint i = 0; i < vertices.GetVertexCount(); i++) {
			aiVector3D pos = mesh->mVertices[i];
			/*if(isAnimated)*/ vertices.SetPosition((*meshMatrices)[id] * Vector3f(pos.x, pos.y, pos.z), i);
			//else vertices.SetPosition(Vector3f(pos.x, pos.y, pos.z), i);
			aiVector3D uv = mesh->mTextureCoords[0][i];
			vertices.SetTexCoord(Vector2f(uv.x, 1.0f - uv.y), i);
			aiVector3D norm = mesh->mNormals[i];
			vertices.SetNormal(Vector3f(norm.x, norm.y, norm.z), i);

			if (isAnimated) {
				vertices.SetBoneIndex(Vector4i(0, 0, 0, 0), i);
				vertices.SetBoneWeight(Vector4f(0.0f, 0.0f, 0.0f, 0.0f), i);
			}

		}

		if (isAnimated) {
			for (unsigned j = 0; j < mesh->mNumBones; j++) {
				//meshData[i].bones[j] *= Matrix4f::Invert(meshMatrix);
				aiBone* bone = mesh->mBones[j];
				std::map<std::string, unsigned int>::iterator it = boneIndex.find(bone->mName.data);
				if (it == boneIndex.end())
					std::cout << "Mesh " << meshIds[id] << " bone " << bone->mName.data << " not found" << std::endl;
				for (unsigned k = 0; k < bone->mNumWeights; k++) {
					int v = bone->mWeights[k].mVertexId;

					Vector4f& vw = vertices.GetBoneWeight(v);
					Vector4i& vi = vertices.GetBoneIndex(v);
					if (vw.x == 0.0f) {
						vw.x = bone->mWeights[k].mWeight;
						vi.x = it->second;
					}
					else if (vw.y == 0.0f) {
						vw.y = bone->mWeights[k].mWeight;
						vi.y = it->second;
					}
					else if (vw.z == 0.0f) {
						vw.z = bone->mWeights[k].mWeight;
						vi.z = it->second;
					}
					else if (vw.w == 0.0f) {
						vw.w = bone->mWeights[k].mWeight;
						vi.w = it->second;
					}
					else {
						std::cout << "Too many bone weights!" << std::endl;
					}
				}
			}
		}

		result->indices = indices;
		return result;
	}

	Skeleton* ResourceLoader::GetSkeleton() {
		return new FM3D::Skeleton(*boneOffsetMatrices, *animations);
	}

	ResourceLoader::~ResourceLoader() {
		delete[] meshMatrices;
		delete globalInverseTransformation;
		//delete scene;
		//delete importer;
	}

}