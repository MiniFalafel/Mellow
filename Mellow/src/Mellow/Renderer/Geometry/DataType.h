#pragma once

#include "mwpch.h"

namespace Mellow {

	enum class DataType : uint16_t {
		None = 0,
		Float, Int, Bool,
		Vec2, Vec3, Vec4,
		iVec2, iVec3, iVec4,
		Mat3, Mat4
	};

	inline uint32_t SizeofDataType(DataType& type) {
		switch (type) {
			case DataType::None:
				MW_CORE_ASSERT(false, "DataType None is not valid!");
				return 0;
			case DataType::Float:	return 4;
			case DataType::Int:		return 4;
			case DataType::Bool:	return 1;
			case DataType::Vec2:	return 8;
			case DataType::Vec3:	return 12;
			case DataType::Vec4:	return 16;
			case DataType::iVec2:	return 8;
			case DataType::iVec3:	return 12;
			case DataType::iVec4:	return 16;
			case DataType::Mat3:	return 36;
			case DataType::Mat4:	return 64;
		}
		MW_CORE_ASSERT(false, "Unknown DataType!");
		return 0;
	}

}