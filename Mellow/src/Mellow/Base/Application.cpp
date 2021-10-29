#include "mwpch.h"
#include "Application.h"

#include "Mellow/Base/Log.h"

#include "Mellow/Renderer/Renderer.h"

#include "Mellow/Events/ApplicationEvent.h"
#include "Mellow/Events/MouseEvent.h"
#include "Mellow/Events/KeyEvent.h"

namespace Mellow {

	Application* Application::s_Instance = nullptr;

	Application::Application() {

		MW_CORE_ASSERT(!s_Instance, "Application already exists!");
		// Only do this after the assert.
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		// Setup event callbacks
		m_Window->SetEventCallbackFunction(MW_BIND_EVENT_FN(Application::OnEvent));

		// Initialize renderer
		Renderer::Init();
		// Make sure that the Render commands work
		RenderCommand::SetClearColor(glm::vec4(0.2, 0.3, 0.3, 1.0));

	}

	Application::~Application() {
		// Shutdown the renderer
		Renderer::Shutdown();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MW_BIND_EVENT_FN(Application::OnWindowClose));
	}

	void Application::Run() {	
		while (m_Running) {
			// Update the window
			m_Window->OnUpdate();

			RenderCommand::Clear();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false; return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e) {
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

}
