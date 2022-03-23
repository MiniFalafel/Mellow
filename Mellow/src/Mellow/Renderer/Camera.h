#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Mellow {

	// I'm debating whether or not I should have separate camera classes for
	// Perspective the difference of projection matrices. We'll see I guess.
	class Camera {

		void UpdateVectors();
		void UpdateRightAndUpVectors(); // For when users set the front vector manually.

	public:
		//Camera();
		//~Camera();

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetRotation() const { return m_Rotation; }
		void SetPosition(const glm::vec3& position) { m_Position = position; UpdateViewMatrix(); }
		void AddToPosition(const glm::vec3& offset) { m_Position += offset; UpdateViewMatrix(); }
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; UpdateViewMatrix(); }
		void AddToRotation(const glm::vec3& offset) { m_Rotation += offset; UpdateViewMatrix(); }

		void SetFrontVector(const glm::vec3& frontDir) { m_Front = frontDir; UpdateRightAndUpVectors(); }

		const glm::vec3& GetFrontVector() const { return m_Front; }
		const glm::vec3& GetRightVector() const { return m_Right; }
		const glm::vec3& GetUpVector() const { return m_Up; }

		const float& GetFOV() { return m_FOV; }

		void UpdateViewMatrix();
		void UpdateProjectionMatrixPerspective(float FOV, float aspectRatio);
		void UpdateProjectionMatrixOrthographic(float left, float right, float bottom, float top);

		const glm::mat4& GetProjectionMatrixPerspective() const { return m_ProjectionMatrixPerspective; }
		const glm::mat4& GetProjectionMatrixOrthographic() const { return m_ProjectionMatrixOrthographic; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionViewMatrixPerspective() const { return m_ProjectionMatrixPerspective * m_ViewMatrix; }
		const glm::mat4& GetProjectionViewMatrixOrthographic() const { return m_ProjectionMatrixOrthographic * m_ViewMatrix; }

	private:

		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);

		glm::vec3 m_Front, m_Right, m_Up;

		// m_FOV won't be used if the camera is orthographic, but it doesn't matter because we will only
		// have a couple of cameras at a maximum and one float is only 4 bytes. Not a huge sacrifice.
		float m_FOV = 45.0f;

		glm::mat4 m_ProjectionMatrixPerspective;
		glm::mat4 m_ProjectionMatrixOrthographic;
		glm::mat4 m_ViewMatrix;

	};

}