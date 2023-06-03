#include "mwpch.h"

#include "Model.h"

namespace Mellow
{
	
	Ref<Mesh> Model::GetMesh(const char* name)
	{
		MW_PROFILE_FUNCTION();

		for (unsigned int i = 0; i < m_Meshes.size(); i++)
		{
			if (m_Meshes[i]->GetName() == name)
				return m_Meshes[i];
		}

		MW_ERROR("MESH \"{0}\" DOES NOT EXIST IN THIS MODEL", name);
	}

	Ref<Mesh> Model::GetMesh(uint32_t index)
	{
		MW_PROFILE_FUNCTION();

		MW_ASSERT(m_Meshes.size() > index, "MODEL INDEX DOES NOT EXIST!");
		return m_Meshes[index];
	}

	void Model::AddMesh(Ref<Mesh> mesh)
	{
		MW_PROFILE_FUNCTION();

		m_Meshes.push_back(mesh);
	}

	glm::mat4 Model::GetMeshModelMatrix(const char* meshName)
	{
		return GetModelMatrix() * GetMesh(meshName)->GetModelMatrix();
	}

	glm::mat4 Model::GetMeshModelMatrixRelative(const char* meshName)
	{
		return GetMesh(meshName)->GetModelMatrix();
	}

}
