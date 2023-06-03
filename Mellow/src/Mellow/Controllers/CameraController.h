#pragma once

#include "Mellow/Renderer/Camera.h"
#include "Mellow/Base/Timestep.h"
#include "Mellow/Events/MouseEvent.h"
#include "Mellow/Base/KeyCodes.h"

// placeholder so we don
static void PlaceholderFunc(void* params) {}

namespace Mellow {

	// --------------------------
	// --  General Controller  --
	// --------------------------
	class CameraController {

	public:
		// takes in a pointer to whatever kind of parameters the user wants to use
		typedef void(*ActiveStateCallbackFnPtr)(void*);

		CameraController(Ref<Camera> camera, const float& aspectRatio);
		CameraController(const float& aspectRatio,
			const glm::vec3& position = glm::vec3(0.0), const glm::vec3& rotation = glm::vec3(0.0));

		Ref<Camera>& GetCamera() { return m_Camera; }

		void OnMouseMovement(MouseMovedEvent& e);

		// Key binding functions so users can change camera controls.
		// This will likely be much different in the future.
		void BindMovementKey(const char* keyName, KeyCode keyCode);

		void SetMouseSensitivity(const float& sensitivity) { m_Sensitivity = sensitivity; }
		void SetActiveState(const bool isEnabled) { m_Enabled = isEnabled; m_ActiveStateCallback(m_ASCallbackParameterPtr); }
		void BindActiveStateCallback(ActiveStateCallbackFnPtr callback) { m_ActiveStateCallback = callback; }
		void SetActiveStateCallbackParameterPtr(void* ASCPtr) { m_ASCallbackParameterPtr = ASCPtr; }

		void CheckInputs();
		void Update(Timestep ts);

	private:

		bool m_Enabled = true;

		ActiveStateCallbackFnPtr m_ActiveStateCallback = PlaceholderFunc;
		void* m_ASCallbackParameterPtr = (void*)&m_Enabled; // just so we don't get errors. maybe not super safe... Oh well!

		float m_LastMouseX = 0.0f;
		float m_LastMouseY = 0.0f;

		glm::vec3 m_MovementDirMultiplier = glm::vec3(0.0f);

		std::map<const char*, KeyCode> m_MovementKeyBinds =
		{
			{"Forward", Key::W},
			{"Backward", Key::S},
			{"Left", Key::A},
			{"Right", Key::D},
			{"Up", Key::Space},
			{"Down", Key::LeftControl},
		};

		float m_Zoom = 1.0f;
		float m_MovementSpeed = 1.0f;
		float m_Sensitivity = 1.0f;

		float m_AspectRatio;

		Ref<Camera> m_Camera;

	};
}