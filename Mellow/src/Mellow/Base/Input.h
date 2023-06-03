#pragma once

#include "Mellow/Base/KeyCodes.h"
#include "Mellow/Base/MouseCodes.h"

namespace Mellow {
	
	class Input {

	public:
		
		// Get Buttons
		inline static bool IsKeyPressed(KeyCode keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }
		inline static bool IsMouseButtonPressed(MouseCode mouseCode) { return s_Instance->IsMouseButtonPressedImpl(mouseCode); }
		// Get Mouse Pos
		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		// Mouse states
		inline static void SetMouseDisabled() { s_Instance->SetMouseDisabledImpl(); }
		inline static void SetMouseHidden() { s_Instance->SetMouseHiddenImpl(); }
		inline static void SetMouseNormal() { s_Instance->SetMouseNormalImpl(); }

	private:

		virtual bool IsKeyPressedImpl(KeyCode keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode mouseCode) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

		virtual void SetMouseDisabledImpl() = 0;
		virtual void SetMouseHiddenImpl() = 0;
		virtual void SetMouseNormalImpl() = 0;

	private:
		static Input* s_Instance;

	};

}