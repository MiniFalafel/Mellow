#pragma once

namespace Mellow {

	typedef enum class MouseCode : uint16_t {

		Button1 = 0,
		Button2 = 1,
		Button3 = 2,
		Button4 = 3,
		Button5 = 4,
		Button6 = 5,
		Button7 = 6,
		Button8 = 7,

		ButtonLast   = Button8,
		ButtonLeft   = Button1,
		ButtonRight  = Button2,
		ButtonMiddle = Button3

	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode) {
		os << static_cast<int32_t>(mouseCode);
		return os;
	}

}

#define MP_MOUSE_BUTTON_1         ::Mellow::MouseCode::Button1
#define MP_MOUSE_BUTTON_2         ::Mellow::MouseCode::Button2
#define MP_MOUSE_BUTTON_3         ::Mellow::MouseCode::Button3
#define MP_MOUSE_BUTTON_4         ::Mellow::MouseCode::Button4
#define MP_MOUSE_BUTTON_5         ::Mellow::MouseCode::Button5
#define MP_MOUSE_BUTTON_6         ::Mellow::MouseCode::Button6
#define MP_MOUSE_BUTTON_7         ::Mellow::MouseCode::Button7
#define MP_MOUSE_BUTTON_8         ::Mellow::MouseCode::Button8

#define MP_MOUSE_BUTTON_LAST      ::Mellow::MouseCode::ButtonLast
#define MP_MOUSE_BUTTON_LEFT      ::Mellow::MouseCode::ButtonLeft
#define MP_MOUSE_BUTTON_RIGHT     ::Mellow::MouseCode::ButtonRight
#define MP_MOUSE_BUTTON_MIDDLE    ::Mellow::MouseCode::ButtonMiddle