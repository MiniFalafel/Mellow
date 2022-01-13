#include "mwpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Mellow {
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
		MW_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init() {
		MW_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		// Load glad
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MW_CORE_ASSERT(success, "failed to initialize glad!");

		// Log graphics info
		MW_CORE_INFO("OpenGL info:");
		MW_CORE_INFO("    Vendor: {0}", glGetString(GL_VENDOR));
		MW_CORE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
		MW_CORE_INFO("    Version: {0}", glGetString(GL_VERSION));

	#ifdef MW_ENABLE_ASSERTS
			int versionMajor, versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MAJOR_VERSION, &versionMinor);

			MW_CORE_ASSERT(!(versionMajor < 4) && !(versionMinor < 4), "Maple requires an OpenGL version of 4.4 or higher");
	#endif
	}

	void OpenGLContext::SwapBuffers() {
		MW_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}
