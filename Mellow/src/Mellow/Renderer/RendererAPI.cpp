#include "mwpch.h"
#include "RendererAPI.h"

namespace Mellow {
	
	// This will change eventually to check for the API that we're actually currently using
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

}