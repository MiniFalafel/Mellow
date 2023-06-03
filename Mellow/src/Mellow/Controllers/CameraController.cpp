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

		if (m_Enabled)
		{
			float multiplier = m_Sensitivity * 0.1875f; // 360.0f / 1920.0f = 0.1875f (360 degrees for a full screen movement).

			float dX = (mouseX - m_LastMouseX) * multiplier;
			float dY = (mouseY - m_LastMouseY) * multiplier;

			glm::vec3 rotation = m_Camera->GetRotation();

			rotation.x -= dY;
			// This line will change once we add proper constraints
			rotation.x = glm::min(glm::max(rotation.x, -89.0f), 89.0f);
			rotation.y -= dX;

			m_Camera->SetRotation(rotation);

			m_Camera->UpdateViewMatrix();
		}

		m_LastMouseX = mouseX;
		m_LastMouseY = mouseY;
	}

	void CameraController::BindMovementKey(const char* keyName, KeyCode keyCode)
	{
		// make sure the keyName actually exists.
		for (auto it = m_MovementKeyBinds.begin(); it != m_MovementKeyBinds.end(); it++)
		{
			if (it->first == keyName)
			{
				m_MovementKeyBinds[keyName] = keyCode;
				return;
			}
		}

		// Shouldn't get here unless the keyName doesn't exist
		MW_CORE_ERROR("INVALID KEY BIND NAME!:\n    keyName {0} does not exist in the CameraController keybind list.", keyName);

	}

	void CameraController::CheckInputs() {

		m_MovementDirMultiplier.z = float(Input::IsKeyPressed(m_MovementKeyBinds["Forward"])) - float(Input::IsKeyPressed(m_MovementKeyBinds["Backward"]));
		m_MovementDirMultiplier.x = float(Input::IsKeyPressed(m_MovementKeyBinds["Right"])) - float(Input::IsKeyPressed(m_MovementKeyBinds["Left"]));
		m_MovementDirMultiplier.y = float(Input::IsKeyPressed(m_MovementKeyBinds["Up"])) - float(Input::IsKeyPressed(m_MovementKeyBinds["Down"]));

		glm::normalize(m_MovementDirMultiplier);

	}

	void CameraController::Update(Timestep ts) {
		if (m_Enabled)
		{
			glm::vec3 NetMotion = glm::vec3(0.0f);
			NetMotion += m_Camera->GetFrontVector() * m_MovementDirMultiplier.z;
			NetMotion += m_Camera->GetRightVector() * m_MovementDirMultiplier.x;
			NetMotion += m_Camera->GetUpVector()    * m_MovementDirMultiplier.y;

			m_Camera->AddToPosition(NetMotion * m_MovementSpeed * ts.GetSeconds());

			m_Camera->UpdateViewMatrix();
		}
	}

}