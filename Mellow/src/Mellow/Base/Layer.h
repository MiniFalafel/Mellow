#pragma once

#include "Mellow/Base/Base.h"
#include "Mellow/Base/Timestep.h"
#include "Mellow/Events/Event.h"

namespace Mellow {
	
	class Layer {

	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& e) {}

	private:

		std::string m_DebugName;

	};

}
