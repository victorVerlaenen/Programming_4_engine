#include "BurgerTimePCH.h"
#include "IngredientComponent.h"

#include "ResourceManager.h"
#include "CollisionComponent.h"
#include "PlateComponent.h"
#include "PlayerControllerComponent.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "TileComponent.h"
#include "TransformComponent.h"

std::vector<dae::IngredientComponent*> dae::IngredientComponent::m_pIngredients = {};

dae::IngredientComponent::IngredientComponent(GameObject* pOwner, GameObject* pPlayerObject, Ingedient ingredientType)
	:Component(pOwner)
	, m_pCollisionComponent(pOwner->GetComponent<CollisionComponent>())
	, m_pRenderComponent(pOwner->GetComponent<RenderComponent>())
	, m_pTransformComponent(pOwner->GetComponent<TransformComponent>())
	, m_IngredientState(IngedientState::OnPlatform)
{
	switch (ingredientType)
	{
	case Ingedient::TopBun:
		m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture("Top_Bun.png"));
		break;
	case Ingedient::Lettuce:
		m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture("Lettuce.png"));
		break;
	case Ingedient::Tomato:
		m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture("Tomato.png"));
		break;
	case Ingedient::Cheese:
		m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture("Cheese.png"));
		break;
	case Ingedient::Patty:
		m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture("Patty.png"));
		break;
	case Ingedient::BottomBun:
		m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture("Bottom_Bun.png"));
		break;
	}

	m_pPlayerCollisionComponent = pPlayerObject->GetComponent<CollisionComponent>();
	m_pPlayerTransformComponent = pPlayerObject->GetComponent<TransformComponent>();

	m_pIngredients.push_back(this);
}

void dae::IngredientComponent::Update()
{
	switch (m_IngredientState)
	{
	case IngedientState::OnPlatform:
		m_Timer = 0;
		if (m_pPlayerCollisionComponent->IsOverlapping(m_pCollisionComponent->GetShape()))
		{
			if (m_pPlayerTransformComponent->GetPosition().x < m_pTransformComponent->GetPosition().x + 10 && m_pPlayerTransformComponent->GetPosition().x > m_pTransformComponent->GetPosition().x - 10)
			{
				m_IngredientState = IngedientState::Falling;
			}
		}
		break;
	case IngedientState::Falling:
		m_pTransformComponent->Translate(glm::vec2{ 0, 80 * Clock::GetInstance().GetDeltaTime() });
		m_Timer += Clock::GetInstance().GetDeltaTime();
		for (auto tileComp : TileComponent::m_pTileComponents)
		{
			if (tileComp->GetTileType() == TileType::Ladder)
			{
				continue;
			}
			if (tileComp->GetCollider()->IsOverlapping(m_pTransformComponent->GetPosition()))
			{
				if (m_Timer >= m_FallingCooldown)
				{
					m_IngredientState = IngedientState::OnPlatform;
					Notify(GetOwner(), Observer::Event::EVENT_PLAYER_POINTS);
					m_pTransformComponent->SetPosition(glm::vec2{ m_pTransformComponent->GetPosition().x, tileComp->GetCollider()->GetShape().yPos + tileComp->GetPlatformMargin() });
					return;
				}
			}
		}
		for (const auto ingredient : m_pIngredients)
		{
			if (ingredient == this)
			{
				continue;
			}
			if (ingredient->GetCollider()->IsOverlapping(m_pTransformComponent->GetPosition()))
			{
				if(ingredient->m_IngredientState == IngedientState::Collected)
				{
					m_IngredientState = IngedientState::Collected;
					Notify(GetOwner(), Observer::Event::EVENT_PLAYER_POINTS);
					return;
				}
				ingredient->m_IngredientState = IngedientState::Falling;
				return;
			}
		}
		for(const auto plate : PlateComponent::m_pPlateComponents)
		{
			if(m_pCollisionComponent->IsOverlapping(plate->GetCollider()->GetShape()))
			{
				m_IngredientState = IngedientState::Collected;
				Notify(GetOwner(), Observer::Event::EVENT_PLAYER_POINTS);
			}
		}
		break;
	case IngedientState::Collected:
		break;
	}
}

void dae::IngredientComponent::FixedUpdate()
{
}

void dae::IngredientComponent::Render() const
{
}
