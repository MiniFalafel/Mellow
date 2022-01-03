#pragma once

#include <Mellow/Base/Layer.h>
#include <Mellow/Events/Event.h>
#include <Mellow/Events/KeyEvent.h>

#include <Mellow/Base/Input.h>

#include <Mellow/Renderer/Geometry/VertexArray.h>

using namespace Mellow;

class MyLayer : public Layer {

public:
	MyLayer();
	virtual ~MyLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;

private:
	Ref<VertexArray> m_TriangleVAO = VertexArray::Create();

};