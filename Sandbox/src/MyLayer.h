#pragma once

#include <Mellow/Base/Layer.h>
#include <Mellow/Events/Event.h>
#include <Mellow/Events/KeyEvent.h>

#include <Mellow/Base/Input.h>

using namespace Mellow;

class MyLayer : public Layer {

public:
	MyLayer();
	virtual ~MyLayer() = default;

	virtual void OnEvent(Event& e) override;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;

	bool OnKeyPressedEvent(KeyPressedEvent& e);

};