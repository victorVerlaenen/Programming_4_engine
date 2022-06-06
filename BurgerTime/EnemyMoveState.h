
#pragma once
#include "MoveCommand.h"
#include "State.h"

namespace dae
{
	class ActorComponent;
	class TransformComponent;
	class Texture2D;

	class EnemyMoveState : public State
	{
	public:
		EnemyMoveState(GameObject* pOwner, MoveDirection moveDirection, float moveSpeed);
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
		ActorComponent* m_pActorComponent;
		const float m_MoveSpeed;
		glm::vec2 m_Movement;
		bool m_MovingDown = false;
	};
}

