#pragma once

#include "Mellow/Renderer/GraphicsContext.h"

// TODO: figure out how to do this better! This is really stupid!
struct GLFWwindow;

namespace Mellow {

	class OpenGLContext : public GraphicsContext {

	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;

	};

}
