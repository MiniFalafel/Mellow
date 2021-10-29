#include "mwpch.h"
#include "Renderer.h"

namespace Mellow {

	void Renderer::Init() {
		RenderCommand::Init();
	}

	void Renderer::Shutdown() {

	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::SetViewport(0, 0, width, height);
	}

}