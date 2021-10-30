#include "mwpch.h"
#include "Layer.h"
#include "LayerStack.h"

namespace Mellow {

	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() {
		// Detach and destroy Layers
		for (Layer* layer : m_Layers) {
			layer->OnDetach();
			delete layer;
		}

	}

	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_InsertionIndex, layer);
		m_InsertionIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		std::vector<Layer*>::iterator it = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertionIndex, layer);
		if (it != m_Layers.end()) {
			layer->OnDetach();
			m_Layers.erase(it);
			m_InsertionIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		std::vector<Layer*>::iterator it = std::find(m_Layers.begin() + m_InsertionIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}
}
