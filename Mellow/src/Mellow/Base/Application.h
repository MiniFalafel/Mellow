#pragma once

#include "Mellow/Base/Base.h"
#include "Mellow/Base/Window.h"
#include "Mellow/Renderer/GraphicsContext.h"

#include "Mellow/Events/Event.h"
#include "Mellow/Events/ApplicationEvent.h"

#include "Mellow/Base/LayerStack.h"
#include "Mellow/ImGui/ImGuiLayer.h"

// NOTE: This is only here for the 'glfwGetTime()' function
#include <GLFW/glfw3.h>

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

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_PreviousFrameTime = 0.0f;

		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		static Application* s_Instance;

	private:

		// Callbacks
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		// TODO: We should have some sort of platform agnostic way of doing this.
		float GetTime() { return (float)glfwGetTime(); }

	};

	Application* CreateApplication();

}