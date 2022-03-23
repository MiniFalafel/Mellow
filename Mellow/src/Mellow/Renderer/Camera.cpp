#include "mwpch.h"
#include "Camera.h"

namespace Mellow {

	void Camera::UpdateVectors() {
		MW_PROFILE_FUNCTION();

		glm::vec3 front;
		front.x = -glm::sin(glm::radians(m_Rotation.y)) * glm::cos(glm::radians(m_Rotation.z));
		front.y =  glm::sin(glm::radians(m_Rotation.x));
		front.z = -glm::cos(glm::radians(m_Rotation.y)) * glm::cos(glm::radians(m_Rotation.x));
		// Note that we might want to normalize this because there may be roundoff error
		// It's likely extremely negligible, so I'm ignoring it for now (unless it becomes an issue).
		m_Front = front;

		UpdateRightAndUpVectors();
	}

	void Camera::UpdateRightAndUpVectors() {
		m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
	
	void Camera::UpdateViewMatrix() {
		MW_PROFILE_FUNCTION();

		UpdateVectors();
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::UpdateProjectionMatrixPerspective(float FOV, float aspectRatio) {
		MW_PROFILE_FUNCTION();

		UpdateVectors();
		m_ProjectionMatrixPerspective = glm::perspective(FOV, aspectRatio, 0.1f, 100.0f);
	}

	void Camera::UpdateProjectionMatrixOrthographic(float left, float right, float bottom, float top) {
		MW_PROFILE_FUNCTION();
		
		m_ProjectionMatrixOrthographic = glm::ortho(left, right, bottom, top, 0.0f, 100.0f);
	}

}