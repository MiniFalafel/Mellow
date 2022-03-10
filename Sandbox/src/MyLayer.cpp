#include "MyLayer.h"

#include <imgui.h>

MyLayer::MyLayer() : Layer("MyLayer") {}

void MyLayer::OnAttach() {
	// Check to see that OnAttach is called when layers are pushed.
	MW_TRACE("'MyLayer' is being attached!");
	// Make sure that the Render commands work
	RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.12, 1.0));

	// Shader
	m_ShaderLib.Load("res/shaders/example.shader");

	// !! - VERTICES
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

	//m_Texture = Texture2D::Create("res/textures/floor_tiles_06_diff_1k.png");
	m_Texture = Texture2D::Create(512, 512, {1.0f, 0.0f, 1.0f, 1.0f});

}

void MyLayer::OnDetach() {
	// Check to see that OnDetach is called during Application shutdown.
	MW_TRACE("'MyLayer' is being shut down.");
}

void MyLayer::OnUpdate(Timestep ts) {


	Ref<Shader>& shader = m_ShaderLib.Get("example");
	shader->Use();
	m_Texture->Bind(1);
	shader->SetInt("uTexImage", 1);
	shader->SetVec4("uColor", m_UniformColor);
	RenderCommand::DrawIndexed(m_TriangleVAO);
}

void MyLayer::OnImGuiRender() {
	ImGui::Begin("Shader Interaction Window");
	ImGui::ColorPicker4("Uniform Color", &m_UniformColor[0]);
	ImGui::End();
}
