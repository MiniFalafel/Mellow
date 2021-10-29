#include "mwpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Mellow {
	
	// This will look different when we add other Rendering APIs
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}