#include "BurgerTimePCH.h"
#include "TileComponent.h"
#include "RenderComponent.h"

#include "CollisionComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

std::vector<dae::TileComponent*> dae::TileComponent::m_pTileComponents = {};

dae::TileComponent::TileComponent(GameObject* pOwner, TileType tileType)
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

	for(const auto actorComponent : ActorComponent::m_pActorComponents)
	{
		m_pActorColliders.push_back(actorComponent->GetCollider());
		m_pActorTransformComponents.push_back(actorComponent->GetTransform());
	}
	m_pTileComponents.push_back(this);
}

void dae::TileComponent::Update()
{
	for(const auto actorComponent : ActorComponent::m_pActorComponents)
	{
		actorComponent->SetIsOnLadder(false);
		actorComponent->SetIsGrounded(false);
		actorComponent->SetColliding(false);
		actorComponent->SetCantClimbDown(true);
		actorComponent->SetCantClimbUp(true);
		actorComponent->SetIsPastPlatform(true);
	}
}

void dae::TileComponent::LateUpdate()
{
	for (size_t i{}; i < ActorComponent::m_pActorComponents.size(); ++i)
	{
		if(m_pCollisionComponent->IsOverlapping(m_pActorTransformComponents[i]->GetPosition()))
		{
			ActorComponent::m_pActorComponents[i]->SetIsPastPlatform(false);
			ActorComponent::m_pActorComponents[i]->SetFixPosition(m_pActorTransformComponents[i]->GetPosition());
		}
		if (m_pCollisionComponent->IsOverlapping(m_pActorColliders[i]->GetShape()))
		{
			if (m_TileType != TileType::Ladder)
			{

				if (std::abs(m_pActorTransformComponents[i]->GetPosition().y - static_cast<float>(m_pCollisionComponent->GetShape().yPos)) <= GetPlatformMargin() * 2)
				{
					if (m_TileType == TileType::LadderPlatform)
					{
						ActorComponent::m_pActorComponents[i]->SetCantClimbDown(false);//
					}
					
					ActorComponent::m_pActorComponents[i]->SetIsGrounded(true);//
					ActorComponent::m_pActorComponents[i]->SetGroundYPos(static_cast<float>(m_pCollisionComponent->GetShape().yPos + GetPlatformMargin()));
				}
			}
			else
			{
				ActorComponent::m_pActorComponents[i]->SetCantClimbUp(false);//
			}

			if (m_TileType == TileType::LadderPlatform || m_TileType == TileType::Ladder)
			{
				if (m_pCollisionComponent->IsBetween(m_pActorColliders[i]->GetShape(), 8))
				{
					ActorComponent::m_pActorComponents[i]->SetIsOnLadder(true);//
				}
			}
			ActorComponent::m_pActorComponents[i]->SetColliding(true);//
		}
	}
}
