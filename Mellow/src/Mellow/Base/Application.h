#pragma once

#include "Mellow/Base/Base.h"
#include "Mellow/Base/Window.h"
#include "Mellow/Renderer/GraphicsContext.h"

#include "Mellow/Events/Event.h"
#include "Mellow/Events/ApplicationEvent.h"

#include "Mellow/Base/LayerStack.h"


namespace Mellow {
	
	class Application {

	public:
		Application();
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void OnEvent(Event& e);
		void Run();

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:

		// Callbacks
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		static Application* s_Instance;

	};

	Application* CreateApplication();

}