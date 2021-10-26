#pragma once

#include "Mellow/Base/Base.h"
#include "Mellow/Base/Window.h"

#include "Mellow/Events/Event.h"
#include "Mellow/Events/ApplicationEvent.h"


namespace Mellow {
	
	class Application {

	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);
		void Run();

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:

		// Callbacks
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running;

		static Application* s_Instance;

	};

	Application* CreateApplication();

}