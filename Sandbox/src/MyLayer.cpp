#include "MyLayer.h"

#include <Mellow/Events/KeyEvent.h>
#include <imgui.h>

MyLayer::MyLayer() : Layer("MyLayer") {}

void MyLayer::OnEvent(Event& e) {
	EventDispatcher Dispatcher(e);
	Dispatcher.Dispatch<KeyPressedEvent>(MW_BIND_EVENT_FN(MyLayer::OnKeyPressedEvent));
}

void MyLayer::OnAttach() {
	// Check to see that OnAttach is called when layers are pushed.
	MW_TRACE("'MyLayer' is being attached!");
}

void MyLayer::OnDetach() {
	// Check to see that OnDetach is called during Application shutdown.
	MW_TRACE("'MyLayer' is being shut down.");
}

void MyLayer::OnUpdate(Timestep ts) {

}

bool MyLayer::OnKeyPressedEvent(KeyPressedEvent& e) {
	MW_TRACE("A Key Was Pressed: {0}", e.GetKeyCode());
	return true;
}

void MyLayer::OnImGuiRender() {
	ImGui::ShowDemoWindow();
}
