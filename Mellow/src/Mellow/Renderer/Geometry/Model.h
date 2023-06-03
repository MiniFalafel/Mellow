#pragma once

#include "Mesh.h"

namespace Mellow
{
	
	class Model
	{

	public:
		Model() {}

		// Getters
		Ref<Mesh> GetMesh(const char* name);
		Ref<Mesh> GetMesh(uint32_t index);
		std::vector<Ref<Mesh>> GetMeshList() { return m_Meshes; }

		glm::mat4 GetModelMatrix() const { return m_Transform.GetModelMatrix(); }
		Transform3D& GetTransform() { return m_Transform; }
		glm::mat4 GetMeshModelMatrix(const char* meshName); // model matrix in world space
		glm::mat4 GetMeshModelMatrixRelative(const char* meshName); // model matrix relative to the model's model matrix

		// Setters
		void AddMesh(Ref<Mesh> mesh);

	private:
		std::vector<Ref<Mesh>> m_Meshes;
		Transform3D m_Transform;

	};

}
