#pragma once

#include "Mellow/Events/Event.h"

namespace Mellow {
	
	class WindowResizeEvent : public Event {
		
	public:
		WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();

		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowResize)

	private:
		int m_Width; int m_Height;

	};

	class WindowCloseEvent : public Event {

	public:
		WindowCloseEvent() {}

		std::string ToString() const override {

			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();

		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowClose)

	};

	class AppTickEvent : public Event {

	public:
		AppTickEvent() {}

		std::string ToString() const override {

			std::stringstream ss;
			ss << "AppTickEvent";
			return ss.str();

		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppTick)

	};

	class AppUpdateEvent : public Event {

	public:
		AppUpdateEvent() {}

		std::string ToString() const override {

			std::stringstream ss;
			ss << "AppUpdateEvent";
			return ss.str();

		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppUpdate)

	};

	class AppRenderEvent : public Event {

	public:
		AppRenderEvent() {}

		std::string ToString() const override {

			std::stringstream ss;
			ss << "AppRenderEvent";
			return ss.str();

		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppRender)

	};

}