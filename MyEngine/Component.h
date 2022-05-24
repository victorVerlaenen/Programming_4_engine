#pragma once
#include "GameObject.h"

namespace dae
{
	class Component
	{
	public:
		virtual ~Component() = default;

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;
	protected:
		explicit Component(dae::GameObject* pOwner);
		GameObject* GetOwner() const { return m_pOwner; }
	private:
		GameObject* m_pOwner;
	};
}