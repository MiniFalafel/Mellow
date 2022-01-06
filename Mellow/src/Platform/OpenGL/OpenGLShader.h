#pragma once

#include "Mellow/Renderer/Shader.h"

using GLenum = uint32_t;

namespace Mellow {

	class OpenGLShader : public Shader {

	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		void Use() const override;
		void Unuse() const override;

		// Uniforms
		void SetInt(const std::string& name, const int& value) override;
		void SetBool(const std::string& name, const bool& value) override;
		void SetFloat(const std::string& name, const float& value) override;

		void SetMat3(const std::string& name, const glm::mat3& value) override;
		void SetMat4(const std::string& name, const glm::mat4& value) override;
		
		void SetVec2(const std::string& name, const glm::vec2& value) override;
		void SetVec3(const std::string& name, const glm::vec3& value) override;
		void SetVec4(const std::string& name, const glm::vec4& value) override;

	private:

		void SetupShaders(const std::unordered_map<GLenum, std::string>& shaderData);
		uint32_t SetupSingleShader(GLenum type, const std::string& shaderCode);
		void CheckCompileErrors(uint32_t ID, const std::string& type);

		uint32_t m_ProgramID;

		std::string m_Name;

	};

}
