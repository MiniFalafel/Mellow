#include "mwpch.h"

#include "WindowsWindow.h"

#include "Mellow/Events/ApplicationEvent.h"
#include "Mellow/Events/MouseEvent.h"
#include "Mellow/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Mellow {

	static int s_GLFWWindowCount = 0;

	static void glfwErrorCallback(int error, const char* description) {
		MW_CORE_ERROR("GLFW_ERROR ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProperties& windowProps)
	{
		return new WindowsWindow(windowProps);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& windowProps) {
		MW_PROFILE_FUNCTION();

		Init(windowProps);
	}
	WindowsWindow::~WindowsWindow() {
		MW_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& windowProps) {
		MW_PROFILE_FUNCTION();

		m_Data.Title = windowProps.Title;
		m_Data.Width = windowProps.Width;
		m_Data.Height = windowProps.Height;

		MW_CORE_INFO("Creating GLFW Window: {0} {1} {2}", m_Data.Title, m_Data.Width, m_Data.Height);

		// Initialize GLFW (only if it hasn't been initialized yet!)
		if (s_GLFWWindowCount == 0) {
			int success = glfwInit();
			// Assert window success
			MW_CORE_ASSERT(success, "GLFW failed to initialize!");
			glfwSetErrorCallback(glfwErrorCallback);
		}

		// Create Window
		{
			MW_PROFILE_SCOPE("Create GLFW Window");
			m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
			s_GLFWWindowCount += 1;
		}

		// Setup the Graphics Context
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVsync(m_Data.vSync);

		// Set GLFW callback functions
		{
			MW_PROFILE_SCOPE("Set GLFW Callbacks");
			glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				WindowCloseEvent e;
				data.EventCallback(e);

			});
			glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				WindowResizeEvent e(width, height);
				data.Width = width; data.Height = height;
				data.EventCallback(e);

			});
			glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent e(key, 0);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent e(key);
					data.EventCallback(e);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent e(key, 1);
					data.EventCallback(e);
					break;
				}
				}

			});
			glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int c) {
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				KeyTypedEvent e(c);
				data.EventCallback(e);
			});
			glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent e(button);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
					MouseButtonReleasedEvent e(button);
					data.EventCallback(e);
					break;
				}
			});
			glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				MouseMovedEvent e((float)x, (float)y);
				data.EventCallback(e);
			});
			glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y) {
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				MouseScrolledEvent e((float)x, (float)y);
				data.EventCallback(e);
			});
		}

	}

	void WindowsWindow::Shutdown() {
		MW_PROFILE_FUNCTION();

		// We should probably destroy the GLFW window
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		MW_PROFILE_FUNCTION();

		// Poll for GLFW events
		glfwPollEvents();
		m_Context->SwapBuffers();
;	}

	void WindowsWindow::SetVsync(bool isVsync) {
		MW_PROFILE_FUNCTION();
		
		if (isVsync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.vSync = isVsync;
	}

	bool WindowsWindow::IsVsync() const  {
		return m_Data.vSync;
	}
}