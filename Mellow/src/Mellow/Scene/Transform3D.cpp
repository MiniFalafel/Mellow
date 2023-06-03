#include "mwpch.h"

#include "Transform3D.h"

namespace Mellow
{
	
	glm::mat4 Transform3D::GetModelMatrix() const
	{
		MW_PROFILE_FUNCTION();

		glm::mat4 mat = glm::mat4(1.0f);

		mat = glm::translate(mat, Position);
		mat = glm::rotate(mat, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		mat = glm::rotate(mat, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::rotate(mat, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		mat = glm::scale(mat, Scale);

		return mat;
	}

}
