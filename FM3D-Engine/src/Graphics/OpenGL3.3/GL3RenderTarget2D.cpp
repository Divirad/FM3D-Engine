#include <Engine.h>

namespace FM3D {

	GL3RenderTarget2D::GL3RenderTarget2D(const Vector2i& size, bool useDepth): RenderTarget2D(size), m_depthBuffer(0) {
		Create(useDepth);
	}

	GL3RenderTarget2D::~GL3RenderTarget2D() {
		Delete();
	}

	void GL3RenderTarget2D::ReSize(const Vector2i& size) {
		bool useDepth = m_depthBuffer != 0;
		Delete();
		m_size = size;
		Create(useDepth);
	}

	void GL3RenderTarget2D::PresentOnScreen(const Vector2i& screenSize) {
		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
		GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_frameBuffer));
		GLCall(glViewport(0, 0, screenSize.x, screenSize.y));

		GLCall(glReadBuffer(GL_COLOR_ATTACHMENT0));
		GLCall(glBlitFramebuffer(0, 0, m_size.x, m_size.y, 0, 0, screenSize.x, screenSize.y, GL_COLOR_BUFFER_BIT, GL_LINEAR));
	}

	void GL3RenderTarget2D::BindAsTarget() const {
		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_frameBuffer));
		GLCall(glViewport(0, 0, m_size.x, m_size.y));
	}

	void GL3RenderTarget2D::BindAsSource() const {
		GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_frameBuffer));
		GLCall(glViewport(0, 0, m_size.x, m_size.y));
	}

	const Texture* GL3RenderTarget2D::GetTexture() {
		return m_texture;
	}

	std::vector<byte> GL3RenderTarget2D::GetPixelData() {
		std::vector<byte> result(m_size.x * m_size.y * 3);
		m_texture->BindForReading();
		GLCall(glReadPixels(0, 0, m_size.x, m_size.y, GL_RGB, GL_UNSIGNED_BYTE, &result[0]));
		return result;
	}

	void GL3RenderTarget2D::Create(bool useDepth) {
		GLCall(glGenFramebuffers(1, &m_frameBuffer));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer));

		m_texture = new GL3Texture(m_size.x, m_size.y, Texture::NEAREST, Texture::REPEAT, Texture::NONE, (char*)nullptr, 24);

		if (useDepth) {
			GLCall(glGenRenderbuffers(1, &m_depthBuffer));
			GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer));
			GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_size.x, m_size.y));
			GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer));
		}

		GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture->GetID(), 0));

		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		GLCall(glDrawBuffers(1, DrawBuffers));

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			throw std::exception("Error on creating RenderTarget2D!");
		GLErrorCheck();

		std::cout << "Framebuffer: " << m_frameBuffer << " (" << m_texture->GetID() << ", " << m_depthBuffer << ")" << std::endl;

		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void GL3RenderTarget2D::Delete() {
		std::cout << "Del Framebuffer: " << m_frameBuffer << " (" << m_texture->GetID() << ", " << m_depthBuffer << ")" << std::endl;

		GLCall(glDeleteFramebuffers(1, &m_frameBuffer));
		delete m_texture;
		GLCall(glDeleteRenderbuffers(1, &m_depthBuffer)); //silently ignores 0's

		m_texture = nullptr;
		m_depthBuffer = 0;
		m_frameBuffer = 0;
	}
}