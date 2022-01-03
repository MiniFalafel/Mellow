#include "mwpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Mellow {

	OpenGLVertexArray::OpenGLVertexArray() {
		MW_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_VaoID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		MW_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_VaoID);
	}

	void OpenGLVertexArray::Bind() const {
		MW_PROFILE_FUNCTION();

		glBindVertexArray(m_VaoID);
	}

	void OpenGLVertexArray::Unbind() const {
		MW_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	static GLuint GetOpenGLDataType(DataType type) {
		switch (type) {
		case DataType::None:
			MW_CORE_ASSERT(false, "DataType None is not valid!");
			return 0;
		case DataType::Float:	return GL_FLOAT;
		case DataType::Int:		return GL_INT;
		case DataType::Bool:	return GL_BOOL;
		case DataType::Vec2:	return GL_FLOAT;
		case DataType::Vec3:	return GL_FLOAT;
		case DataType::Vec4:	return GL_FLOAT;
		case DataType::iVec2:	return GL_INT;
		case DataType::iVec3:	return GL_INT;
		case DataType::iVec4:	return GL_INT;
		case DataType::Mat3:	return GL_FLOAT;
		case DataType::Mat4:	return GL_FLOAT;
		}
		MW_CORE_ASSERT(false, "Unknown DataType!");
		return 0;
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> vbo) {
		MW_PROFILE_FUNCTION();

		glBindVertexArray(m_VaoID);
		vbo->Bind();

		uint32_t elementIndex = 0;
		const auto& layout = vbo->GetLayout();
		for (const auto& e : layout) {
			glEnableVertexAttribArray(elementIndex);
			glVertexAttribPointer(elementIndex, e.GetCount(), GetOpenGLDataType(e.Type),
				e.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (void*)e.Offset
			);
			elementIndex++;
		}
		m_VertexBuffers.push_back(vbo);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> ebo) {
		MW_PROFILE_FUNCTION();
		
		glBindVertexArray(m_VaoID);
		ebo->Bind();

		m_ElementBuffer = ebo;
	}

}
