#pragma once
#include "MoveCommand.h"
#include "State.h"

namespace dae
{
	class TransformComponent;
	class Texture2D;

	class MoveState : public State
	{
	public:
		MoveState(GameObject* pOwner, MoveDirection moveDirection);
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual void Update() override;
		virtual std::string GetType() override;
	private:
		std::shared_ptr<Texture2D> m_pLeftTexture;
		std::shared_ptr<Texture2D> m_pRightTexture;
		std::shared_ptr<Texture2D> m_pUpTexture;
		std::shared_ptr<Texture2D> m_pDownTexture;
		MoveDirection m_MoveDirection;
		TransformComponent* m_pTransformComponent;
		MrPepperComponent* m_pMrPepperComponent;
		const float m_MoveSpeed{ 80.f };
		glm::vec2 m_Movement;
	};
}

