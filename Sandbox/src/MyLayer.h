#pragma once

#include <Mellow/Base/Layer.h>
#include <Mellow/Events/KeyEvent.h>

#include <Mellow/Renderer/Shader.h>
#include <Mellow/Renderer/Texture.h>
#include <Mellow/Renderer/Renderer.h>
#include <Mellow/Controllers/CameraController.h>

#include <Mellow/Renderer/Geometry/VertexArray.h>


using namespace Mellow;

class MyLayer : public Layer {

	bool OnMouseMovement(MouseMovedEvent& e);
	bool OnKeyPress(KeyPressedEvent& e);

public:
	MyLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnEvent(Event& e) override;
	void OnUpdate(Timestep ts) override;
	void OnImGuiRender() override;

private:

	CameraController m_CameraController;

	Ref<VertexArray> m_TriangleVAO = VertexArray::Create();
	Ref<Texture2D> m_Texture;

	ShaderLibrary m_ShaderLib;
	glm::vec4 m_UniformColor = glm::vec4(1.0);

	bool m_MouseLocked = false;
	bool m_T = false; // 'T' stands for toggle (in case anyone cares).

};