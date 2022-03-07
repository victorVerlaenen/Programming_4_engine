#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "TransformComponent.h"

RenderComponent::RenderComponent(dae::GameObject* pOwner)
	:Component{pOwner}
	,m_pTransformComponent{ GetOwner()->GetComponent<TransformComponent>() }
{
	
}

void RenderComponent::Update()
{
	
}

void RenderComponent::FixedUpdate()
{

}

void RenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const glm::vec2& pos = m_pTransformComponent->GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void RenderComponent::SetTexture(std::shared_ptr<dae::Texture2D> pTexture)
{
	m_pTexture = pTexture;
}