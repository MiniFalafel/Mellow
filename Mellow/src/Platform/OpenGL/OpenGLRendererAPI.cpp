#include "mwpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Mellow {
	
	void OpenGLRendererAPI::Init() {
		MW_PROFILE_FUNCTION();

		// Setup OpenGL stuff
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::SetViewport(const uint32_t x, const uint32_t y, const uint32_t X, const uint32_t Y) {
		glViewport(x, y, X, Y);
	}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOTE: We might want to add some way of clearing the stencil buffer.
	}

	void OpenGLRendererAPI::DrawIndexed(Ref<VertexArray> vao) {
		MW_PROFILE_FUNCTION();

		vao->Bind();
		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}