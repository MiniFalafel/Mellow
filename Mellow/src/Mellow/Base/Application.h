#pragma once

#include "Mellow/Events/Event.h"
#include "Mellow/Events/KeyEvent.h"

namespace Mellow {
	
	class Application {

	public:
		Application();
		virtual ~Application();

		void Run();

		inline static Application& Get() { return *s_Instance; }

	private:
		static Application* s_Instance;

	};

	Application* CreateApplication();

}