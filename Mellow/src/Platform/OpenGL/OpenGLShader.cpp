#include "mwpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Mellow {

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : m_Name(name) {
		SetupShaders({
			{GL_VERTEX_SHADER, vertexSrc},
			{GL_FRAGMENT_SHADER, fragmentSrc},
		});
	}

	OpenGLShader::~OpenGLShader() {

	}

	void OpenGLShader::Use() const {
		glUseProgram(m_ProgramID);
	}

	void OpenGLShader::Unuse() const {
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, const int& value) {
		glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
	}

	void OpenGLShader::SetBool(const std::string& name, const bool& value) {
		glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
	}

	void OpenGLShader::SetFloat(const std::string& name, const float& value) {
		glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), value);
	}

	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& value) {
		glUniformMatrix3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value) {
		glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

	void OpenGLShader::SetVec2(const std::string& name, const glm::vec2& value) {
		glUniform2fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);
	}

	void OpenGLShader::SetVec3(const std::string& name, const glm::vec3& value) {
		glUniform3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);

	}

	void OpenGLShader::SetVec4(const std::string& name, const glm::vec4& value) {
		glUniform4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);

	}

	void OpenGLShader::SetupShaders(const std::unordered_map<GLenum, std::string>& shaderData) {
		m_ProgramID = glCreateProgram();
		
		std::array<GLenum, 3> ShaderIDs;
		uint32_t ShaderIDindex = 0;
		for (auto& pair : shaderData) {
			ShaderIDs[ShaderIDindex++] = SetupSingleShader(pair.first, pair.second);
		}
		glLinkProgram(m_ProgramID);
		CheckCompileErrors(m_ProgramID, "PROGRAM");
		for (auto& ID : ShaderIDs) {
			glDeleteShader(ID);
		}
	}

	uint32_t OpenGLShader::SetupSingleShader(GLenum type, const std::string& shaderCode) {
		uint32_t shader = glCreateShader(type);

		const GLchar* cSrc = shaderCode.c_str();
		glShaderSource(shader, 1, &cSrc, NULL);
		glCompileShader(shader);
		const std::string typeName = type == GL_VERTEX_SHADER ? "VERTEX" : type == GL_FRAGMENT_SHADER ? "FRAGMENT" : "GEOMETRY";
		CheckCompileErrors(shader, typeName);
		glAttachShader(m_ProgramID, shader);

		return shader;
	}

	void OpenGLShader::CheckCompileErrors(uint32_t ID, const std::string& type) {
		int success;
		char infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
			if (!success) {
				GLint logLength = 0;
				glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logLength);

				glGetShaderInfoLog(ID, logLength, &logLength, &infoLog[0]);

				glDeleteShader(ID);

				MW_CORE_ERROR("Shader did not compile successfully: {0}", infoLog);
				MW_CORE_ASSERT(false, "Shader did not compile successfully!");
			}
		}
		else {
			glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
			if (!success) {
				GLint logLength = 0;
				glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &logLength);

				glGetProgramInfoLog(ID, logLength, &logLength, &infoLog[0]);

				glDeleteProgram(ID);

				MW_CORE_ERROR("Program did not link successfully: {0}", infoLog);
				MW_CORE_ASSERT(false, "Program did not link successfully!");
			}
		}
	}

}