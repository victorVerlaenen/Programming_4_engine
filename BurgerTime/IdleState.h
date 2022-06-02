#pragma once
#include "State.h"

namespace dae
{
	class Texture2D;

	class IdleState : public State
	{
	public:
		IdleState(GameObject* pOwner);
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual void Update() override;
		virtual std::string GetType() override;
	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}

