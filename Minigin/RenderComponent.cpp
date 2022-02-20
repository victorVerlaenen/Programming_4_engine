#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"

RenderComponent::RenderComponent(dae::GameObject* pOwner)
	:Component{pOwner}
{

}

void RenderComponent::Update(float)
{
	Render();
}

void RenderComponent::SetTexture(dae::Texture2D* pTexture)
{
	m_pTexture = pTexture;
}

void RenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		glm::vec2 pos = m_pOwner->GetComponent<TransformComponent>()->GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}