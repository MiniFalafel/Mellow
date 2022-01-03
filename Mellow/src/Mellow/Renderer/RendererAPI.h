#pragma once

#include "Mellow/Renderer/Geometry/VertexArray.h"

#include <glm/glm.hpp>

namespace Mellow {
	
	class RendererAPI {

	public:

		enum class API {
			None = 0, OpenGL = 1
		};

		virtual void Init() = 0;
		// Render calls
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void SetViewport(const uint32_t x, const uint32_t y, const uint32_t X, const uint32_t Y) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(Ref<VertexArray> vao) = 0;

		inline static API GetAPI() { return s_API; }

	private:

		static API s_API;

	};

}
