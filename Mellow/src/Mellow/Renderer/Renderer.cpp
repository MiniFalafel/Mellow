#include "mwpch.h"
#include "Renderer.h"

#include "Mellow/Renderer/Geometry/VertexArray.h"

namespace Mellow {

	void Renderer::Init() {
		MW_PROFILE_FUNCTION();

		RenderCommand::Init();
	}

	void Renderer::Shutdown() {
		// We'll add profiling here when something is added here
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::SetViewport(0, 0, width, height);
	}

}