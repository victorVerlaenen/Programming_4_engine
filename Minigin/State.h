#pragma once
#include "GameObject.h"

namespace dae
{
class State
{
public:
	State(GameObject* pOwner) :m_pOwner(pOwner) {};
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void Update() = 0;
protected:
	GameObject* m_pOwner;
};
}

