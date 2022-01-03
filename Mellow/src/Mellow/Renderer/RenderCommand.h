#pragma once

#include "Mellow/Renderer/RendererAPI.h"

namespace Mellow {
	
	class RenderCommand {

	public:
		inline static void Init() {
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		inline static void SetViewport(const uint32_t x, const uint32_t y, const uint32_t X, const uint32_t Y) { s_RendererAPI->SetViewport(x, y, X, Y); }
		inline static void Clear() { s_RendererAPI->Clear(); }
		inline static void DrawIndexed(Ref<VertexArray> vao) { s_RendererAPI->DrawIndexed(vao); }

	private:

		static RendererAPI* s_RendererAPI;

	};

}
