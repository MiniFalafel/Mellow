#include "mwpch.h"
#include "Application.h"

#include "Mellow/Base/Log.h"

namespace Mellow {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		MW_CORE_INFO("Hello Logging!!");
		MW_CORE_WARN("This is the warning color.");
		MW_CORE_ERROR("This is the error color.");
	}

	Application::~Application() {
	}

	void Application::Run()
	{
		while (true) {
			MW_CORE_TRACE("GameLoop Frame.");
		}
	}
}
