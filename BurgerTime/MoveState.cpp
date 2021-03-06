#include "BurgerTimePCH.h"
#include "MoveState.h"

#include "IdleState.h"
#include "MrPepperComponent.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "ActorComponent.h"

dae::MoveState::MoveState(GameObject* pOwner, MoveDirection moveDirection, float moveSpeed)
	:State(pOwner)
	, m_pLeftTexture(ResourceManager::GetInstance().LoadTexture("Running.png"))
	, m_pRightTexture(ResourceManager::GetInstance().LoadTexture("RunningRight.png"))
	, m_pUpTexture(ResourceManager::GetInstance().LoadTexture("Climbing.png"))
	, m_pDownTexture(ResourceManager::GetInstance().LoadTexture("Decending.png"))
	, m_MoveDirection(moveDirection)
	, m_pTransformComponent(pOwner->GetComponent<TransformComponent>())
	, m_pActorComponent(pOwner->GetComponent<ActorComponent>())
	, m_MoveSpeed(moveSpeed)
{

}

void dae::MoveState::OnEnter()
{
	switch (m_MoveDirection)
	{
	case MoveDirection::Left:
		if (m_pActorComponent->GetIsGrounded() == true)
		{
			m_pActorComponent->MoveToGround();
			m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pLeftTexture, 1, 4, 3);
			m_Movement = glm::vec2{ -m_MoveSpeed, 0 };
		}
		break;
	case MoveDirection::Right:
		if (m_pActorComponent->GetIsGrounded() == true)
		{
			m_pActorComponent->MoveToGround();
			m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pRightTexture, 1, 4, 3);
			m_Movement = glm::vec2{ m_MoveSpeed , 0 };
		}
		break;
	case MoveDirection::Up:
		if (m_pActorComponent->GetIsOnLadder() == true)
		{
			m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pUpTexture, 1, 4, 3);
			m_Movement = glm::vec2{ 0, -m_MoveSpeed };
		}
		break;
	case MoveDirection::Down:
		if (m_pActorComponent->GetIsOnLadder() == true && m_pActorComponent->GetCantClimbDown() == false)
		{
			m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pDownTexture, 1, 4, 3);
			m_Movement = glm::vec2{ 0, m_MoveSpeed };
			m_MovingDown = true;
		}
		break;
	}
}

void dae::MoveState::OnExit()
{
}

void dae::MoveState::Update()
{
	const bool climbDown = m_pActorComponent->GetCantClimbDown();
	if (climbDown == true && m_MovingDown == true)
	{
		m_pActorComponent->SetState(std::make_shared<IdleState>(m_pOwner));
		return;
	}
	m_pTransformComponent->Translate(m_Movement * Clock::GetInstance().GetDeltaTime());
}

std::string dae::MoveState::GetType()
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
