#pragma once

namespace Mellow {
	
	class Timestep {

	public:
		Timestep(float dt = 0.0f) : m_DeltaTime(dt) {}

		float GetSeconds() { return m_DeltaTime; }
		float GetMilliseconds() { return m_DeltaTime * 1000.0f; }

		operator float() { return m_DeltaTime; }

	private:
		float m_DeltaTime;

	};

}