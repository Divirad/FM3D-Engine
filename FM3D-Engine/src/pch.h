#pragma once

#include <Windows.h>
#include <windowsx.h>

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <memory>
#include <math.h>
#include <vector>
#include <fstream>
#include <comdef.h>
#include <map>
#include <forward_list>
#include <list>
#ifndef __cplusplus_cli
#include <mutex>
#else
namespace std {
	class mutex {
	};
}
#endif
#include <functional>
#include <stack>
#include <unordered_set>
#include <utility>
#include <unordered_map>

#include <smmintrin.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <d3d11.h>
#include <d3dcompiler.h>

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#include <FreeImage.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>