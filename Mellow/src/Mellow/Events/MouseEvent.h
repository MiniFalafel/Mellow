#pragma once

#include "Mellow/Events/Event.h"
#include "Mellow/Base/MouseCodes.h"

namespace Mellow {
	
	class MouseButtonEvent : public Event {
		
	public:
		inline MouseCode GetMouseCode() { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

	protected:
		MouseButtonEvent(MouseCode button) : m_Button(button) {}

		MouseCode m_Button;

	};

	class MouseButtonPressedEvent : public MouseButtonEvent {

	public:
		MouseButtonPressedEvent(MouseCode button) : MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {

	public:
		MouseButtonReleasedEvent(MouseCode button) : MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

	};

	class MouseMovedEvent : public Event {

	public:
		MouseMovedEvent(float xPosition, float yPosition) : m_MouseX(xPosition), m_MouseY(yPosition) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
		EVENT_CLASS_TYPE(MouseMoved)

	private:
		float m_MouseX; float m_MouseY;

	};

	class MouseScrolledEvent : public Event {

	public:
		MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
		EVENT_CLASS_TYPE(MouseScrolled)

	private:
		float m_XOffset; float m_YOffset;

	};
}