#include "mwpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Mellow {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath) {
		MW_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		{
			MW_PROFILE_SCOPE("stbi_load OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
			data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
		}
		MW_CORE_ASSERT(data, "Texture failed to load!");
		m_Width = width; m_Height = height;

		GLenum format = 0, internalFormat = 0;
		if (channels == STBI_grey) {
			format = GL_RED;
			internalFormat = GL_RED;
		}
		else if (channels == STBI_grey_alpha) {
			format = GL_RG;
			internalFormat = GL_RG8;
		}
		else if (channels == STBI_rgb) {
			format = GL_RGB;
			internalFormat = GL_RGB8;
		}
		else if (channels == STBI_rgb_alpha) {
			format = GL_RGBA;
			internalFormat = GL_RGBA8;
		}
		MW_CORE_ASSERT(internalFormat & format, "Image format not supported!");
		m_Format = format;
		m_InternalFormat = internalFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, internalFormat, m_Width, m_Height);

		SetupTextureParams();

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(const uint32_t width, const uint32_t height) : m_Width(width), m_Height(height) {
		MW_PROFILE_FUNCTION();

		m_Format = GL_RGBA8;
		m_InternalFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);

		SetupTextureParams();
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		MW_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_TextureID);
	}

	OpenGLTexture2D::OpenGLTexture2D(const uint32_t width, const uint32_t height, const glm::vec4& color) : m_Width(width), m_Height(height) {
		MW_PROFILE_FUNCTION();

		// We have 4 channels
		unsigned char* data = new unsigned char[4 * m_Width * m_Height * sizeof(unsigned char)];
		// We're just multiplying width and height instead of two loops because all pixels will be the same color
		// That is, nothing is dependent on its x, y coordinates.
		for (uint32_t i = 0; i < m_Width * m_Height; i++) {
			for (uint32_t c = 0; c < 4; c++) { // Ahahahahaahahha... c++ (super funny, I know).
				data[i * 4 + c] = unsigned char(int(color[c] * 255.0f));
			}
		}
		MW_CORE_ASSERT(data, "Texture data creation failed!");
		m_Width = width; m_Height = height;

		m_Format = GL_RGBA;
		m_InternalFormat = GL_RGBA8;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);

		SetupTextureParams();

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_Format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

	}

	const void OpenGLTexture2D::Bind(uint32_t unit) const {
		MW_PROFILE_FUNCTION();

		glBindTextureUnit(unit, m_TextureID);
	}

	void OpenGLTexture2D::SetupTextureParams() {
		MW_PROFILE_FUNCTION();

		// TODO: Make texture parameters customizable
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size) {
		MW_PROFILE_FUNCTION();

		MW_CORE_ASSERT(data, "No data was provided!");

		uint32_t bytesPerPixel = m_Format == GL_RGBA ? 4 : m_Format == GL_RGB ? 3 : m_Format == GL_RG ? 2 : 1;
		bytesPerPixel *= sizeof(unsigned char);
		MW_CORE_ASSERT(m_Width * m_Height * bytesPerPixel == size, "Texture data size is different than parameter 'size'!");

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_Format, GL_UNSIGNED_BYTE, data);
	}

}