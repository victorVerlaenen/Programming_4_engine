#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "Component.h"

TransformComponent::TransformComponent(std::shared_ptr<dae::GameObject> pOwner, const glm::vec2& position)
	:Component{pOwner}
	,m_Position{position}
{

}

void TransformComponent::Update(float)
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