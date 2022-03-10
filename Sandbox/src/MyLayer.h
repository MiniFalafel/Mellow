#pragma once

#include <Mellow/Base/Layer.h>
#include <Mellow/Renderer/Geometry/VertexArray.h>
#include <Mellow/Renderer/Shader.h>
#include <Mellow/Renderer/Renderer.h>
#include <Mellow/Renderer/Texture.h>

using namespace Mellow;

class MyLayer : public Layer {

public:
	MyLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Timestep ts) override;
	void OnImGuiRender() override;

private:

	glm::vec4 m_UniformColor = glm::vec4(1.0);

	Ref<VertexArray> m_TriangleVAO = VertexArray::Create();

	Ref<Texture2D> m_Texture;

	ShaderLibrary m_ShaderLib;

};