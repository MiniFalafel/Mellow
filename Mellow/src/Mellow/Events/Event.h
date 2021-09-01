#pragma once
#include "mwpch.h"

#include "Mellow/Base/Base.h"

namespace Mellow {
	
	enum class EventType {
		None = 0, WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BSHIFT(0),
		EventCategoryInput       = BSHIFT(1),
		EventCategoryKeyboard    = BSHIFT(2),
		EventCategoryMouse       = BSHIFT(3),
		EventCategoryMouseButton = BSHIFT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event {

		friend class EventDispatcher;

	public:

		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); };

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false;

	};

	// Event dispatcher for handling events
	class EventDispatcher {

	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		// Template with the type of event you want to dispatch and the event function
		template<typename T, typename F>
		bool Dispatch(const F& func) {
			// Check whether the stored event's type matches the event of typename T
			if (m_Event.GetEventType() == T::GetStaticType()) {
				// Try and handle the event if the types match
				m_Event.m_Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false; // Return false if the event type didn't match
		}

	private:
		Event& m_Event;

	};

	// Event << operator uses the ToString method of a given event
	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}