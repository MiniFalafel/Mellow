#include "MyLayer.h"

#include <imgui.h>

MyLayer::MyLayer() : Layer("MyLayer"), m_CameraController(1280.0f / 720.0f, glm::vec3(0.0f, 0.0f, 2.0f)) {}

void MyLayer::OnAttach() {
	// Check to see that OnAttach is called when layers are pushed.
	MW_TRACE("'MyLayer' is being attached!");
	// Make sure that the Render commands work
	RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.12, 1.0));

	// Shader
	m_ShaderLib.Load("res/shaders/example.shader");
	// Texture
	m_Texture = Texture2D::Create("res/textures/floor_tiles_06_diff_1k.png");
	//m_Texture = Texture2D::Create(512, 512, {1.0f, 1.0f, 1.0f, 1.0f});

	// VAO, VBO testing
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0, 0.0,
		 0.5f, -0.5f, 0.0f, 1.0, 0.0,
		 0.5f,  0.5f, 0.0f, 1.0, 1.0,
		-0.5f,  0.5f, 0.0f, 0.0, 1.0,
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};
	
	Ref<VertexBuffer> VBO = VertexBuffer::Create(vertices, sizeof(vertices));
	VBO->SetVertexLayout(VertexLayout({
		{"aPosition", DataType::Vec3},
		{"aTexCoord", DataType::Vec2},
	}));
	m_TriangleVAO->AddVertexBuffer(VBO);

	Ref<IndexBuffer> EBO = IndexBuffer::Create(indices, sizeof(indices));

	m_TriangleVAO->SetIndexBuffer(EBO);

	m_CameraController.SetMouseSensitivity(0.25f);

}

bool MyLayer::OnMouseMovement(MouseMovedEvent& e) {
	if (m_MouseLocked)
		m_CameraController.OnMouseMovement(e);

	return false;
}

bool MyLayer::OnKeyPress(KeyPressedEvent& e) {

	if (e.GetKeyCode() == Mellow::Key::Escape)
		m_MouseLocked = !m_MouseLocked;

	if (e.GetKeyCode() == Mellow::Key::T) // Toggle between perspective and orthographic
		// Just thought it would be a little fun to showcase both things that the controller can do.
		m_T = !m_T;

	return true;
}

void MyLayer::OnDetach() {
	// Check to see that OnDetach is called during Application shutdown.
	MW_TRACE("'MyLayer' is being shut down.");
}

void MyLayer::OnEvent(Event& e) {
	EventDispatcher dispatcher(e);
	// Dispatch event callbacks for camera controls
	dispatcher.Dispatch<MouseMovedEvent>(MW_BIND_EVENT_FN(MyLayer::OnMouseMovement));
	dispatcher.Dispatch<KeyPressedEvent>(MW_BIND_EVENT_FN(MyLayer::OnKeyPress));
}

void MyLayer::OnUpdate(Timestep ts) {

	m_CameraController.CheckInputs();
	m_CameraController.Update(ts);

	Ref<Shader>& shader = m_ShaderLib.Get("example");
	shader->Use();
	m_Texture->Bind(1);
	shader->SetInt("uTexImage", 1);
	shader->SetVec4("uColor", m_UniformColor);
	shader->SetMat4("uProjectionMatrix", m_T ? m_CameraController.GetCamera()->GetProjectionMatrixOrthographic() : m_CameraController.GetCamera()->GetProjectionMatrixPerspective());
	shader->SetMat4("uViewMatrix", m_CameraController.GetCamera()->GetViewMatrix());
	RenderCommand::DrawIndexed(m_TriangleVAO);
}

void MyLayer::OnImGuiRender() {
	ImGui::Begin("Shader Interaction Window");
	ImGui::ColorPicker4("Uniform Color", &m_UniformColor[0]);
	ImGui::End();
}
