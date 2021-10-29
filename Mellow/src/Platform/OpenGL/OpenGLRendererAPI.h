#pragma once

#include "Mellow/Renderer/RendererAPI.h"

namespace Mellow {
	
	class OpenGLRendererAPI : public RendererAPI {

	public:

		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetViewport(const uint32_t x, const uint32_t y, const uint32_t X, const uint32_t Y) override;
		virtual void Clear() override;

	};

}