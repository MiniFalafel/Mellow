#pragma once

#include <Mellow/Base/Layer.h>
#include <Mellow/Events/Event.h>
#include <Mellow/Events/KeyEvent.h>

#include <Mellow/Base/Input.h>

#include <Mellow/Renderer/Geometry/VertexArray.h>
#include <Mellow/Renderer/Shader.h>

using namespace Mellow;

class MyLayer : public Layer {

public:
	MyLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Timestep ts) override;
	void OnImGuiRender() override;

private:
	Ref<VertexArray> m_TriangleVAO = VertexArray::Create();

	ShaderLibrary m_ShaderLib;
	glm::vec3 m_ShaderColor = glm::vec3(1.0f);

};