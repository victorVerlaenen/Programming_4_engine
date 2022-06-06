#include "BurgerTimePCH.h"
#include "IngredientComponent.h"

#include "ResourceManager.h"
#include "PlateComponent.h"
#include "RenderComponent.h"
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
	SetCollisionPieces();

	m_pPlayerCollisionComponent = pPlayerObject->GetComponent<CollisionComponent>();
	m_pPlayerTransformComponent = pPlayerObject->GetComponent<TransformComponent>();

	m_pIngredients.push_back(this);
}

void dae::IngredientComponent::Update()
{
	SetCollisionPieces();
	switch (m_IngredientState)
	{
	case IngedientState::OnPlatform:
		m_Timer = 0;
		if (m_pCollisionComponent->IsOverlapping(m_pPlayerCollisionComponent->GetShape()))
		{
			if (m_pPlayerCollisionComponent->IsBetween(m_LeftPiece))
			{
				m_LeftWalked = true;
			}
			if (m_pPlayerCollisionComponent->IsBetween(m_MiddleLeftPiece))
			{
				m_MiddleLeftWalked = true;
			}
			if (m_pPlayerCollisionComponent->IsBetween(m_MiddleRightPiece))
			{
				m_MiddleRightWalked = true;
			}
			if (m_pPlayerCollisionComponent->IsBetween(m_RightPiece))
			{
				m_RightWalked = true;
			}
		}
		if(m_LeftWalked && m_MiddleLeftWalked && m_MiddleRightWalked && m_RightWalked)
		{
			m_IngredientState = IngedientState::Falling;
		}
		break;
	case IngedientState::Falling:
		m_RightWalked = false;
		m_MiddleRightWalked = false;
		m_MiddleLeftWalked = false;
		m_LeftWalked = false;

		m_pTransformComponent->Translate(glm::vec2{ 0, 80 * Clock::GetInstance().GetDeltaTime() });
		m_Timer += Clock::GetInstance().GetDeltaTime();
		for (const auto tileComp : TileComponent::m_pTileComponents)
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

void dae::IngredientComponent::SetCollisionPieces()
{
	m_LeftPiece = m_pCollisionComponent->GetShape();
	m_LeftPiece.width = m_LeftPiece.width / 4;
	m_MiddleLeftPiece = m_LeftPiece;
	m_MiddleLeftPiece.xPos += m_MiddleLeftPiece.width;
	m_MiddleRightPiece = m_MiddleLeftPiece;
	m_MiddleRightPiece.xPos += m_MiddleRightPiece.width;
	m_RightPiece = m_MiddleRightPiece;
	m_RightPiece.xPos += m_RightPiece.width;
}
