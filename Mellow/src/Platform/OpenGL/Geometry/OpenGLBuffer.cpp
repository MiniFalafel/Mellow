#include "mwpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Mellow {

	// -----------------------------------
	// VERTEX Buffer
	// -----------------------------------

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
		MW_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_VboID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		MW_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_VboID);
	}

	void OpenGLVertexBuffer::Bind() const {
		MW_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
	}

	void OpenGLVertexBuffer::Unbind() const {
		MW_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// -----------------------------------
	// INDEX Buffer
	// -----------------------------------

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count) {
		MW_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_EboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		MW_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_EboID);
	}
	
	void OpenGLIndexBuffer::Bind() const {
		MW_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboID);
	}

	void OpenGLIndexBuffer::Unbind() const {
		MW_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}