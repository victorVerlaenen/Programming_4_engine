#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"

RenderComponent::RenderComponent(dae::Texture2D* pTexture, TransformComponent* pTransform, std::shared_ptr<dae::GameObject> pOwner)
	:Component{pOwner}
	,m_pTransform{pTransform}
	,m_pTexture{pTexture}
{

}

void RenderComponent::Update(float)
{
	Render();
}

void RenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const glm::vec2 pos = m_pTransform->GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}