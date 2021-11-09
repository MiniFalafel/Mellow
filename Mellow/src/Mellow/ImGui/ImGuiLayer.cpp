#include "mwpch.h"
#include "ImGuiLayer.h"

#include "Mellow/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLImGuiLayer.h"

#include <imgui.h>

namespace Mellow {
	
	ImGuiLayer* ImGuiLayer::Create() {
		switch (RendererAPI::GetAPI()) {
			case (RendererAPI::API::None): return nullptr;
			case (RendererAPI::API::OpenGL): return new OpenGLImGuiLayer();
		}
		MW_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

}