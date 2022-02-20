#pragma once
#include "GameObject.h"

class Component
{
public:
	Component(dae::GameObject* pOwner);
	virtual ~Component() = default;

	virtual void Update(float deltaTime) = 0;
protected:
	dae::GameObject* m_pOwner;
};