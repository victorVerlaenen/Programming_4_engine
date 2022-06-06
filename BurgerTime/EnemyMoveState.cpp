#include "BurgerTimePCH.h"
#include "EnemyMoveState.h"

#include "ResourceManager.h"
#include "ActorComponent.h"
#include "IdleState.h"
#include "SpriteRenderComponent.h"
#include "TransformComponent.h"

dae::EnemyMoveState::EnemyMoveState(GameObject* pOwner, MoveDirection moveDirection, float moveSpeed)
	:State(pOwner)
	, m_pLeftTexture(ResourceManager::GetInstance().LoadTexture("EnemyRunning.png"))
	, m_pRightTexture(ResourceManager::GetInstance().LoadTexture("EnemyRunningRight.png"))
	, m_pUpTexture(ResourceManager::GetInstance().LoadTexture("EnemyClimbing.png"))
	, m_pDownTexture(ResourceManager::GetInstance().LoadTexture("EnemyDecending.png"))
	, m_MoveDirection(moveDirection)
	, m_pTransformComponent(pOwner->GetComponent<TransformComponent>())
	, m_pActorComponent(pOwner->GetComponent<ActorComponent>())
	, m_MoveSpeed(moveSpeed)
{

}


void dae::EnemyMoveState::OnEnter()
{
	switch (m_MoveDirection)
	{
	case MoveDirection::Left:
		if (m_pActorComponent->GetIsGrounded() == true)
		{
			m_pActorComponent->MoveToGround();
			m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pLeftTexture, 1, 2, 3);
			m_Movement = glm::vec2{ -m_MoveSpeed, 0 };
		}
		break;
	case MoveDirection::Right:
		if (m_pActorComponent->GetIsGrounded() == true)
		{
			m_pActorComponent->MoveToGround();
			m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pRightTexture, 1, 2, 3);
			m_Movement = glm::vec2{ m_MoveSpeed , 0 };
		}
		break;
	case MoveDirection::Up:
		if (m_pActorComponent->GetIsOnLadder() == true)
		{
			m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pUpTexture, 1, 2, 3);
			m_Movement = glm::vec2{ 0, -m_MoveSpeed };
		}
		break;
	case MoveDirection::Down:
		if (m_pActorComponent->GetIsOnLadder() == true && m_pActorComponent->GetCantClimbDown() == false)
		{
			m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pDownTexture, 1, 2, 3);
			m_Movement = glm::vec2{ 0, m_MoveSpeed };
			m_MovingDown = true;
		}
		break;
	}
}

void dae::EnemyMoveState::OnExit()
{
}

void dae::EnemyMoveState::Update()
{
	const bool climbDown = m_pActorComponent->GetCantClimbDown();
	if (climbDown == true && m_MovingDown == true)
	{
		m_pActorComponent->SetState(std::make_shared<IdleState>(m_pOwner));
		return;
	}
	m_pTransformComponent->Translate(m_Movement * Clock::GetInstance().GetDeltaTime());
}

std::string dae::EnemyMoveState::GetType()
{
	switch (m_MoveDirection)
	{
	case MoveDirection::Left:
		return "MoveLeft";
	case MoveDirection::Right:
		return "MoveRight";
	case MoveDirection::Up:
		return "MoveUp";
	case MoveDirection::Down:
		return "MoveDown";
	default:
		return"";
	}
}
