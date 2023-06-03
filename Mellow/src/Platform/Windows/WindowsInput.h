#pragma once

#include "Mellow/Base/Base.h"
#include "Mellow/Base/Input.h"

using KeyCode = uint16_t;
using MouseCode = uint16_t;

namespace Mellow {
	
	class WindowsInput : public Input {

	private:

		bool IsKeyPressedImpl(KeyCode keyCode) override;
		bool IsMouseButtonPressedImpl(MouseCode mouseCode) override;
		std::pair<float, float> GetMousePosImpl() override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
		void SetMouseDisabledImpl() override;
		void SetMouseHiddenImpl() override;
		void SetMouseNormalImpl() override;

	};

}