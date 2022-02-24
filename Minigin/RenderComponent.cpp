#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "TransformComponent.h"

RenderComponent::RenderComponent(std::shared_ptr<dae::GameObject> pOwner)
	:Component{pOwner}
{

}

void RenderComponent::Update(float)
{
	
}

void RenderComponent::FixedUpdate(float)
{

}

void RenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		//Again hotcode path, gotta check
		const glm::vec2& pos = m_pOwner.lock()->GetComponent<TransformComponent>()->GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void RenderComponent::SetTexture(std::shared_ptr<dae::Texture2D> pTexture)
{
	m_pTexture = pTexture;
}