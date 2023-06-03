#include "mwpch.h"

#include "Mesh.h"

#include <glm/mat4x4.hpp>

namespace Mellow
{

	Mesh::Mesh(const char* name, float* vertices, uint32_t vertArraySize, uint32_t* indices, uint32_t indexArraySize, VertexLayout& vertLayout)
		: m_Name(name)
	{
		MW_PROFILE_FUNCTION();

		Ref<VertexBuffer> VBO = VertexBuffer::Create(vertices, vertArraySize);
		VBO->SetVertexLayout(vertLayout);
		m_VAO->AddVertexBuffer(VBO);

		Ref<IndexBuffer> EBO = IndexBuffer::Create(indices, indexArraySize);
		m_VAO->SetIndexBuffer(EBO);
	}
	
}
