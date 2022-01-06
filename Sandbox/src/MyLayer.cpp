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
	const std::string vertexSrc = "\n"
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"\n"
		"uniform float uScale;\n"
		"\n"
		"void main() {\n"
		"    \n"
		"    gl_Position = vec4(uScale * aPos, 1.0);\n"
		"    \n"
		"}\n";
	const std::string fragmentSrc = "\n"
		"#version 330 core\n"
		"\n"
		"out vec4 FragColor;\n"
		"\n"
		"uniform vec3 uColor;\n"
		"\n"
		"void main() {\n"
		"    \n"
		"    FragColor = vec4(uColor, 1.0);\n"
		"    \n"
		"}\n";

	m_Shader = Shader::Create("Cool Shader ;)", vertexSrc, fragmentSrc);

	// !! - VERTICES
	// VAO, VBO testing
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};
	
	Ref<VertexBuffer> VBO = VertexBuffer::Create(vertices, sizeof(vertices));
	VBO->SetVertexLayout(VertexLayout({
		{"aPosition", DataType::Vec3},
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

	float mx = Input::GetMouseX();

	m_Shader->Use();
	m_Shader->SetFloat("uScale", mx / 1280.0f);
	m_Shader->SetVec3("uColor", m_ShaderColor);
	RenderCommand::DrawIndexed(m_TriangleVAO);
}

void MyLayer::OnImGuiRender() {
	ImGui::Begin("Test Window");
	ImGui::Text("ImGui stuff exists so that's cool.");
	ImGui::ColorEdit3("Rectangle Color", &m_ShaderColor[0]);
	ImGui::End();
}
