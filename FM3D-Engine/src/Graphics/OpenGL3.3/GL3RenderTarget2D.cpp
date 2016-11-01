#include <Engine.h>

namespace ENGINE_NAME {

	GL3RenderTarget2D::GL3RenderTarget2D(const Vector2i& size, bool useDepth): RenderTarget2D(size), m_depthBuffer(0) {
		GLCall(glGenFramebuffers(1, &m_frameBuffer));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer));

		GLCall(glGenTextures(1, &m_texture));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

		if (useDepth) {
			GLCall(glGenRenderbuffers(1, &m_depthBuffer));
			GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer));
			GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y));
			GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer));
		}

		GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture, 0));

		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		GLCall(glDrawBuffers(1, DrawBuffers));

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			throw std::exception("Error on creating RenderTarget2D!");
		GLErrorCheck();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GL3RenderTarget2D::ReSize(const Vector2i& size) {
		GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0));

		if (m_depthBuffer != 0) {
			GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer));
			GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y));
			GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
		}
	}

	void GL3RenderTarget2D::PresentOnScreen(const Vector2i& screenSize) {
		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
		GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_frameBuffer));
		glViewport(0, 0, screenSize.x, screenSize.y);

		GLCall(glReadBuffer(GL_COLOR_ATTACHMENT0));
		GLCall(glBlitFramebuffer(0, 0, m_size.x, m_size.y, 0, 0, screenSize.x, screenSize.y, GL_COLOR_BUFFER_BIT, GL_LINEAR));
	}

	void GL3RenderTarget2D::Bind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
		glViewport(0, 0, m_size.x, m_size.y);
	}
}