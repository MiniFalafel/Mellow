#include <Mellow.h>
#include <Mellow/Base/EntryPoint.h>

class Sandbox : public Mellow::Application {

public:

	Sandbox() {
		// Nothing yet (need to implement layers)
	}

	~Sandbox() {
		
	}

};

Mellow::Application* Mellow::CreateApplication() {
	return new Sandbox();
}
