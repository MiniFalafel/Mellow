#pragma once

#include "Mellow/Renderer/Shader.h"

using GLenum = uint32_t;

namespace Mellow {

	class OpenGLShader : public Shader {

	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& geometrySrc);
		OpenGLShader(const std::string& filePath);
		~OpenGLShader() override;

		void Use() const override;
		void Unuse() const override;

		// Uniforms
		void SetInt(const std::string& name, const int& value) const override;
		void SetBool(const std::string& name, const bool& value) const override;
		void SetFloat(const std::string& name, const float& value) const override;

		void SetMat3(const std::string& name, const glm::mat3& value) const override;
		void SetMat4(const std::string& name, const glm::mat4& value) const override;
		
		void SetVec2(const std::string& name, const glm::vec2& value) const override;
		void SetVec3(const std::string& name, const glm::vec3& value) const override;
		void SetVec4(const std::string& name, const glm::vec4& value) const override;

		const std::string& GetName() const override { return m_Name; }

	private:

		void SetupShaders(const std::unordered_map<GLenum, std::string>& shaderData);
		uint32_t SetupSingleShader(GLenum type, const std::string& shaderCode);
		void CheckCompileErrors(uint32_t ID, const std::string& type);

		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> Process(const std::string source);

		uint32_t m_ProgramID;

		std::string m_Name;

	};

}
