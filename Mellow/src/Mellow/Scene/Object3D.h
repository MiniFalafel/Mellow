#pragma once

#include "Transform3D.h"

namespace Mellow
{

	class Object3D
	{
		struct ObjectData
		{
			Transform3D Transform;
		};

	private:
		ObjectData m_Data;

	};

}
