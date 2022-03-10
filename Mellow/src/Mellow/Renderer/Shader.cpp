#include "mwpch.h"
#include "Shader.h"

#include "Mellow/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Mellow {

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& geometrySrc = nullptr) {
		MW_PROFILE_FUNCTION();

		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				MW_CORE_ASSERT(false, "RendererAPI None is not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc, geometrySrc);
		}
		MW_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& filePath) {
		MW_PROFILE_FUNCTION();

		switch (Renderer::GetAPI()) {
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(filePath);
		}
		MW_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	
	void ShaderLibrary::Add(const std::string& name, Ref<Shader>& shader) {
		MW_PROFILE_FUNCTION();

		MW_CORE_ASSERT(!Exists(name), "Shader with that name already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(Ref<Shader>& shader) {
		Add(shader->GetName(), shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath) {
		MW_PROFILE_FUNCTION();

		Ref<Shader> shader = Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filePath) {
		MW_PROFILE_FUNCTION();

		Ref<Shader> shader = Shader::Create(filePath);
		Add(shader->GetName(), shader);
		return shader;
	}

	Ref<Shader>& ShaderLibrary::Get(const std::string& name) {
		MW_PROFILE_FUNCTION();

		MW_CORE_ASSERT(Exists(name), "Shader does not exist!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const {
		MW_PROFILE_FUNCTION();

		return m_Shaders.find(name) != m_Shaders.end();
	}
}
