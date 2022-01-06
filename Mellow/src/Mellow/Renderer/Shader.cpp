#include "mwpch.h"
#include "Shader.h"

#include "Mellow/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Mellow {

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
		
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);

		}
	}

}
