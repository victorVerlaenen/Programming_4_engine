#pragma once
#include "GameObject.h"

class Component
{
public:
	virtual ~Component() = default;

	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Render() const = 0;
protected:
	explicit Component(dae::GameObject* pOwner);
	dae::GameObject* GetOwner() const { return m_pOwner; }
private:
	dae::GameObject* m_pOwner;
};