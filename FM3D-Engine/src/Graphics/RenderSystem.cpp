#include <Engine.h>

namespace ENGINE_NAME {

	RenderSystem* RenderSystem::Create(Renderer renderer) {
		switch (renderer) {
		case OpenGL3_3:
			return new GL3RenderSystem();
		case OpenGL4_5:
			return new GL4RenderSystem();
		default:
			std::cout << "Unknown Renderer!" << std::endl;
			return 0;
		}
	}
}