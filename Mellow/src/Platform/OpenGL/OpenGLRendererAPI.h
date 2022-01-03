#pragma once

#include "Mellow/Renderer/RendererAPI.h"

namespace Mellow {
	
	class OpenGLRendererAPI : public RendererAPI {

	public:

		void Init() override;
		void SetClearColor(const glm::vec4& color) override;
		void SetViewport(const uint32_t x, const uint32_t y, const uint32_t X, const uint32_t Y) override;
		void Clear() override;
		void DrawIndexed(Ref<VertexArray> vao) override;

	};

}