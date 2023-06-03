#pragma once

#include "Mellow/Base/Layer.h"
#include "Mellow/Events/MouseEvent.h"
#include "Mellow/Events/KeyEvent.h"

#include "Mellow/Controllers/CameraController.h"

#include "Mellow/Renderer/Geometry/Model.h"
#include "Mellow/Renderer/Texture.h"
#include "Mellow/Renderer/Shader.h"

struct CameraToggleCallbackParams
{
	bool CurrentToggleState;
};

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
	CameraToggleCallbackParams m_CamToggleParams = { true, };

	Ref<Model> m_Model;
	Ref<Mesh> m_Mesh;
	Ref<Texture2D> m_Texture;

	ShaderLibrary m_ShaderLib;
	// Uniforms
	glm::vec4 m_UniformColor = glm::vec4(1.0);
	glm::vec3 m_LightPosition = glm::vec3(0.3f, 0.85f, 1.9f);
	glm::vec3 m_LightColor = glm::vec3(1.0f);

	float m_Time = 0.0f;
	float m_Framerate = 0.0f;

};