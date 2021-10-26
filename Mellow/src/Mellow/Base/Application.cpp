#include "mwpch.h"
#include "Application.h"

#include "Mellow/Base/Log.h"

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

	}

	Application::~Application() {}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MW_BIND_EVENT_FN(Application::OnWindowClose));
	}

	void Application::Run() {	
		while (m_Running) {
			// Update the window
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false; return true;
	}

}
