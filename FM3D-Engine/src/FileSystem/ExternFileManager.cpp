#include <Engine.h>

namespace FM3D {

	using namespace std;

	FT_Library ExternFileManager::s_ft;

	int nodee = 0;

	bool ExternFileManager::ReadTextureFile(const char* filename, Texture* texture, Texture::FilterMode filterMode, Texture::WrapMode wrapMode, Texture::MipMapMode mipMapMode) {
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
			return false;
		}

		texture->Initialize(width, height, filterMode, wrapMode, mipMapMode, (char*)result, bits);
		return true;
	}

	static void DrawNodeTree(const aiNode* node, int level = 0) {
		for (int i = 0; i < level; i++) cout << "   ";
		cout << node->mName.data << endl;
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			DrawNodeTree(node->mChildren[i], level + 1);
		}
	}

	static Matrix4f CreateMatrix4f(const aiMatrix4x4 mat) {
		Matrix4f result;
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

	static void InitializePart(MeshPart& result, const aiScene* scene, uint meshIndex, const Matrix4f& meshMatrix, map<string, unsigned int>& boneIndex, DynamicRawArray<Matrix4f>& boneOffsetMatrices, bool supportsInstancing, bool useAnimation, const Matrix4f& modelMatrix) {
		aiMesh* mesh = scene->mMeshes[meshIndex];

		for (unsigned int j = 0; j < mesh->mNumBones; j++) {
			aiBone *bone = mesh->mBones[j];
			map<string, unsigned int>::iterator it = boneIndex.find(bone->mName.data);
			unsigned int jointIndex = boneIndex.size();
			if (it == boneIndex.end()) {
				boneIndex[bone->mName.data] = jointIndex;
				boneOffsetMatrices.AdvanceBy(1);
				boneOffsetMatrices[boneOffsetMatrices.Size()-1] = CreateMatrix4f(bone->mOffsetMatrix);
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
		result.indicesCount = mesh->mNumFaces * 3;
		result.indexSize = sizeof(uint);
		result.supportsInstancing = supportsInstancing;
		result.vertices = Vertices(mesh->mNumVertices, vertexData);
		result.indices = nullptr;
		uint* indices = new uint[result.indicesCount];
		Vertices& vertices = result.vertices;
		
		for (uint i = 0; i < mesh->mNumFaces; i++) {
			indices[(i * 3) + 0] = mesh->mFaces[i].mIndices[0];
			indices[(i * 3) + 1] = mesh->mFaces[i].mIndices[1];
			indices[(i * 3) + 2] = mesh->mFaces[i].mIndices[2];
		}

		for (uint i = 0; i < vertices.GetVertexCount(); i++) {
			aiVector3D pos = mesh->mVertices[i];
			/*if(isAnimated)*/ vertices.SetPosition(modelMatrix * (meshMatrix * Vector3f(pos.x, pos.y, pos.z)), i);
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

		result.indices = indices;
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
		vector<Matrix4f> mat;
		Channel *parent;
		aiNodeAnim *node;
		uint bone;
#define UNUSEDCHANNEL 0xffffffff
	};

	static void CalcMatricesWithNodes(RawArray<Array<Matrix4f>>& matrices, Channel* channels, uint numChannels, Matrix4f& globalInverseTransformation) {
		for (uint c = 0; c < numChannels; c++) {
			uint bone = channels[c].bone;
			if (bone == UNUSEDCHANNEL) continue;
			uint numKeys = channels[c].mat.size();
			new (&matrices[bone]) Array<Matrix4f>(numKeys);
			for (uint key = 0; key < numKeys; key++) {
				Matrix4f mat = Matrix4f::Identity();
				for (Channel* node = &channels[c]; node; node = node->parent) {
					mat = node->mat[key] * mat;
				}
				mat = globalInverseTransformation * mat;
				matrices[bone][key] = mat;
			}
		}
	}

	static void InitializeAnimation(Animation* inAnimation, const aiScene* scene, uint animationIndex, const char* filename, uint boneCount, map<string, unsigned int>& boneIndex, Matrix4f& globalInverseTransformation) {
		aiAnimation *animation = scene->mAnimations[animationIndex];
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
		Channel* channels = new Channel[numChannels];
		uint unusedBones = 0u;
		bool foundOneBone = false;
		for (unsigned int j = 0; j < numChannels; j++) {
			aiNodeAnim *ain = animation->mChannels[j];
			if (ain->mNumPositionKeys != ain->mNumRotationKeys || ain->mNumScalingKeys != ain->mNumRotationKeys)
				cout << "Loading AnimatedModel: " << filename << " Bad animation setup: Pos keys " << ain->mNumPositionKeys << ", rot keys " << ain->mNumRotationKeys << ", scaling keys " << ain->mNumScalingKeys << endl;
			channels[j].node = ain;
			channels[j].parent = 0;
			map<string, unsigned int>::iterator it = boneIndex.find(ain->mNodeName.data);
			if (it == boneIndex.end()) {
				channels[j].bone = UNUSEDCHANNEL;
				unusedBones++;
				continue;
			}
			foundOneBone = true;
			unsigned int bone = it->second;
			channels[j].bone = bone;
		}
		if (!foundOneBone)
			cout << "Loading AnimatedModel: " << filename << " animation " << animationIndex << " no bones used" << endl;

		for (unsigned j = 0; j < numChannels; j++) {
			aiNode *n = FindNode(scene->mRootNode, channels[j].node->mNodeName.data);
			if (n == 0 || n->mParent == 0)
				continue;
			n = n->mParent;
			for (unsigned p = 0; p < numChannels; p++) {
				if (p == j || strcmp(n->mName.data, channels[p].node->mNodeName.data) != 0)
					continue;
				channels[j].parent = &channels[p];
				break;
			}
		}

		vector<uint> keyIndices(numChannels);
		for (uint i = 0; i < numChannels; i++) keyIndices[i] = 0u;
		vector<uint> channelIndices;
		DynamicRawArray<double> times(0);
		double time = -1.0;
		double startTime = channels[0].node->mPositionKeys[0].mTime;
		double endTime = channels[0].node->mPositionKeys[channels[0].node->mNumPositionKeys - 1].mTime;

		for (uint c = 0u; c < numChannels; c++) {
			if (endTime != channels[c].node->mPositionKeys[channels[c].node->mNumPositionKeys - 1].mTime)
				cout << "Loading AnimatedModel: " << filename << " animation " << animationIndex << " Bad animation setup: All channels don't end at the same time" << endl;
			
			if (startTime != channels[c].node->mPositionKeys[0].mTime)
				cout << "Loading AnimatedModel: " << filename << " animation " << animationIndex << " Bad animation setup: All channels don't start at the same time" << endl;
		}

		//Creating Matrices for all keys
		for (int keys = 0; true; keys++) {
			time = -1.0;
			//Find smallest time with channel indices
			for (uint c = 0u; c < numChannels; c++) {
				double pt = channels[c].node->mPositionKeys[keyIndices[c]].mTime;
				double rt = channels[c].node->mRotationKeys[keyIndices[c]].mTime;
				double st = channels[c].node->mScalingKeys[keyIndices[c]].mTime;
				if (pt == rt && pt == st) {
					if (pt < time || time < 0.0) {
						time = pt;
						channelIndices.clear();
						channelIndices.push_back(c);
					} else if (pt == time) {
						channelIndices.push_back(c);
					}
				} else {
					cout << "Loading AnimatedModel: " << filename << " Bad animation setup: Channel " << c << " Keys " << keyIndices[c] << " have different times" << endl;
				}
			}
			times.Push_Back(time - startTime);
			if (time == endTime) break;
			for (uint i : channelIndices) keyIndices[i]++;

			//Interpolate between the two Matrices near the time
			for (uint c = 0u; c < numChannels; c++) {
				aiNodeAnim* node = channels[c].node;
				uint index0 = keyIndices[c] - 1;
				uint index1 = keyIndices[c];
				Matrix4f left = CreateMatrix4f(node->mPositionKeys[index0].mValue, node->mRotationKeys[index0].mValue, node->mScalingKeys[index0].mValue);
				Matrix4f right = CreateMatrix4f(node->mPositionKeys[index1].mValue, node->mRotationKeys[index1].mValue, node->mScalingKeys[index1].mValue);
				double timeLeft = node->mPositionKeys[index0].mTime;
				double timeRight = node->mPositionKeys[index1].mTime;

				Matrix4f m = Matrix4f::Interpolate(left, right, timeLeft, time, timeRight);
				channels[c].mat.push_back(m);
			}
		}

		//Matrices for last Key
		for (uint c = 0u; c < numChannels; c++) {
			aiNodeAnim* node = channels[c].node;
			uint key = node->mNumPositionKeys - 1;
			channels[c].mat.push_back(CreateMatrix4f(node->mPositionKeys[key].mValue, node->mRotationKeys[key].mValue, node->mScalingKeys[key].mValue));
		}

		RawArray<Array<Matrix4f>> matrices(boneCount);
		CalcMatricesWithNodes(matrices, channels, numChannels, globalInverseTransformation);

		new (inAnimation) Animation(animation->mName.data, matrices, RawArray<double>(times), animation->mTicksPerSecond != 0.0 ? animation->mTicksPerSecond : 25.0, animation->mDuration);
	}
	
	void ExternFileManager::ReadModelFile(const char* filename, RenderSystem* renderSystem, Model** result, bool supportsInstancing, bool useAnimation, const Matrix4f& modelMatrix) {
		string path = FileManager::resourcePath + string(filename);
		Assimp::Importer importer;
		const aiScene* scene;

		importer.SetPropertyInteger(AI_CONFIG_PP_LBW_MAX_WEIGHTS, 4);
		scene = importer.ReadFile(path.c_str(), aiProcess_LimitBoneWeights | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
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

		Matrix4f* meshMatrices = new Matrix4f[scene->mNumMeshes];
		FindMeshTransformations(meshMatrices, Matrix4f::Identity(), scene->mRootNode);

		Matrix4f globalInverseTransformation = Matrix4f::Invert(CreateMatrix4f(scene->mRootNode->mTransformation));

		//DrawNodeTree(scene->mRootNode);

		//MESH SECTION
		map<string, unsigned int> boneIndex;
		DynamicRawArray<Matrix4f> boneOffsetMatrices(0);
		Array<MeshPart> parts(meshIds.size());
		uint c = 0;
		for (uint meshIndex : meshIds) {
			InitializePart(parts[c], scene, meshIndex, meshMatrices[c], boneIndex, boneOffsetMatrices, supportsInstancing, useAnimation, modelMatrix);
			c++;
		}

		//ANIMATION SECTION
		DynamicRawArray<Animation> animations(0);
		for (unsigned int i = 0; i < scene->mNumAnimations; i++) {
			animations.AdvanceBy(1);
			InitializeAnimation(&animations[animations.Size() - 1], scene, i, filename, boneOffsetMatrices.Size(), boneIndex, globalInverseTransformation);
		}

		for (Matrix4f& offset : boneOffsetMatrices) {
			offset *= Matrix4f::Invert(meshMatrices[0]);
		}
		Mesh* mesh = renderSystem->CreateMesh(isAnimated ? new Skeleton(RawArray<Matrix4f>(boneOffsetMatrices), RawArray<Animation>(animations)) : nullptr, supportsInstancing, parts);
		boneOffsetMatrices.Delete();
		animations.Delete();
		for (MeshPart& p : parts) {
			delete[] (uint*) p.indices;
		}
		if(isAnimated && useAnimation) *result = new AnimatedModel(mesh, RawArray<const Material*>(parts.Size()), nullptr, 0.0);
		else *result = new Model(mesh, RawArray<const Material*>(parts.Size()));
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

	bool ExternFileManager::ReadFontFile(const char* filename, uint size, Vector2f scale, Texture* inTexture, Font** result) {
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

		GLuint tex;
		GLCall(glActiveTexture(GL_TEXTURE0));
		GLCall(glGenTextures(1, &tex));
		GLCall(glBindTexture(GL_TEXTURE_2D, tex));
		GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0));

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

			GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer));


			c[i].offsetX = (float)x / w;


			x += g->bitmap.width;
		}
		((GL3Texture*)inTexture)->m_width = w;
		((GL3Texture*)inTexture)->m_height = h;
		((GL3Texture*)inTexture)->m_bits = 8u;
		((GL3Texture*)inTexture)->m_tID = tex;

		*result = new Font(c, scale, inTexture);
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
