#pragma once

#include "mwpch.h"
#include "Mellow/Renderer/Geometry/DataType.h"

#include <glad/glad.h>

namespace Mellow {

	uint32_t GetOpenGLType(DataType& type) {
		switch (type) {
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

}
