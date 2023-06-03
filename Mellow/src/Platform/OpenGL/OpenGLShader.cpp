#include "mwpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Mellow {

	static GLenum ShaderTypeFromString(const std::string typeName) {
		if (typeName == "vertex")
			return GL_VERTEX_SHADER;
		else if (typeName == "fragment" || typeName == "pixel")
			return GL_FRAGMENT_SHADER;
		else if (typeName == "geometry")
			return GL_GEOMETRY_SHADER;

		MW_CORE_ASSERT(false, "Unknown shader type!:\n    " + typeName);
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& geometrySrc = nullptr) : m_Name(name) {
		MW_PROFILE_FUNCTION();

		SetupShaders({
			{GL_VERTEX_SHADER, vertexSrc},
			{GL_FRAGMENT_SHADER, fragmentSrc},
		});
	}

	OpenGLShader::OpenGLShader(const std::string& filePath) {
		MW_PROFILE_FUNCTION();

		std::string source = ReadFile(filePath);
		auto shaderSources = Process(source);
		SetupShaders(shaderSources);

		auto lastSlash = filePath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filePath.rfind(".");
		auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filePath.substr(lastSlash, count);
	}

	OpenGLShader::~OpenGLShader() {
		MW_PROFILE_FUNCTION();
		
		glDeleteProgram(m_ProgramID);

	}

	void OpenGLShader::Use() const {
		MW_PROFILE_FUNCTION();

		glUseProgram(m_ProgramID);
	}

	void OpenGLShader::Unuse() const {
		MW_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, const int& value) const {
		MW_PROFILE_FUNCTION();

		glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
	}

	void OpenGLShader::SetBool(const std::string& name, const bool& value) const {
		MW_PROFILE_FUNCTION();

		glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
	}

	void OpenGLShader::SetFloat(const std::string& name, const float& value) const {
		MW_PROFILE_FUNCTION();

		glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), value);
	}

	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& value) const {
		MW_PROFILE_FUNCTION();

		glUniformMatrix3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value) const {
		MW_PROFILE_FUNCTION();

		glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

	void OpenGLShader::SetVec2(const std::string& name, const glm::vec2& value) const {
		MW_PROFILE_FUNCTION();

		glUniform2fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);
	}

	void OpenGLShader::SetVec3(const std::string& name, const glm::vec3& value) const {
		MW_PROFILE_FUNCTION();

		glUniform3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);

	}

	void OpenGLShader::SetVec4(const std::string& name, const glm::vec4& value) const {
		MW_PROFILE_FUNCTION();

		glUniform4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);

	}

	void OpenGLShader::SetupShaders(const std::unordered_map<GLenum, std::string>& shaderData) {
		MW_PROFILE_FUNCTION();

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
		MW_PROFILE_FUNCTION();

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
		MW_PROFILE_FUNCTION();

		int success;
		char infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
			if (!success) {
				GLint logLength = 0;
				glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logLength);

				glGetShaderInfoLog(ID, logLength, &logLength, &infoLog[0]);

				glDeleteShader(ID);

				MW_CORE_ERROR("{0} shader did not compile successfully: {1}", type, infoLog);
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

	std::string OpenGLShader::ReadFile(const std::string& filePath) {
		MW_PROFILE_FUNCTION();
		
		std::string result;
		std::ifstream in(filePath, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else {
			MW_CORE_ERROR("Could not open file '{0}'", filePath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Process(const std::string source) {
		MW_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> ShaderSources;

		const char* TypeToken = "--";
		size_t TypeTokenLength = strlen(TypeToken);
		size_t Pos = source.find(TypeToken, 0);
		while (Pos != std::string::npos) {
			const size_t eol = source.find_first_of("\r\n", Pos);
			const size_t tmp = !eol;
			MW_CORE_ASSERT(tmp != std::string::npos, "Syntax Error!");
			size_t begin = Pos + TypeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			MW_CORE_ASSERT(ShaderTypeFromString(type), "Shader type not supported!");
			size_t NextLinePos = source.find_first_not_of("\r\n", eol);
			Pos = source.find(TypeToken, NextLinePos);
			ShaderSources[ShaderTypeFromString(type)] = source.substr(NextLinePos, Pos - (NextLinePos == std::string::npos ? source.size() - 1 : NextLinePos));
		}

		return ShaderSources;
	}

}