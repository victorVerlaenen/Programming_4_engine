#include "BurgerTimePCH.h"
#include "TileComponent.h"
#include "RenderComponent.h"

#include "CollisionComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

std::vector<dae::TileComponent*> dae::TileComponent::m_pTileComponents = {};

dae::TileComponent::TileComponent(GameObject* pOwner, GameObject* pPlayerObject, TileType tileType)
	:Component(pOwner)
	, m_pCollisionComponent(pOwner->GetComponent<CollisionComponent>())
	, m_pRenderComponent(pOwner->GetComponent<RenderComponent>())
	, m_TileType(tileType)
{
	switch (tileType)
	{
	case TileType::NormalPlatform:
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
	
	m_pPlayerCollisionComponent = pPlayerObject->GetComponent<CollisionComponent>();
	m_pPlayerTransformComponent = pPlayerObject->GetComponent<TransformComponent>();
	m_pMrPepperComponent = pPlayerObject->GetComponent<MrPepperComponent>();

	m_pTileComponents.push_back(this);
}

void dae::TileComponent::Update()
{
	m_pMrPepperComponent->SetIsOnLadder(false);
	m_pMrPepperComponent->SetIsGrounded(false);
	m_pMrPepperComponent->SetColliding(false);
	m_pMrPepperComponent->SetCantClimbDown(true);
}

void dae::TileComponent::LateUpdate()
{
	if (m_pCollisionComponent->IsOverlapping(m_pPlayerCollisionComponent->GetShape()))
	{
		if (m_TileType != TileType::Ladder)
		{

			if (std::abs(m_pPlayerTransformComponent->GetPosition().y - m_pCollisionComponent->GetShape().yPos) <= GetPlatformMargin() * 2)
			{
				if (m_TileType == TileType::LadderPlatform)
				{
					m_pMrPepperComponent->SetCantClimbDown(false);//
				}
				m_pMrPepperComponent->SetIsGrounded(true);//
				m_pMrPepperComponent->SetGroundYPos(static_cast<float>(m_pCollisionComponent->GetShape().yPos + GetPlatformMargin()));
			}
		}

		if (m_TileType == TileType::LadderPlatform || m_TileType == TileType::Ladder)
		{
			if (m_pCollisionComponent->IsBetween(m_pPlayerCollisionComponent->GetShape(), 8))
			{
				m_pMrPepperComponent->SetIsOnLadder(true);//
			}
		}
		m_pMrPepperComponent->SetColliding(true);//
	}
}
