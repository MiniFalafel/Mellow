#pragma once

#include "Mellow/Renderer/Geometry/Buffer.h"

namespace Mellow {

	// Vertex Buffer
	class OpenGLVertexBuffer : public VertexBuffer {

	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		void SetVertexLayout(VertexLayout& layout) override { m_Layout = layout; }
		const VertexLayout& GetLayout() const override { return m_Layout; }

	private:
		uint32_t m_VboID;
		VertexLayout m_Layout;
	};

	// Index Buffer
	class OpenGLIndexBuffer : public IndexBuffer {

	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		uint32_t GetCount() const override { return m_Count; }

	private:

		uint32_t m_Count;
		uint32_t m_EboID;

	};

}
