#include "mwpch.h"
#include "Application.h"

namespace Mellow {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true) {
			std::cout << "Running" << "\n";
		}
	}
}
