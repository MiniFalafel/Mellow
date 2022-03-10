#pragma once

#include "Mellow/Renderer/Texture.h"

#include <glad/glad.h>

namespace Mellow {

	class OpenGLTexture2D : public Texture2D {

	public:
		OpenGLTexture2D(const std::string& filePath);
		OpenGLTexture2D(const uint32_t width, const uint32_t height);
		OpenGLTexture2D(const uint32_t width, const uint32_t height, const glm::vec4& color);
		~OpenGLTexture2D();

		const uint32_t GetWidth() const override { return m_Width; }
		const uint32_t GetHeight() const override { return m_Height; }
		void SetData(void* data, uint32_t size) override;
		const void Bind(uint32_t unit) const override;

	private:
		
		void SetupTextureParams();

		uint32_t m_Width, m_Height;

		GLenum m_InternalFormat;
		GLenum m_Format;

		uint32_t m_TextureID;

	};

}