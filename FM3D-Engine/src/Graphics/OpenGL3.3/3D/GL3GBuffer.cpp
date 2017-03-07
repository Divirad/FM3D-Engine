#include <Engine.h>

namespace FM3D {

	GL3GBuffer::GL3GBuffer(unsigned int width, unsigned int height):
		m_fbo(0), m_textures{ 0, 0, 0 }, m_depthTexture(0),
		m_finalTexture(0), m_width(width), m_height(height) {
		Create();
	}

	GL3GBuffer::~GL3GBuffer() {
		Delete();
	}

	void GL3GBuffer::StartFrame() {
		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo));
		GLCall(glViewport(0, 0, m_width, m_height));
		GLCall(glDrawBuffer(GL_COLOR_ATTACHMENT3));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
	}


	void GL3GBuffer::BindForGeomPass() {
		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo));

		GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0,
			GL_COLOR_ATTACHMENT1,
			GL_COLOR_ATTACHMENT2 };

		GLCall(glDrawBuffers(ARRAY_SIZE_IN_ELEMENTS(DrawBuffers), DrawBuffers));
	}


	void GL3GBuffer::BindForStencilPass() {
		GLCall(glDrawBuffer(GL_NONE));
	}

	void GL3GBuffer::BindForLightPass() {
		GLCall(glDrawBuffer(GL_COLOR_ATTACHMENT3));

		for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_textures); i++) {
			GLCall(glActiveTexture(GL_TEXTURE0 + i));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION + i]));
		}
	}


	void GL3GBuffer::BindForFinalPass() {
		//GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
		GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo));
		GLCall(glReadBuffer(GL_COLOR_ATTACHMENT3));
	}

	void GL3GBuffer::DebugRendering(uint width, uint height) {
		GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo));

		GLCall(glReadBuffer(GL_COLOR_ATTACHMENT0));
		GLCall(glBlitFramebuffer(0, 0, width, height, 0, 0, width / 2, height / 2, GL_COLOR_BUFFER_BIT, GL_LINEAR));

		GLCall(glReadBuffer(GL_COLOR_ATTACHMENT1));
		GLCall(glBlitFramebuffer(0, 0, width, height, 0, height / 2, width / 2, height, GL_COLOR_BUFFER_BIT, GL_LINEAR));

		GLCall(glReadBuffer(GL_COLOR_ATTACHMENT2));
		GLCall(glBlitFramebuffer(0, 0, width, height, width / 2, height / 2, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR));

		GLCall(glReadBuffer(GL_COLOR_ATTACHMENT3));
		GLCall(glBlitFramebuffer(0, 0, width, height, width / 2, 0, width, height / 2, GL_COLOR_BUFFER_BIT, GL_LINEAR));
	}

	bool GL3GBuffer::Resize(uint width, uint height) {
		if (m_width != width || m_height != height) {
			Delete();
			m_width = width;
			m_height = height;
			Create();
			return true;
		}
		return false;
	}

	void GL3GBuffer::Create() {
		GLCall(glGenFramebuffers(1, &m_fbo));
		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo));

		GLCall(glGenTextures(ARRAY_SIZE_IN_ELEMENTS(m_textures), m_textures));

		GLCall(glGenTextures(1, &m_depthTexture));

		GLCall(glGenTextures(1, &m_finalTexture));

		for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_textures); i++) {
			GLCall(glBindTexture(GL_TEXTURE_2D, m_textures[i]));
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, i == GBUFFER_TEXTURE_TYPE_COLOR ? GL_RGBA32F : GL_RGB32F,
				m_width, m_height, 0, i == GBUFFER_TEXTURE_TYPE_COLOR ? GL_RGBA : GL_RGB, GL_FLOAT, NULL));
			GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0));
		}

		GLCall(glBindTexture(GL_TEXTURE_2D, m_depthTexture));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, m_width, m_height, 0, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, NULL));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0));

		GLCall(glBindTexture(GL_TEXTURE_2D, m_finalTexture));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGB, GL_FLOAT, NULL));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, m_finalTexture, 0));

		GLenum Status = GLCall(glCheckFramebufferStatus(GL_FRAMEBUFFER));

		if (Status != GL_FRAMEBUFFER_COMPLETE) {
			printf("FB error, status: 0x%x\n", Status);
			throw std::exception();
		}

		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));

		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

		std::cout << "GBuffer: " << m_fbo << " (" << m_textures[0] << ", " << m_textures[1] << ", " << m_textures[2] << ", " << m_depthTexture << ", " << m_finalTexture << ")" << std::endl;
	}

	void GL3GBuffer::Delete() {
		std::cout << "Del GBuffer: " << m_fbo << " (" << m_textures[0] << ", " << m_textures[1] << ", " << m_textures[2] << ", " << m_depthTexture << ", " << m_finalTexture << ")" << std::endl;


		if (m_fbo != 0) {
			GLCall(glDeleteFramebuffers(1, &m_fbo));
		}

		if (m_textures[0] != 0) {
			GLCall(glDeleteTextures(ARRAY_SIZE_IN_ELEMENTS(m_textures), m_textures));
		}

		if (m_depthTexture != 0) {
			GLCall(glDeleteTextures(1, &m_depthTexture));
		}

		if (m_finalTexture != 0) {
			GLCall(glDeleteTextures(1, &m_finalTexture));
		}
	}
}