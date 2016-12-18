#include "InternOpengl.h"
#include "pch.h"

#ifdef _DEBUG
#define _GLErrorCheck(x) {\
				     GLenum GLCall_error = glGetError();\
				     if (GLCall_error != GL_NO_ERROR) {\
						std::stringstream str;\
						str << "[OpenGL Error] (" << GLCall_error << ": " << gluErrorString(GLCall_error) << "): " << #x << " " << __FILE__ << ":" << __LINE__ << std::endl;\
						std::cerr << str.str();\
						System::Console::WriteLine(gcnew System::String(str.str().c_str()));\
				  		__debugbreak();\
				     }\
					 }
#endif

#ifdef _DEBUG
#define GLCall(x) x;\
				  _GLErrorCheck(x);
#define GLErrorCheck() _GLErrorCheck(0)
#else
#define GLCall(x) x;
#define GLErrorCheck()
#endif

namespace DesignerLib {

	InternOpenGL::InternOpenGL(HINSTANCE hInst) : m_context(hInst) {

	}

	InternOpenGL::~InternOpenGL() {
		GLCall(glDeleteFramebuffers(1, &m_fbo));
		GLCall(glDeleteRenderbuffers(1, &m_renderBuffer));
	}

	void InternOpenGL::Initialize(double width, double height) {
		m_width = width;
		m_height = height;

		if (!m_context.Initialize()) {
			MessageBoxA(NULL, "OpenGL Context failed to start!", "Error in DesignerLib", MB_OK);
			throw std::runtime_error("OpenGL Context failed to start!");
		}

		GLCall(glGenFramebuffers(1, &m_fbo));
		GLCall(glGenRenderbuffers(1, &m_renderBuffer));
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer));
		GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height));
		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo));
		GLCall(glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderBuffer));
	}

	void InternOpenGL::ChangeSize(System::Windows::Size^ size) {
		m_width = static_cast<uint>(size->Width);
		m_height = static_cast<uint>(size->Height);

		GLCall(glDeleteFramebuffers(1, &m_fbo));
		GLCall(glDeleteRenderbuffers(1, &m_renderBuffer));
		
		GLCall(glGenFramebuffers(1, &m_fbo));
		GLCall(glGenRenderbuffers(1, &m_renderBuffer));
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer));
		GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, m_width, m_height));
		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo));
		GLCall(glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderBuffer));
	}

	void InternOpenGL::Render(System::Windows::Controls::Image^ image) {
		GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo));

		std::vector<std::uint8_t> data(m_width * m_height * 4);
		GLCall(glReadBuffer(GL_COLOR_ATTACHMENT0));
		GLCall(glReadPixels(0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]));

		GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));
	}

	void InternOpenGL::Update() {
		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		//TODO: Render something

		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
	}
}