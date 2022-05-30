#include "BurgerTimePCH.h"
#include "MoveState.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

dae::MoveState::MoveState(GameObject* pOwner, MoveDirection moveDirection)
	:State(pOwner)
	,m_MoveDirection(moveDirection)
	,m_pLeftTexture(ResourceManager::GetInstance().LoadTexture("Running.png"))
	,m_pRightTexture(ResourceManager::GetInstance().LoadTexture("RunningRight.png"))
	,m_pUpTexture(ResourceManager::GetInstance().LoadTexture("Climbing.png"))
	,m_pDownTexture(ResourceManager::GetInstance().LoadTexture("Decending.png"))
	, m_pTransformComponent(pOwner->GetComponent<TransformComponent>())
{
}

void dae::MoveState::OnEnter()
{
	switch (m_MoveDirection)
	{
	case MoveDirection::Left:
		m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pLeftTexture, 1, 4, 3);
		m_Movement = glm::vec2{ -m_MoveSpeed * Clock::GetInstance().GetDeltaTime(), 0 };
		break;
	case MoveDirection::Right:
		m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pRightTexture, 1, 4, 3);
		m_Movement = glm::vec2{ m_MoveSpeed * Clock::GetInstance().GetDeltaTime(), 0 };
		break;
	case MoveDirection::Up:
		m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pUpTexture, 1, 4, 3);
		m_Movement = glm::vec2{ 0, -m_MoveSpeed * Clock::GetInstance().GetDeltaTime() };
		break;
	case MoveDirection::Down:
		m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pDownTexture, 1, 4, 3);
		m_Movement = glm::vec2{ 0, m_MoveSpeed * Clock::GetInstance().GetDeltaTime() };
		break;
	}
}

void dae::MoveState::OnExit()
{
}

void dae::MoveState::Update()
{
	m_pTransformComponent->Translate(m_Movement);
}
