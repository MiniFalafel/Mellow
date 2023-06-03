#pragma once

#include "Mellow/Renderer/Geometry/DataType.h"

namespace Mellow {

	// -------------------------
	// VERTEX Buffer
	// -------------------------

	struct VertexElement {

		std::string Name;
		DataType Type;
		bool Normalized;
		uint32_t Size;
		uint32_t Offset = 0;

		VertexElement(std::string name, DataType type, bool normalized = false) : Name(name), 
			Type(type), Normalized(normalized), Size(SizeofDataType(type)) {}

		const uint32_t GetCount() const {
			switch (Type) {
				case DataType::None:
					MW_CORE_ASSERT(false, "DataType None is not valid!");
					return 0;
				case DataType::Float:	return 1;
				case DataType::Int:		return 1;
				case DataType::Bool:	return 1;
				case DataType::Vec2:	return 2;
				case DataType::Vec3:	return 3;
				case DataType::Vec4:	return 4;
				case DataType::iVec2:	return 2;
				case DataType::iVec3:	return 3;
				case DataType::iVec4:	return 4;
				case DataType::Mat3:	return 9;
				case DataType::Mat4:	return 16;
			}
			MW_CORE_ASSERT(false, "Unknown DataType!");
			return 0;
		}

	};

	class VertexLayout {

	public:
		
		VertexLayout() {}
		VertexLayout(std::initializer_list<VertexElement> elements) : m_Elements(elements) {
			MW_PROFILE_FUNCTION();

			ProcessElements();
		}

		// Iterators n' stuff
		std::vector<VertexElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<VertexElement>::iterator end() { return m_Elements.end(); }
		std::vector<VertexElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<VertexElement>::const_iterator end() const { return m_Elements.end(); }

		std::vector<VertexElement> GetElements() { return m_Elements; }
		const uint32_t GetStride() const { return m_Stride; }

	private:

		uint32_t m_Stride = 0;

		void ProcessElements() {
			MW_PROFILE_FUNCTION();

			m_Stride = 0;
			for (VertexElement& e : m_Elements) {
				e.Offset = m_Stride;
				m_Stride += e.Size;
			}
		}

		std::vector<VertexElement> m_Elements;

	};

	class VertexBuffer {

	public:
		virtual ~VertexBuffer() = default;

		virtual void SetVertexLayout(VertexLayout& layout) = 0;
		virtual const VertexLayout& GetLayout() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);

	};

	// -------------------------
	// INDEX Buffer
	// -------------------------

	class IndexBuffer {

	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);

	};

}
