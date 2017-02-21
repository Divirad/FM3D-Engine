#include <Engine.h>

namespace FM3D {

	using namespace std;

	FT_Library ExternFileManager::s_ft;

	int nodee = 0;

	Texture* ExternFileManager::ReadTextureFile(const char* filename, RenderSystem* renderSystem, Texture::FilterMode filterMode, Texture::WrapMode wrapMode, Texture::MipMapMode mipMapMode) {
		string path = FileManager::resourcePath + string(filename);

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = nullptr;
		fif = FreeImage_GetFileType(path.c_str(), 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(path.c_str());
		if (fif == FIF_UNKNOWN)
			return nullptr;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, path.c_str());

		//MessageBox(hWnd, filename, "Could not load image '", MB_OK);

		BYTE* pixels = FreeImage_GetBits(dib);
		uint width = FreeImage_GetWidth(dib);
		uint height = FreeImage_GetHeight(dib);
		uint bits = FreeImage_GetBPP(dib);

		int size = width * height * (bits / 8);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(dib);

		if (result == NULL) {
			MessageBox(0, L"Error on loading Texture", L"Error", MB_OK | MB_ICONERROR);
			return nullptr;
		}
		
		return renderSystem->CreateTexture(width, height, filterMode, wrapMode, mipMapMode, (char*)result, bits);
	}

	static void DrawNodeTree(const aiNode* node, int level = 0) {
		for (int i = 0; i < level; i++) cout << "   ";
		cout << node->mName.data << endl;
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			DrawNodeTree(node->mChildren[i], level + 1);
		}
	}

	static Matrix4f CreateMatrix4f(const aiMatrix4x4 mat) {
		Matrix4f result = Matrix4f::Null();
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

	static Transformation CreateTransformation(const aiVector3D& position, const aiQuaternion& rotation, const aiVector3D& scaling) {
		//return{ Vector3f(position.x, position.y, position.z),
		//	Quaternionf(rotation.w, rotation.x, rotation.y, rotation.z).ToAngles(),
		//	Vector3f(scaling.x, scaling.y, scaling.z) };
		if(Vector3f(scaling.x, scaling.y, scaling.z).ToString() != "(1, 1, 1)")
			std::cout << Vector3f(scaling.x, scaling.y, scaling.z) << std::endl;
		return Transformation(Vector3f(position.x, position.y, position.z), Quaternionf(rotation.w, rotation.x, rotation.y, rotation.z), Vector3f(scaling.x, scaling.y, scaling.z));
	}

	static void FindMeshTransformations(Matrix4f* meshmatrix, const Matrix4f& base, const aiNode* node) {
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

	static MeshPart InitializePart(const aiScene* scene, uint meshIndex, const Matrix4f& meshMatrix, map<string, unsigned int>& boneIndex, std::vector<Matrix4f>& boneOffsetMatrices, bool supportsInstancing, bool useAnimation, const Matrix4f& modelMatrix) {
		aiMesh* mesh = scene->mMeshes[meshIndex];
		uint uvidnex = 0;
		//if (mesh->GetNumUVChannels() != 1) uvidnex = 1;

		for (unsigned int j = 0; j < mesh->mNumBones; j++) {
			aiBone *bone = mesh->mBones[j];
			map<string, unsigned int>::iterator it = boneIndex.find(bone->mName.data);
			unsigned int jointIndex = boneIndex.size();
			if (it == boneIndex.end()) {
				boneIndex[bone->mName.data] = jointIndex;
				boneOffsetMatrices.push_back(CreateMatrix4f(bone->mOffsetMatrix));
			} else {
				jointIndex = it->second;
				if (boneOffsetMatrices[jointIndex] != CreateMatrix4f(bone->mOffsetMatrix)) {
					cout << "FATAL PROGRAMMING ERROR: Same Bones have different Matrices!" << endl;
				}
			}
		}

		bool isAnimated = (mesh->mNumBones != 0) && useAnimation;

		uint vertexData = Vertices::POSITION | Vertices::TEXCOORD | Vertices::NORMAL;
		if (isAnimated) vertexData = vertexData | Vertices::BONE_DATA;
		Vertices vertices(mesh->mNumVertices, vertexData);
		uint* indices = new uint[mesh->mNumFaces * 3];
		
		for (uint i = 0; i < mesh->mNumFaces; i++) {
			indices[(i * 3) + 0] = mesh->mFaces[i].mIndices[0];
			indices[(i * 3) + 1] = mesh->mFaces[i].mIndices[1];
			indices[(i * 3) + 2] = mesh->mFaces[i].mIndices[2];
		}

		for (uint i = 0; i < vertices.GetVertexCount(); i++) {
			aiVector3D pos = mesh->mVertices[i];
			/*if(isAnimated)*/ vertices.SetPosition(modelMatrix * (meshMatrix * Vector3f(pos.x, pos.y, pos.z)), i);
			//else vertices.SetPosition(Vector3f(pos.x, pos.y, pos.z), i);
			aiVector3D uv = mesh->mTextureCoords[uvidnex][i];
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
				map<string, unsigned int>::iterator it = boneIndex.find(bone->mName.data);
				if (it == boneIndex.end())
					cout << "Mesh " << meshIndex << " bone " << bone->mName.data << " not found" << endl;
				for (unsigned k = 0; k < bone->mNumWeights; k++) {
					int v = bone->mWeights[k].mVertexId;

					Vector4f& vw = vertices.GetBoneWeight(v);
					Vector4i& vi = vertices.GetBoneIndex(v);
					if (vw.x == 0.0f) {
						vw.x = bone->mWeights[k].mWeight;
						vi.x = it->second;
					} else if (vw.y == 0.0f) {
						vw.y = bone->mWeights[k].mWeight;
						vi.y = it->second;
					} else if (vw.z == 0.0f) {
						vw.z = bone->mWeights[k].mWeight;
						vi.z = it->second;
					} else if (vw.w == 0.0f) {
						vw.w = bone->mWeights[k].mWeight;
						vi.w = it->second;
					} else {
						std::cout << "Too many bone weights!" << std::endl;
					}
				}
			}
		}
		return MeshPart(mesh->mNumFaces * 3, indices, std::move(vertices), sizeof(uint), supportsInstancing);
	}

	static aiNode* FindNode(aiNode *node, const char *name) {
		if (strcmp(name, node->mName.data) == 0)
			return node;

		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			aiNode *res = FindNode(node->mChildren[i], name);
			if (res != 0)
				return res;
		}

		return 0;
	}

	struct Channel {
		vector<Transformation> mat;
		Channel *parent;
		aiNodeAnim *node;
		uint bone;
#define UNUSEDCHANNEL 0xffffffff
	};

	static void CalcMatricesWithNodes(std::vector<std::vector<Transformation>>& matrices, Channel* channels, uint numChannels, Matrix4f& globalInverseTransformation) {
		for (uint c = 0; c < numChannels; c++) {
			uint bone = channels[c].bone;
			if (bone == UNUSEDCHANNEL) continue;
			uint numKeys = channels[c].mat.size();
			matrices[bone] = std::vector<Transformation>(numKeys, Transformation());
			for (uint key = 0; key < numKeys; key++) {
				Transformation mat;
				for (Channel* node = &channels[c]; node; node = node->parent) {
					mat = node->mat[key] * mat;
				}
				//mat = globalInverseTransformation * mat;
				matrices[bone][key] = mat;
			}
		}
	}

	static const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const aiNode* node) {
		for (uint i = 0; i < pAnimation->mNumChannels; i++) {
			const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

			if (pNodeAnim->mNodeName == node->mName) {
				return pNodeAnim;
			}
		}

		return nullptr;
	}

	static int CreateBoneStructure(const aiAnimation* pAnimation, vector<Animation::Bone>& bones, vector<Animation::AnimatedBone>& abones, aiNode* node, map<string, unsigned int>& boneIndex) {
		std::vector<uint> children;
		for (uint i = 0; i < node->mNumChildren; i++) {
			aiNode* n = node->mChildren[i];
			int indx = CreateBoneStructure(pAnimation, bones, abones, n, boneIndex);
			if (indx > 0) {
				children.push_back(indx);
			}
		}

		const aiNodeAnim* animNode = FindNodeAnim(pAnimation, node);
		map<string, unsigned int>::iterator it = boneIndex.find(node->mName.data);

		int index = -1, aindex = -1;

		if (it != boneIndex.end()) {
			index = it->second;
			if (animNode) {
				vector<pair<double, Vector3f>> positions;
				vector<pair<double, Quaternionf>> rotations;
				vector<pair<double, Vector3f>> scalings;
				for (uint i = 0; i < animNode->mNumPositionKeys; i++) {
					const aiVector3D& vec = animNode->mPositionKeys[i].mValue;
					positions.push_back(make_pair(animNode->mPositionKeys[i].mTime, Vector3f(vec.x, vec.y, vec.z)));
				}
				for (uint i = 0; i < animNode->mNumRotationKeys; i++) {
					const aiQuaternion& quat = animNode->mRotationKeys[i].mValue;
					rotations.push_back(make_pair(animNode->mRotationKeys[i].mTime, Quaternionf(quat.w, quat.x, quat.y, quat.z)));
				}
				for (uint i = 0; i < animNode->mNumScalingKeys; i++) {
					const aiVector3D& vec = animNode->mScalingKeys[i].mValue;
					scalings.push_back(make_pair(animNode->mScalingKeys[i].mTime, Vector3f(vec.x, vec.y, vec.z)));
				}

				aindex = abones.size();
				abones.push_back({ TimeList<Vector3f>(move(positions), REPEAT), TimeList<Quaternionf>(move(rotations), REPEAT),TimeList<Vector3f>(move(scalings), REPEAT) });
			}
			else {
				cout << "Necessary node is not animated!" << endl;
			}
		}
		
		bones.push_back({ index, aindex, move(children) });
		return bones.size() - 1;
		//}
		//else {
		//	map<string, unsigned int>::iterator it = boneIndex.find(node->mName.data);
		//	if (it != boneIndex.end()) {
		//		cout << "Needed node is not animated!" << endl;
		//	}
		//	return -1;
		//}

	}

	static void InitializeAnimation(const aiScene* scene, uint animationIndex, const char* filename, uint boneCount, map<string, unsigned int>& boneIndex, Matrix4f& globalInverseTransformation, Skeleton* skeleton) {
		aiAnimation* animation = scene->mAnimations[animationIndex];
		uint numChannels = animation->mNumChannels;
		if (numChannels == 0)
			cout << "Loading AnimatedModel: no animation channels for " << animation->mName.data << " " << filename << endl;
		if (numChannels < boneCount)
			cout << "Loading AnimatedModel: " << filename << " animation " << animationIndex << ": Can only handle when all bones are used (" << numChannels << " out of " << boneCount << ")" << endl;
		/*else if (numChannels > boneCount) {
			cout << "Loading AnimatedModel: " << filename << " animation " << animationIndex << ": Too many channels (" << numChannels << " instead of " << boneCount << ")" << endl;
			cout << "Unknown bones: " << endl;
			for (int j = 0; j < numChannels; j++) {
				aiNodeAnim *ain = animation->mChannels[j];
				if (boneIndex.find(ain->mNodeName.C_Str()) == boneIndex.end()) {
					cout << "   " << ain->mNodeName.C_Str() << endl;
				}
			}
		}*/
		/*
		//Channel* channels = new Channel[numChannels];
		//uint unusedBones = 0u;
		//bool foundOneBone = false;
		//for (unsigned int j = 0; j < numChannels; j++) {
		//	aiNodeAnim *ain = animation->mChannels[j];
		//	if (ain->mNumPositionKeys != ain->mNumRotationKeys || ain->mNumScalingKeys != ain->mNumRotationKeys)
		//		cout << "Loading AnimatedModel: " << filename << " Bad animation setup: Pos keys " << ain->mNumPositionKeys << ", rot keys " << ain->mNumRotationKeys << ", scaling keys " << ain->mNumScalingKeys << endl;
		//	channels[j].node = ain;
		//	channels[j].parent = 0;
		//	map<string, unsigned int>::iterator it = boneIndex.find(ain->mNodeName.data);
		//	if (it == boneIndex.end()) {
		//		channels[j].bone = UNUSEDCHANNEL;
		//		unusedBones++;
		//		continue;
		//	}
		//	foundOneBone = true;
		//	unsigned int bone = it->second;
		//	channels[j].bone = bone;
		//}
		//if (!foundOneBone)
		//	cout << "Loading AnimatedModel: " << filename << " animation " << animationIndex << " no bones used" << endl;

		//for (unsigned j = 0; j < numChannels; j++) {
		//	aiNode *n = FindNode(scene->mRootNode, channels[j].node->mNodeName.data);
		//	if (n == 0 || n->mParent == 0)
		//		continue;
		//	n = n->mParent;
		//	for (unsigned p = 0; p < numChannels; p++) {
		//		if (p == j || strcmp(n->mName.data, channels[p].node->mNodeName.data) != 0)
		//			continue;
		//		channels[j].parent = &channels[p];
		//		break;
		//	}
		//}

		//vector<uint> keyIndices(numChannels);
		//for (uint i = 0; i < numChannels; i++) keyIndices[i] = 0u;
		//vector<uint> channelIndices;
		//std::vector<double> times(0);
		//double time = -1.0;
		//double startTime = channels[0].node->mPositionKeys[0].mTime;
		//double endTime = channels[0].node->mPositionKeys[channels[0].node->mNumPositionKeys - 1].mTime;

		//for (uint c = 0u; c < numChannels; c++) {
		//	if (endTime != channels[c].node->mPositionKeys[channels[c].node->mNumPositionKeys - 1].mTime)
		//		cout << "Loading AnimatedModel: " << filename << " animation " << animationIndex << " Bad animation setup: All channels don't end at the same time" << endl;
		//	
		//	if (startTime != channels[c].node->mPositionKeys[0].mTime)
		//		cout << "Loading AnimatedModel: " << filename << " animation " << animationIndex << " Bad animation setup: All channels don't start at the same time" << endl;
		//}

		////Creating Matrices for all keys
		//for (int keys = 0; true; keys++) {
		//	time = -1.0;
		//	//Find smallest time with channel indices
		//	for (uint c = 0u; c < numChannels; c++) {
		//		double pt = channels[c].node->mPositionKeys[keyIndices[c]].mTime;
		//		double rt = channels[c].node->mRotationKeys[keyIndices[c]].mTime;
		//		double st = channels[c].node->mScalingKeys[keyIndices[c]].mTime;
		//		if (pt == rt && pt == st) {
		//			if (pt < time || time < 0.0) {
		//				time = pt;
		//				channelIndices.clear();
		//				channelIndices.push_back(c);
		//			} else if (pt == time) {
		//				channelIndices.push_back(c);
		//			}
		//		} else {
		//			cout << "Loading AnimatedModel: " << filename << " Bad animation setup: Channel " << c << " Keys " << keyIndices[c] << " have different times" << endl;
		//		}
		//	}
		//	times.push_back(time - startTime);
		//	if (time == endTime) break;
		//	for (uint i : channelIndices) keyIndices[i]++;

		//	//Interpolate between the two Matrices near the time
		//	for (uint c = 0u; c < numChannels; c++) {
		//		aiNodeAnim* node = channels[c].node;
		//		uint index0 = keyIndices[c] - 1;
		//		uint index1 = keyIndices[c];
		//		Transformation left = CreateTransformation(node->mPositionKeys[index0].mValue, node->mRotationKeys[index0].mValue, node->mScalingKeys[index0].mValue);
		//		Transformation right = CreateTransformation(node->mPositionKeys[index1].mValue, node->mRotationKeys[index1].mValue, node->mScalingKeys[index1].mValue);
		//		double timeLeft = node->mPositionKeys[index0].mTime;
		//		double timeRight = node->mPositionKeys[index1].mTime;

		//		//Matrix4f m = Matrix4f::Interpolate(left, right, timeLeft, time, timeRight);
		//		auto trans = left.Interpolate(right, static_cast<float>((time - timeLeft) / (timeRight - timeLeft)));
		//		channels[c].mat.push_back(trans);
		//	}
		//}

		////Matrices for last Key
		//for (uint c = 0u; c < numChannels; c++) {
		//	aiNodeAnim* node = channels[c].node;
		//	uint key = node->mNumPositionKeys - 1;
		//	channels[c].mat.push_back(CreateTransformation(node->mPositionKeys[key].mValue, node->mRotationKeys[key].mValue, node->mScalingKeys[key].mValue));
		//}

		//std::vector<std::vector<Transformation>> matrices(boneCount);
		//CalcMatricesWithNodes(matrices, channels, numChannels, globalInverseTransformation);

		//std::vector<std::vector<Transformation>> matrices2(matrices);
		*/

		vector<Animation::Bone> bones;
		vector<Animation::AnimatedBone> abones;
		int rootIndex = CreateBoneStructure(animation, bones, abones, scene->mRootNode, boneIndex);

		skeleton->AddAnimation(Animation(animation->mName.data, move(bones), move(abones), rootIndex, animation->mTicksPerSecond != 0.0 ? animation->mTicksPerSecond : 25.0, boneCount, skeleton));
	}
	
	void ExternFileManager::ReadModelFile(const char* filename, RenderSystem* renderSystem, Model** result, bool supportsInstancing, bool useAnimation, const Matrix4f& modelMatrix) {
		string path = FileManager::resourcePath + string(filename);
		Assimp::Importer importer;
		const aiScene* scene;

		importer.SetPropertyInteger(AI_CONFIG_PP_LBW_MAX_WEIGHTS, 4);
		scene = importer.ReadFile(path.c_str(), aiProcess_LimitBoneWeights | aiProcess_GenUVCoords | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
		if (!scene) cout << "Assimp loading " << filename << ": " << importer.GetErrorString() << endl;

		vector<uint> meshIds;
		uint materialCount = scene->mNumMaterials;
		bool isAnimated = false;
		for (uint i = 0; i < scene->mNumMeshes; i++) {
			if (scene->mMeshes[i]->mFaces[0].mNumIndices == 3) {
				if (scene->mMeshes[i]->mNumBones != 0) isAnimated = true;
				meshIds.push_back(i);
			}
		}

		std::vector<Matrix4f> meshMatrices(scene->mNumMeshes, Matrix4f::Identity());
		FindMeshTransformations(&meshMatrices[0], Matrix4f::Identity(), scene->mRootNode);

		Matrix4f globalInverseTransformation = Matrix4f::Invert(CreateMatrix4f(scene->mRootNode->mTransformation));

		//DrawNodeTree(scene->mRootNode);

		//MESH SECTION
		map<string, unsigned int> boneIndex;
		std::vector<Matrix4f> boneOffsetMatrices;
		std::vector<MeshPart> parts;
		parts.reserve(meshIds.size());
		uint c = 0;
		for (uint meshIndex : meshIds) {
			parts.push_back(InitializePart(scene, meshIndex, meshMatrices[c], boneIndex, boneOffsetMatrices, supportsInstancing, useAnimation, modelMatrix));
			c++;
		}

		//Skeleton
		for (Matrix4f& offset : boneOffsetMatrices) {
			offset *= Matrix4f::Invert(meshMatrices[0]);
		}
		Skeleton* skeleton = new Skeleton(std::vector<Matrix4f>(boneOffsetMatrices), std::vector<Animation>());

		//ANIMATION SECTION
		for (unsigned int i = 0; i < scene->mNumAnimations; i++) {
			InitializeAnimation(scene, i, filename, boneOffsetMatrices.size(), boneIndex, globalInverseTransformation, skeleton);
		}

		Mesh* mesh = renderSystem->CreateMesh(isAnimated ? skeleton : nullptr, supportsInstancing, parts);
		for (MeshPart& p : parts) {
			delete[] (uint*) p.indices;
		}
		if(isAnimated && useAnimation) *result = new AnimatedModel(mesh, std::vector<const Material*>(parts.size()), nullptr, 0.0);
		else *result = new Model(mesh, std::vector<const Material*>(parts.size()));
	}

	/*void ExternFileManager::ReadModelFile(const char* filename, StaticModel* model) {
		string path = FileManager::resourcePath + string(filename);
		ifstream file;
		file.open(path, ios::in);

		StaticModel::VertexData* data;
		uint* indices;

		vector<Vector3f> vVertices;
		vector<Vector2f> vTexCoords;
		vector<Vector3f> vNormals;
		vector<int> vIndices;

		string line;
		while (getline(file, line)) {
			if (line.substr(0, 2) == "v ") {
				istringstream s(line.substr(2));
				Vector3f v;
				s >> v.x;
				s >> v.y;
				s >> v.z;
				vVertices.push_back(v);
			} else if (line.substr(0, 3) == "vt ") {
				istringstream s(line.substr(2));
				Vector2f v;
				s >> v.x;
				s >> v.y;
				vTexCoords.push_back(v);
			} else if (line.substr(0, 3) == "vn ") {
				istringstream s(line.substr(2));
				Vector3f v;
				s >> v.x;
				s >> v.y;
				s >> v.z;
				vNormals.push_back(v);
			} else if (line.substr(0, 2) == "f ") {
				data = new StaticModel::VertexData[vVertices.size()];
				break;
			}
		}

		do {
			if (!(line.substr(0, 2) == "f ")) {
				continue;
			}
			istringstream s(line.substr(2));
			istringstream s2;
			for (int i = 0; i < 3; i++) {
				int vertexPointer, texturePointer, normalPointer;
				s >> vertexPointer;
				s.ignore(s.str().length(), '/');
				s >> texturePointer;
				s.ignore(s.str().length(), '/');
				s >> normalPointer;

				vertexPointer--;
				texturePointer--;
				normalPointer--;

				vIndices.push_back(vertexPointer);
				(data[vertexPointer]).uv = vTexCoords[texturePointer];
				(data[vertexPointer]).normal = vNormals[normalPointer];
			}
		} while (getline(file, line));

		indices = new uint[vIndices.size()];

		int vertexPointer = 0;
		for (Vector3f vertex : vVertices) {
			(data[vertexPointer++]).position = vertex;
		}

		for (int i = 0; i < (int)vIndices.size(); i++) {
			indices[i] = vIndices[i];
		}

		model->Initialize(vVertices.size(), vIndices.size(), indices, data);
		file.close();
		delete[] data;
		delete[] indices;
	}*/

	bool ExternFileManager::ReadFontFile(const char* filename, uint size, Vector2f scale, RenderSystem* renderSystem, Font** result) {
		FT_Face face;
		if (FT_New_Face(s_ft, (FileManager::resourcePath + string(filename)).c_str(), 0, &face)) {
			std::cout << "Could not open font: " << FileManager::resourcePath + string(filename) << std::endl;
			return false;
		}
		FT_Set_Pixel_Sizes(face, 0, size);

		FT_GlyphSlot g = face->glyph;
		int w = 0;
		int h = 0;

		for (int i = 0; i < 256; i++) {
			if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
				fprintf(stderr, "Loading character %c failed!\n", i);
				continue;
			}

			w += g->bitmap.width;
			h = (uint)h >= g->bitmap.rows ? h : g->bitmap.rows;

		}

		Texture* tex = renderSystem->CreateTexture(w, h, Texture::NEAREST, Texture::CLAMP_TO_EDGE, Texture::NONE, (char*)nullptr, 8);
		tex->BindForEditing();

		int x = 0;

		Character* c = new Character[256];

		byte* texture = new byte[w*h];
		for (int i = 0; i < w*h; i++) texture[i] = 0;

		for (int i = 0; i < 256; i++) {
			if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
				c[i] = { 0, 0, 0, 0, 0, 0, 0 };
				continue;
			}

			c[i].advanceX = (float) (g->advance.x >> 6);
			c[i].advanceY = (float) (g->advance.y >> 6);

			c[i].width = (float) g->bitmap.width;
			c[i].height = (float) g->bitmap.rows;

			c[i].left = (float) g->bitmap_left;
			c[i].top = (float) g->bitmap_top;

			tex->SetPixels(0, x, 0, g->bitmap.width, g->bitmap.rows, g->bitmap.buffer);

			c[i].offsetX = (float)x / w;


			x += g->bitmap.width;
		}
		tex->Unbind();

		*result = new Font(c, scale, tex);
		return true;
	}

	bool ExternFileManager::Initialize() {
		if (FT_Init_FreeType(&s_ft)) {
			std::cout << "Could not init freetype library" << std::endl;
			return false;
		}
		return true;
	}

	bool ExternFileManager::PathName(const string in, string* name, string* end) {
		bool result = false;
		int i;
		for (i = in.length() - 1; i >= 0; i--) {
			if (in[i] == '\\') {
				result = true;
				break;
			}
		}
		if (!result) {
			MessageBox(0, L"Not a Valid Filepath", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = false;
		int j;
		for (j = in.length() - 1; j >= 0; j--) {
			if (in[j] == '.') {
				result = true;
				break;
			}
		}
		if (!result) {
			MessageBox(0, L"Not a Valid Fileending", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		string tmp = "";

		if (name != NULL) {
			*name = "";
			for (int x = i + 1; x < j; x++) {
				tmp += in[x];
			}
			*name = tmp;
		}

		tmp = "";

		if (end != NULL) {
			*end = "";
			for (int x = j + 1; x < (int)in.length(); x++) {
				tmp += in[x];
			}
			*end = tmp;
		}
		return true;
	}
}
