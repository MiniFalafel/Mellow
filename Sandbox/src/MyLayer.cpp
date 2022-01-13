#include "MyLayer.h"

#include <Mellow/Events/KeyEvent.h>
#include <Mellow/Renderer/Renderer.h>
#include <glm/glm.hpp>

#include <imgui.h>

MyLayer::MyLayer() : Layer("MyLayer") {}

void MyLayer::OnAttach() {
	// Check to see that OnAttach is called when layers are pushed.
	MW_TRACE("'MyLayer' is being attached!");
	// Make sure that the Render commands work
	RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.12, 1.0));

	// Shader
	m_ShaderLib.Load("res/example.shader");

	// !! - VERTICES
	// VAO, VBO testing
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.4f, 0.2f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.4f,
		 0.5f,  0.5f, 0.0f, 0.4f, 0.2f, 0.8f,
		-0.5f,  0.5f, 0.0f, 0.8f, 0.2f, 0.8f,
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};
	
	Ref<VertexBuffer> VBO = VertexBuffer::Create(vertices, sizeof(vertices));
	VBO->SetVertexLayout(VertexLayout({
		{"aPosition", DataType::Vec3},
		{"aColor", DataType::Vec3},
	}));
	m_TriangleVAO->AddVertexBuffer(VBO);

	Ref<IndexBuffer> EBO = IndexBuffer::Create(indices, sizeof(indices));

	m_TriangleVAO->SetIndexBuffer(EBO);
	
}

void MyLayer::OnDetach() {
	// Check to see that OnDetach is called during Application shutdown.
	MW_TRACE("'MyLayer' is being shut down.");
}

void MyLayer::OnUpdate(Timestep ts) {

	Ref<Shader>& shader = m_ShaderLib.Get("example");
	shader->Use();
	shader->SetVec3("uColor", m_ShaderColor);
	RenderCommand::DrawIndexed(m_TriangleVAO);
}

void MyLayer::OnImGuiRender() {
	ImGui::Begin("Test Window");
	ImGui::Text("ImGui stuff exists so that's cool.");
	ImGui::ColorEdit3("Rectangle Color", &m_ShaderColor[0]);
	ImGui::End();
}
