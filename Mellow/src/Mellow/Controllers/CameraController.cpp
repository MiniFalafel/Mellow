#include "mwpch.h"
#include "CameraController.h"

#include "Mellow/Base/Input.h"

namespace Mellow {

	// --------------------------
	// --  General Controller  --
	// --------------------------

	CameraController::CameraController(Ref<Camera> camera, const float& aspectRatio)
		: m_AspectRatio(aspectRatio), m_Camera(camera) {
		MW_PROFILE_FUNCTION();

		m_Camera->UpdateProjectionMatrixPerspective(m_Camera->GetFOV(), m_AspectRatio);
		m_Camera->UpdateProjectionMatrixOrthographic(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
	}

	CameraController::CameraController(const float& aspectRatio, const glm::vec3& position, const glm::vec3& rotation)
		: m_AspectRatio(aspectRatio), m_Camera(CreateRef<Camera>()) {
		MW_PROFILE_FUNCTION();

		m_Camera->SetPosition(position); m_Camera->SetRotation(rotation);
		m_Camera->UpdateViewMatrix();
		m_Camera->UpdateProjectionMatrixPerspective(m_Camera->GetFOV(), m_AspectRatio);
		m_Camera->UpdateProjectionMatrixOrthographic(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);

	}

	// --       Input       --
	void CameraController::OnMouseMovement(MouseMovedEvent& e) {
		MW_PROFILE_FUNCTION();

		float mouseX = e.GetX();
		float mouseY = e.GetY();

		if (!m_FirstMouseMovement) {

			float dX = mouseX - m_LastMouseX;
			float dY = mouseY - m_LastMouseY;

			glm::vec3 rotation = m_Camera->GetRotation();

			rotation.x -= dY;
			// This line will change once we add proper constraints
			rotation.x = glm::min(glm::max(rotation.x, -89.0f), 89.0f);
			rotation.y -= dX;

			m_Camera->SetRotation(rotation);
		}
		else { m_FirstMouseMovement = false; }

		m_Camera->UpdateViewMatrix();

		m_LastMouseX = mouseX;
		m_LastMouseY = mouseY;
	}

	void CameraController::CheckInputs() {
		m_Forward = Input::IsKeyPressed(m_KeyForward);
		m_Backward = Input::IsKeyPressed(m_KeyBackward);
		m_Left = Input::IsKeyPressed(m_KeyLeft);
		m_Right = Input::IsKeyPressed(m_KeyRight);
		m_Up = Input::IsKeyPressed(m_KeyUp);
		m_Down = Input::IsKeyPressed(m_KeyDown);
	}

	void CameraController::Update(Timestep ts) {
		if (m_Forward) { m_Camera->AddToPosition(m_Camera->GetFrontVector() * ts.GetSeconds()); }
		if (m_Backward) { m_Camera->AddToPosition(-m_Camera->GetFrontVector() * ts.GetSeconds()); }
		if (m_Left) { m_Camera->AddToPosition(-m_Camera->GetRightVector() * ts.GetSeconds()); }
		if (m_Right) { m_Camera->AddToPosition(m_Camera->GetRightVector() * ts.GetSeconds()); }
		if (m_Up) { m_Camera->AddToPosition(m_Camera->GetUpVector() * ts.GetSeconds()); }
		if (m_Down) { m_Camera->AddToPosition(-m_Camera->GetUpVector() * ts.GetSeconds()); }

		m_Camera->UpdateViewMatrix();
	}

}