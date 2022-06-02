#include "BurgerTimePCH.h"
#include "TileComponent.h"
#include "RenderComponent.h"

#include "CollisionComponent.h"
#include "MrPepperComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

dae::TileComponent::TileComponent(GameObject* pOwner, TileType tileType)
	:Component(pOwner)
	, m_pCollisionComponent(pOwner->GetComponent<CollisionComponent>())
	, m_pRenderComponent(pOwner->GetComponent<RenderComponent>())
	, m_TileType(tileType)
{
	switch (tileType)
	{
	case TileType::NormalPlaform:
		m_pCollisionComponent->AddPlaformMargin(m_PlatformMargin);
		m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture("NormalPlatform.png"));
		break;
	case TileType::LadderPlatform:
		m_pCollisionComponent->AddPlaformMargin(m_PlatformMargin);
		m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture("LadderPlatform.png"));
		break;
	case TileType::Ladder:
		m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture("Ladder.png"));
		break;
	}
}

void dae::TileComponent::Update()
{
	
}

void dae::TileComponent::FixedUpdate()
{
}

void dae::TileComponent::Render() const
{
}
