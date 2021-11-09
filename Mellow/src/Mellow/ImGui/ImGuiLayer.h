#pragma once

#include "mwpch.h"
#include "Mellow/Base/Layer.h"

namespace Mellow {
	
	class ImGuiLayer : public Layer {

	public:

		virtual void Begin() = 0;
		virtual void End() = 0;

		static ImGuiLayer* Create();

	};

}
