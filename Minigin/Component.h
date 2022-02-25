#pragma once
#include "GameObject.h"

class Component
{
public:
	Component(std::shared_ptr<dae::GameObject> pOwner);
	virtual ~Component() = default;

	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Render() const{};
protected:
	std::weak_ptr<dae::GameObject> m_pOwner;
};