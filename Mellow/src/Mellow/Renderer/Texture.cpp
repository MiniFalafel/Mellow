#include "mwpch.h"
#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Mellow {
	
	Ref<Texture2D> Texture2D::Create(const std::string& filePath) {
		MW_PROFILE_FUNCTION();

		switch (RendererAPI::GetAPI()) {
			case RendererAPI::API::None:
				MW_CORE_ASSERT(false, "RendererAPI None is not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLTexture2D>(filePath);
		}

		MW_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const uint32_t width, const uint32_t height, const glm::vec4& color) {
		MW_PROFILE_FUNCTION();

		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:
			MW_CORE_ASSERT(false, "RendererAPI None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height, color);
		}

		MW_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}