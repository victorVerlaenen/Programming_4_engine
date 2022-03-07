#include "MiniginPCH.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(dae::GameObject* pOwner, const glm::vec2& position)
	:Component{pOwner}
	,m_Position{position}
{

}

void TransformComponent::Update()
{

}

void TransformComponent::FixedUpdate()
{
	
}

void TransformComponent::Render() const
{
	
}


glm::vec2 TransformComponent::GetPosition() const
{
	return m_Position;
}

void TransformComponent::SetPosition(const glm::vec2& position)
{
	m_Position = position;
}