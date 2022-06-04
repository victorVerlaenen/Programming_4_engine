#include "BurgerTimePCH.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "SpriteRenderComponent.h"
#include "TransformComponent.h"

dae::CollisionComponent::CollisionComponent(GameObject* pOwner)
	:Component(pOwner)
	, m_pRenderComponent{ pOwner->GetComponent<RenderComponent>() }
	, m_pSpriteRenderComponent{ pOwner->GetComponent<SpriteRenderComponent>() }
{
}

dae::CollisionComponent::CollisionComponent(GameObject* pOwner, int xPos, int yPos)
	:Component(pOwner)
	, m_pRenderComponent{ pOwner->GetComponent<RenderComponent>() }
	, m_pSpriteRenderComponent{ pOwner->GetComponent<SpriteRenderComponent>() }
	, m_Shape(Rect{ xPos,yPos,0,0 })
{
}

dae::CollisionComponent::CollisionComponent(GameObject* pOwner, int xPos, int yPos, int width, int height)
	:Component(pOwner)
	, m_pRenderComponent{ pOwner->GetComponent<RenderComponent>() }
	, m_pSpriteRenderComponent{ pOwner->GetComponent<SpriteRenderComponent>() }
	, m_Shape(Rect{ xPos,yPos,width,height })
{
	
}


void dae::CollisionComponent::Update()
{
	if (m_pSpriteRenderComponent != nullptr)
	{
		m_Shape.xPos = static_cast<int>(m_pSpriteRenderComponent->GetPosition().x);
		m_Shape.yPos = static_cast<int>(m_pSpriteRenderComponent->GetPosition().y) - m_Margin;
		m_Shape.width = m_pSpriteRenderComponent->GetTextureWidth();
		m_Shape.height = m_pSpriteRenderComponent->GetTextureHeight() + m_Margin;
	}
	else
	{
		m_Shape.xPos = static_cast<int>(m_pRenderComponent->GetPosition().x);
		m_Shape.yPos = static_cast<int>(m_pRenderComponent->GetPosition().y) - m_Margin;
		m_Shape.width = m_pRenderComponent->GetTextureWidth();
		m_Shape.height = m_pRenderComponent->GetTextureHeight() + m_Margin;
	}

}

void dae::CollisionComponent::FixedUpdate()
{
}

void dae::CollisionComponent::Render() const
{
}

void dae::CollisionComponent::AddPlaformMargin(int margin)
{
	m_Margin = margin;
	m_Shape.height += margin;
}

bool dae::CollisionComponent::IsOverlapping(const Rect& otherShape) const
{
	// If one rectangle is on left side of the other
	if ((m_Shape.xPos + m_Shape.width) < otherShape.xPos || (otherShape.xPos + otherShape.width) < m_Shape.xPos)
	{
		return false;
	}

	// If one rectangle is under the other
	if (m_Shape.yPos > (otherShape.yPos + otherShape.height) || otherShape.yPos > (m_Shape.yPos + m_Shape.height))
	{
		return false;
	}

	return true;
}

bool dae::CollisionComponent::IsOverlapping(const glm::vec2& point) const
{
	// If one rectangle is on left side of the other
	if (point.x < m_Shape.xPos || (m_Shape.xPos + m_Shape.width) < point.x)
	{
		return false;
	}

	// If one rectangle is under the other
	if (point.y > (m_Shape.yPos + m_Shape.height) || point.y < m_Shape.yPos)
	{
		return false;
	}
	return true;
}

bool dae::CollisionComponent::IsBetween(const Rect& otherShape) const
{
	if (m_Shape.xPos + 8 < otherShape.xPos || (m_Shape.xPos + m_Shape.width - 8) > (otherShape.xPos + otherShape.width))
	{
		return false;
	}
	
	return true;
}
