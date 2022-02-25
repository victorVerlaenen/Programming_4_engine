#pragma once
#include "Singleton.h"

class Time final : public dae::Singleton<Time>
{
public:
	void SetDeltaTime(float deltaTime) { m_DeltaTime = deltaTime; }
	float GetDeltaTime() const { return m_DeltaTime; }
	void SetFixedDeltaTime(float fixedDeltaTime) { m_FixedDeltaTime = fixedDeltaTime; }
	float GetFixedDeltaTime() const { return m_FixedDeltaTime; }
private:
	friend class Singleton<Time>;
	Time() = default;

	float m_DeltaTime;
	float m_FixedDeltaTime{.02f};
};

