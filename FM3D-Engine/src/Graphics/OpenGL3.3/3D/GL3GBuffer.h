#include <Engine.h>

namespace FM3D {

	class GL3GBuffer {
	public:

		enum GBUFFER_TEXTURE_TYPE {
			GBUFFER_TEXTURE_TYPE_POSITION,
			GBUFFER_TEXTURE_TYPE_DIFFUSE,
			GBUFFER_TEXTURE_TYPE_NORMAL,
			GBUFFER_NUM_TEXTURES
		};

		GL3GBuffer(unsigned int width, unsigned int height);

		~GL3GBuffer();

		void StartFrame();
		void BindForGeomPass();
		void BindForStencilPass();
		void BindForLightPass();
		void BindForFinalPass();

		void DebugRendering(uint width, uint height);
	private:

		GLuint m_fbo;
		GLuint m_textures[GBUFFER_NUM_TEXTURES];
		GLuint m_depthTexture;
		GLuint m_finalTexture;
	};

}