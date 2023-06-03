#pragma once

#include "VertexArray.h"
#include "Mellow/Scene/Transform3D.h"

namespace Mellow
{

	class Mesh // Just a wrapper for a VAO that has more useful data
	{
	public:
		// Constructors
		Mesh(const char* name, float* vertices, uint32_t vertArraySize, uint32_t* indices, uint32_t indexArraySize, VertexLayout& vertLayout);

		// Getters
		Ref<VertexArray> GetVAO() { return m_VAO; }
		const char* GetName() const { return m_Name; }
		Transform3D GetTransform() const { return m_Transform; }
		glm::mat4 GetModelMatrix() const { return m_Transform.GetModelMatrix(); }
		bool GetEnabledState() { return m_Enabled; }

		// Setters
		void SetTransform(Transform3D transform) { m_Transform = transform; }
		void SetEnabledState(bool state) { m_Enabled = state; }
		void Disable() { m_Enabled = false; }
		void Enable() { m_Enabled = true; }
		bool Toggle() { m_Enabled = !m_Enabled; return m_Enabled; }

	private:
		const char* m_Name;
		Ref<VertexArray> m_VAO = VertexArray::Create(); // This might change later since other APIs don't use VAOs
		Transform3D m_Transform;

		bool m_Enabled = true;

	};

}
