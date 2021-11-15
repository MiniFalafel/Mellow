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
		RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.2, 1.0));

		// Make the ImGuiLayer
		m_ImGuiLayer = ImGuiLayer::Create();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application() {
		// Shutdown the renderer
		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MW_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(MW_BIND_EVENT_FN(Application::OnWindowResize));

		for (std::vector<Layer*>::reverse_iterator it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++) {
			(*it)->OnEvent(e);
			if (e.IsHandled()) {
				break;
			}
		}
	}

	void Application::Run() {	
		while (m_Running) {

			RenderCommand::Clear();

			float time = GetTime();
			Timestep ts = time - m_PreviousFrameTime;
			m_PreviousFrameTime = time;

			// Update Layers
			if (!m_Minimized) {
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(ts);
			}

			// ImGuiRender
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			// Update the window
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false; return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

}
