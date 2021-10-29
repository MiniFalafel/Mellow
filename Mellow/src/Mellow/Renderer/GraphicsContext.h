#pragma once

namespace Mellow {
	
	class GraphicsContext {

	public:
		// This will be a wrapper for whatever graphics API we're using
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

	};

}