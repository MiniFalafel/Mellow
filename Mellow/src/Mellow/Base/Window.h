#pragma once

#include "mwpch.h"

#include "Mellow/Base/Base.h"
#include "Mellow/Events/Event.h"

namespace Mellow {
	
	struct WindowProperties {
		std::string Title;

		unsigned int Width;
		unsigned int Height;

		// TODO: Make a more clearly defined way of setting these from the Application.
		// For example, there could be an 'ApplicationConfig' struct that stores configuration data
		// about the app, but includes the kind of data you'd find in a WindowProperties struct.
		WindowProperties(std::string title = "Mellow Engine Window", int width = 1280, int height = 720) 
			: Title(title), Width(width), Height(height) {}

	};

	class Window {

	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		// Window Update function
		virtual void OnUpdate() = 0;

		// Getters
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual void SetEventCallbackFunction(const EventCallbackFn& callbackFn) = 0;
		virtual void SetVsync(bool doVSync) = 0;
		virtual bool IsVsync() const = 0;

		static Window* Create(const WindowProperties& windProps = WindowProperties());

	};

}
