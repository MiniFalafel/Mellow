#pragma once
#include "Mellow/ImGui/ImGuiLayer.h"

namespace Mellow {
	
	class OpenGLImGuiLayer : public ImGuiLayer {
		
	public:
		OpenGLImGuiLayer();
		~OpenGLImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		void Begin() override;
		void End() override;

		void OnImGuiRender() override;
	};

}