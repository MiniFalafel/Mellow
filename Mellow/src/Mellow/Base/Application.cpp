#include "mwpch.h"
#include "Application.h"

#include "Mellow/Base/Log.h"

#include "Mellow/Events/ApplicationEvent.h"
#include "Mellow/Events/MouseEvent.h"
#include "Mellow/Events/KeyEvent.h"

namespace Mellow {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		MW_CORE_INFO("Application Starting.");
	}

	Application::~Application() {}

	void Application::Run()
	{
		
		KeyPressedEvent e(MW_KEY_A, 0);
		MW_CORE_TRACE(e);
		
		while (true) {
			// Nothing
		}
	}
}
