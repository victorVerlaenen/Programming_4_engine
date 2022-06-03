#include "BurgerTimePCH.h"
#include "MoveState.h"

#include "IdleState.h"
#include "MrPepperComponent.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

dae::MoveState::MoveState(GameObject* pOwner, MoveDirection moveDirection)
	:State(pOwner)
	, m_MoveDirection(moveDirection)
	, m_pLeftTexture(ResourceManager::GetInstance().LoadTexture("Running.png"))
	, m_pRightTexture(ResourceManager::GetInstance().LoadTexture("RunningRight.png"))
	, m_pUpTexture(ResourceManager::GetInstance().LoadTexture("Climbing.png"))
	, m_pDownTexture(ResourceManager::GetInstance().LoadTexture("Decending.png"))
	, m_pTransformComponent(pOwner->GetComponent<TransformComponent>())
	, m_pMrPepperComponent(pOwner->GetComponent<MrPepperComponent>())
{

}

void dae::MoveState::OnEnter()
{
	switch (m_MoveDirection)
	{
	case MoveDirection::Left:
		if (m_pMrPepperComponent->GetIsGrounded() == true)
		{
			m_pMrPepperComponent->MoveToGround();
			m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pLeftTexture, 1, 4, 3);
			m_Movement = glm::vec2{ -m_MoveSpeed * Clock::GetInstance().GetDeltaTime(), 0 };
		}
		break;
	case MoveDirection::Right:
		if (m_pMrPepperComponent->GetIsGrounded() == true)
		{
			m_pMrPepperComponent->MoveToGround();
			m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pRightTexture, 1, 4, 3);
			m_Movement = glm::vec2{ m_MoveSpeed * Clock::GetInstance().GetDeltaTime(), 0 };
		}
		break;
	case MoveDirection::Up:
		if (m_pMrPepperComponent->GetIsOnLadder() == true)
		{
			m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pUpTexture, 1, 4, 3);
			m_Movement = glm::vec2{ 0, -m_MoveSpeed * Clock::GetInstance().GetDeltaTime() };
		}
		break;
	case MoveDirection::Down:
		if (m_pMrPepperComponent->GetIsOnLadder() == true && m_pMrPepperComponent->GetCantClimbDown() == false)
		{
			m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pDownTexture, 1, 4, 3);
			m_Movement = glm::vec2{ 0, m_MoveSpeed * Clock::GetInstance().GetDeltaTime() };
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
	const bool climbDown = m_pMrPepperComponent->GetCantClimbDown();
	if(climbDown== true && m_MovingDown == true)
	{
		m_pMrPepperComponent->SetState(std::make_shared<IdleState>(m_pOwner));
		return;
	}
	m_pTransformComponent->Translate(m_Movement);
}

std::string dae::MoveState::GetType()
{
	return "Move";
}
