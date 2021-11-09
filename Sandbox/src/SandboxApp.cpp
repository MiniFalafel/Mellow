#include <Mellow.h>

#include "MyLayer.h"

class Sandbox : public Mellow::Application {

public:

	Sandbox() {
		PushLayer(new MyLayer()); // Push the example layer
	}

	~Sandbox() {
		
	}

private:

};

Mellow::Application* Mellow::CreateApplication() {
	return new Sandbox();
}
