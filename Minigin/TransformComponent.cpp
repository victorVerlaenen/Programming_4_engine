#include "MiniginPCH.h"
#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(GameObject* pOwner, const glm::vec2& position)
	:Component{pOwner}
	,m_Position{position}
{

}

void dae::TransformComponent::Update()
{

}

void dae::TransformComponent::FixedUpdate()
{
	
}

void dae::TransformComponent::Render() const
{
	
}


glm::vec2 dae::TransformComponent::GetPosition() const
{
	return m_Position;
}

void dae::TransformComponent::SetPosition(const glm::vec2& position)
{
	m_Position = position;
}

void dae::TransformComponent::Translate(const glm::vec2& translation)
{
	m_Position += translation;
}
