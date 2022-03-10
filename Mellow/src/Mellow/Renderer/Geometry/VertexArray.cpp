#include "mwpch.h"
#include "VertexArray.h"

#include "Mellow/Renderer/RendererAPI.h"

#include "Platform/OpenGL/Geometry/OpenGLVertexArray.h"

namespace Mellow {
	
	// Do we even need this? We shouldn't be using vertex arrays for anything other than OpenGL right?
	// It's possible that whatever OpenGL implementations we have could just use OpenGLVertexArrays directly.
	Ref<VertexArray> VertexArray::Create() {
		MW_PROFILE_FUNCTION();

		switch (RendererAPI::GetAPI()) {
			
			case RendererAPI::API::None:
				MW_CORE_ASSERT(false, "RendererAPI None is not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();

		}
		MW_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}