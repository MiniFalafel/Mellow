#pragma once

#include "Mellow/Base/Window.h"
#include <GLFW/glfw3.h>

#ifdef MW_PLATFORM_WINDOWS

namespace Mellow {
	
	class WindowsWindow : public Window {

	public:
		
		WindowsWindow(const WindowProperties& windowProps);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		
		bool IsVsync() const override;
		void SetVsync(bool isVsync) override;

		inline virtual void* GetNativeWindow() const { return m_Window; }

		inline void SetEventCallbackFunction(const EventCallbackFn& callbackFunction) { m_Data.EventCallback = callbackFunction; }

		// Create a window
		static Window* Create(const WindowProperties& windowProps);

	private:
		virtual void Init(const WindowProperties& windowProps);
		virtual void Shutdown();

		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;

			unsigned int Width;
			unsigned int Height;

			bool vSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	};

}

#endif