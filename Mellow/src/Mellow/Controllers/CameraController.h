#pragma once

#include "Mellow/Renderer/Camera.h"
#include "Mellow/Base/Timestep.h"
#include "Mellow/Events/MouseEvent.h"
#include "Mellow/Base/KeyCodes.h"

namespace Mellow {

	// --------------------------
	// --  General Controller  --
	// --------------------------
	class CameraController {

	public:
		CameraController(Ref<Camera> camera, const float& aspectRatio);
		CameraController(const float& aspectRatio,
			const glm::vec3& position = glm::vec3(0.0), const glm::vec3& rotation = glm::vec3(0.0));

		Ref<Camera>& GetCamera() { return m_Camera; }

		void OnMouseMovement(MouseMovedEvent& e);

		// Key binding functions so users can change camera controls.
		// This will likely be much different in the future.
		void BindKeyForward(KeyCode keyCode) { m_KeyForward = keyCode; }
		void BindKeyBackward(KeyCode keyCode) { m_KeyBackward = keyCode; }
		void BindKeyLeft(KeyCode keyCode) { m_KeyLeft = keyCode; }
		void BindKeyRight(KeyCode keyCode) { m_KeyRight = keyCode; }
		void BindKeyUp(KeyCode keyCode) { m_KeyUp = keyCode; }
		void BindKeyDown(KeyCode keyCode) { m_KeyDown = keyCode; }

		void SetMouseSensitivity(const float& sensitivity) { m_RotationSpeed = sensitivity; }

		void CheckInputs();
		void Update(Timestep ts);

	private:

		float m_LastMouseX = 0.0f;
		float m_LastMouseY = 0.0f;
		bool m_FirstMouseMovement = true;

		bool m_Forward = false; bool m_Backward = false;
		bool m_Left = false; bool m_Right = false;
		bool m_Up = false; bool m_Down = false;

		KeyCode m_KeyForward = Key::W;
		KeyCode m_KeyBackward = Key::S;
		KeyCode m_KeyLeft = Key::A;
		KeyCode m_KeyRight = Key::D;
		KeyCode m_KeyUp = Key::Space;
		KeyCode m_KeyDown = Key::LeftControl;

		float m_Zoom = 1.0f;
		float m_MovementSpeed = 1.0f;
		float m_RotationSpeed = 1.0f;

		float m_AspectRatio;

		Ref<Camera> m_Camera;

	};
}