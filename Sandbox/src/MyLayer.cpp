#include "MyLayer.h"

#include <Mellow/Base/Input.h>
#include <Mellow/Scene/Object3D.h>

#include <imgui.h>

MyLayer::MyLayer() : Layer("MyLayer"), m_CameraController(1280.0f / 720.0f, glm::vec3(0.0f, 0.0f, 2.0f)) {}

void CameraToggleCallback(void* params)
{
	CameraToggleCallbackParams* stateInfo = (CameraToggleCallbackParams*)params;

	if (stateInfo->CurrentToggleState)
	{
		Mellow::Input::SetMouseDisabled();
		return;
	}
	Mellow::Input::SetMouseNormal();
}

void MyLayer::OnAttach() {
	// Check to see that OnAttach is called when layers are pushed.
	MW_TRACE("'MyLayer' is being attached!");
	// Make sure that the Render commands work
	RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.12, 1.0));

	// Shader
	m_ShaderLib.Load("res/shaders/cool lighting n appropriate words.shader");
	// Texture
	m_Texture = Texture2D::Create("res/textures/awesomeface.png");
	//m_Texture = Texture2D::Create(512, 512, {1.0f, 1.0f, 1.0f, 1.0f});

	// Mesh
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 0.0,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 0.0,
		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 1.0,
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 1.0,
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};
	m_Mesh = CreateRef<Mesh>("quad", vertices, sizeof(vertices), indices, sizeof(indices), VertexLayout({
		{"aPosition", DataType::Vec3},
		{"aNormal", DataType::Vec3},
		{"aTexCoord", DataType::Vec2},
	}));

	Ref<Mesh> otherMesh = CreateRef<Mesh>("smallquad", vertices, sizeof(vertices), indices, sizeof(indices), VertexLayout({
		{"aPosition", DataType::Vec3},
		{"aNormal", DataType::Vec3},
		{"aTexCoord", DataType::Vec2},
	}));

	otherMesh->SetTransform(
	{
		glm::vec3(0.0f, 0.0f, 0.5f),
		glm::vec3(0.0f),
		glm::vec3(0.25f),
	});

	// Model
	m_Model = CreateRef<Model>();
	m_Model->AddMesh(m_Mesh);
	m_Model->AddMesh(otherMesh);

	m_CameraController.SetMouseSensitivity(0.7f);
	m_CameraController.BindActiveStateCallback(CameraToggleCallback);
	m_CameraController.SetActiveStateCallbackParameterPtr(&m_CamToggleParams);
	m_CameraController.SetActiveState(m_CamToggleParams.CurrentToggleState);

	// Test Custom Attribute Thing
	Mellow::Object3D::CustomAttributeList list;
	list.AddAttribute("coolAttribute", 69);
	list.AddAttribute("sickAttribute", "420");
	// retrieve
	const char* woah = list.GetAttribute<const char*>("sickAttribute");

	MW_TRACE("the attribute was {0}", woah);

}

bool MyLayer::OnMouseMovement(MouseMovedEvent& e) {
	m_CameraController.OnMouseMovement(e);

	return false;
}

bool MyLayer::OnKeyPress(KeyPressedEvent& e) {

	if (e.GetKeyCode() == Mellow::Key::Escape)
	{
		m_CamToggleParams.CurrentToggleState = !m_CamToggleParams.CurrentToggleState;
		m_CameraController.SetActiveState(m_CamToggleParams.CurrentToggleState);
	}

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
	m_Time += ts.GetSeconds();

	m_Framerate = 1.0f / ts.GetSeconds();

	m_CameraController.CheckInputs();
	m_CameraController.Update(ts);

	Ref<Shader>& shader = m_ShaderLib.Get("cool lighting n appropriate words");
	shader->Use();
	m_Texture->Bind(1);
	shader->SetInt("uTexImage", 1);
	shader->SetVec4("uColor", m_UniformColor);
	shader->SetVec3("uLightPos", m_LightPosition);
	shader->SetVec3("uLightColor", m_LightColor);
	shader->SetVec3("uCameraPos", m_CameraController.GetCamera()->GetPosition());

	shader->SetMat4("uProjectionMatrix", m_CameraController.GetCamera()->GetProjectionMatrixPerspective());
	shader->SetMat4("uViewMatrix", m_CameraController.GetCamera()->GetViewMatrix());
	shader->SetFloat("uTime", m_Time);

	for (Ref<Mesh> mesh : m_Model->GetMeshList())
	{
		if (mesh->GetEnabledState())
		{
			shader->SetMat4("uModelMatrix", m_Model->GetMeshModelMatrix(mesh->GetName()));
			RenderCommand::DrawIndexed(mesh->GetVAO());
		}
	}
}

void MyLayer::OnImGuiRender()
{
	ImGui::Begin("Uniform Window");
	if (ImGui::BeginTabBar("Shader Tabs I Guess"))
	{
		if (ImGui::BeginTabItem("Object"))
		{
			ImGui::Text("Object Color:");
			ImGui::ColorPicker4("", &m_UniformColor[0]);
			ImGui::Text("Model Editor:");
			ImGui::DragFloat3("Pos", &m_Model->GetTransform().Position[0], 0.016843f);
			ImGui::DragFloat3("Rot", &m_Model->GetTransform().Rotation[0], 0.036843f);
			ImGui::DragFloat3("Scale", &m_Model->GetTransform().Scale[0],  0.016843f);
			ImGui::EndTabItem();
		}
		if(ImGui::BeginTabItem("Lighting"))
		{
			ImGui::Text("Light Position:");
			ImGui::DragFloat3("", &m_LightPosition[0], 0.1f);
			ImGui::Text("Light Color:");
			ImGui::ColorPicker3("", &m_LightColor[0]);
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
}
