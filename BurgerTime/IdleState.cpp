#include "BurgerTimePCH.h"
#include "IdleState.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"

dae::IdleState::IdleState(GameObject* pOwner)
	:State(pOwner)
	,m_pTexture(ResourceManager::GetInstance().LoadTexture("Idle.png"))
{

}

void dae::IdleState::OnEnter()
{
	m_pOwner->GetComponent<SpriteRenderComponent>()->SetSprite(m_pTexture, 1, 1, 3);
}

void dae::IdleState::OnExit()
{
}

void dae::IdleState::Update()
{
}

std::string dae::IdleState::GetType()
{
	return "Idle";
}
