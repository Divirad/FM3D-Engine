#include <Engine.h>

namespace FM3D {
	/*
	static uint ReadVal(BYTE* bytes, uint& index, uint bits) {
		uint result = 0;
		for (uint i = 0; bits > 0; bits -= 8, i++) {
			result += pow(256U, i) * static_cast<uint>(bytes[index++]);
		}
		return result;
	}

	Vector4f Color(RGBQUAD& rgb) {
		return Vector4f(
			static_cast<float>(rgb.rgbRed) / 256.0f,
			static_cast<float>(rgb.rgbGreen) / 256.0f,
			static_cast<float>(rgb.rgbBlue) / 256.0f,
			static_cast<float>(rgb.rgbReserved) / 256.0f
		);
	}

	static std::vector<std::vector<float>> LoadHeight(FIBITMAP* dib, float bheight, float maxheight) {
		BYTE* pixels = FreeImage_GetBits(dib);
		uint width = FreeImage_GetWidth(dib);
		uint height = FreeImage_GetHeight(dib);
		uint bits = FreeImage_GetBPP(dib);

		int size = width * height * (bits / 8);
		BYTE* heightbytes = new BYTE[size];
		memcpy(heightbytes, pixels, size);

		float maxval = pow(2U, bits) - 1;

		std::vector<std::vector<float>> result(width, std::vector<float>(height));

		for (uint index = 0, w = 0, h = 0; index < width * height; w++) {
			if (w >= width) {
				w = 0;
				h++;
			}

			result[w][h] = ((static_cast<float>(ReadVal(heightbytes, index, bits)) / maxval) * maxheight) + bheight;
		}

		return result;
	}

	Terrain::Terrain(std::string heightmap, const Texture* colormap, std::vector<Texture*>&& textures, float maxheight, Vector3f pos, float vertexSize) {
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = nullptr;
		fif = FreeImage_GetFileType(heightmap.c_str(), 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(heightmap.c_str());
		if (fif == FIF_UNKNOWN)
			std::cerr << "Could not load heightmap" << std::endl;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, heightmap.c_str());

		uint twidth = FreeImage_GetWidth(dib);
		uint theight = FreeImage_GetHeight(dib);

		if (colormap->GetBits() / 8 != textures.size())
			std::cerr << "Colormap and count of textures does not match!" << std::endl;

		std::vector<std::vector<float>> heights = LoadHeight(dib, pos.y, maxheight);
		Vertices vertices(twidth * theight * 4, Vertices::POSITION | Vertices::TEXCOORD | Vertices::NORMAL);
		std::vector<uint> indices;
		indices.reserve(twidth * theight * 4);
		uint c = 0, xi = 0;
		RGBQUAD colorValue;
		for (float x = pos.x; xi < twidth - 1; x += vertexSize, xi++) {
			uint zi = 0;
			for (float z = pos.z; zi < theight - 1; z += vertexSize, zi++) {
				vertices.GetPosition(c + 0) = Vector3f(x, heights[xi][zi], z);
				//vertices.GetNormal(c + 0) = ;
				vertices.GetTexCoord(c + 0) = Vector2f(0.0f, 0.0f);

				vertices.GetPosition(c + 1) = Vector3f(x, heights[xi][zi + 1], z + vertexSize);
				//vertices.GetNormal(c + 1) = ;
				vertices.GetTexCoord(c + 1) = Vector2f(0.0f, 1.0f);

				vertices.GetPosition(c + 2) = Vector3f(x + vertexSize, heights[xi + 1][zi + 1], z + vertexSize);
				//vertices.GetNormal(c + 2) = ;
				vertices.GetTexCoord(c + 2) = Vector2f(1.0f, 1.0f);

				vertices.GetPosition(c + 3) = Vector3f(x + vertexSize, heights[xi + 1][zi], z);
				//vertices.GetNormal(c + 3) = ;
				vertices.GetTexCoord(c + 3) = Vector2f(1.0f, 0.0f);

				indices.push_back(c + 0);
				indices.push_back(c + 1);
				indices.push_back(c + 2);
				indices.push_back(c + 2);
				indices.push_back(c + 3);
				indices.push_back(c + 0);
			}
		}

		FreeImage_Unload(dib);
	}
	*/


	Terrain::Terrain(const Mesh* mesh, const Texture* spatmap, const Texture* normalmap, std::vector<std::pair<Texture*, float>>&& materials, float texCount):
	m_position(Vector3f::Zero()), m_rotation(Vector3f::Zero()), m_scale(Vector3f(1.0f, 1.0f, 1.0f)),
	m_mesh(mesh), m_spatmap(spatmap), m_normalmap(normalmap), m_materials(materials), m_texCount(texCount) {
		if (spatmap->GetHeight() != normalmap->GetHeight() || spatmap->GetWidth() != normalmap->GetWidth()) {
			std::cerr << "Terrain Error: Spatmap and Normalmap does not have the same resolution!" << std::endl;
		}
		if (spatmap->GetBits() != 24) {
			std::cerr << "Terrain Error: Spatmap is not a RGB Texture!" << std::endl;
		}
	}

}