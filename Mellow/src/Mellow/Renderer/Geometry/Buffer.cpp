#include "mwpch.h"
#include "Buffer.h"

#include "Mellow/Renderer/RendererAPI.h"

#include "Platform/OpenGL/Geometry/OpenGLBuffer.h"

namespace Mellow {
	
	// Vertex Buffer
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		MW_PROFILE_FUNCTION();

		switch(RendererAPI::GetAPI()) {
			case RendererAPI::API::None:
				MW_CORE_ASSERT(false, "RendererAPI None is not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		MW_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	// Index Buffer
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		MW_PROFILE_FUNCTION();

		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:
			MW_CORE_ASSERT(false, "RendererAPI None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
		}
		MW_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
