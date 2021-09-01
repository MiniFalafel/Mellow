#pragma once

#include "Mellow/Events/Event.h"
#include "Mellow/Base/KeyCodes.h"

namespace Mellow {
	
	// Basic overall key event (parent to more specific key-related events).
	class KeyEvent : public Event {

	public:
		inline KeyCode GetKeyCode() { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(KeyCode keyCode) : m_KeyCode(keyCode) {}

		KeyCode m_KeyCode;
	};

	// Key Pressed Event
	class KeyPressedEvent : public KeyEvent {
		int m_RepeatCount;

	public:
		KeyPressedEvent(KeyCode keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << " repeats)"; // Gives Key Code and repeat count if applicable
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};
	// Key Released Event
	class KeyReleasedEvent : public KeyEvent {

	public:
		KeyReleasedEvent(KeyCode keyCode) : KeyEvent(keyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode; // Gives Key Code
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
	// Key Released Event
	class KeyTypedEvent : public KeyEvent {

	public:
		KeyTypedEvent(KeyCode keyCode) : KeyEvent(keyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode; // Gives Key Code
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}