#pragma once

#include <glm/glm.hpp>

namespace Mellow {

	class Shader {

	public:
		virtual ~Shader() = default;

		virtual void Use() const = 0;
		virtual void Unuse() const = 0;

		// Uniforms
		virtual void SetInt(const std::string& name, const int& value) = 0;
		virtual void SetBool(const std::string& name, const bool& value) = 0;
		virtual void SetFloat(const std::string& name, const float& value) = 0;

		virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual void SetVec2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetVec3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetVec4(const std::string& name, const glm::vec4& value) = 0;

		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& geometrySrc);
		static Ref<Shader> Create(const std::string& filePath);

		virtual const std::string& GetName() const = 0;

	};

	class ShaderLibrary {

	public:

		void Add(const std::string& name, Ref<Shader>& shader);
		void Add(Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& name, const std::string& filePath);
		Ref<Shader> Load(const std::string& filePath);

		Ref<Shader>& Get(const std::string& name);

		bool Exists(const std::string& name) const;

	private:

		std::unordered_map<std::string, Ref<Shader>> m_Shaders;

	};

}