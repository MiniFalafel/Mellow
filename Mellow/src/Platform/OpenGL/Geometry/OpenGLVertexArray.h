#pragma once

#include "Mellow/Renderer/Geometry/VertexArray.h"

namespace Mellow {

	class OpenGLVertexArray : public VertexArray {

	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void Bind() const override;
		void Unbind() const override;
		
		void AddVertexBuffer(const Ref<VertexBuffer> vbo) override;
		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }

		void SetIndexBuffer(const Ref<IndexBuffer> ebo) override;
		const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_ElementBuffer; }

	private:

		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_ElementBuffer;

		uint32_t m_VaoID;

	};

}
