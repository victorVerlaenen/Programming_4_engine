#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner, RenderMode renderMode, const std::string& filename)
	:Component{pOwner}
	,m_pTransformComponent{ GetOwner()->GetComponent<TransformComponent>() }
	, m_RenderMode{renderMode}
{
	if(!filename.empty())
	{
		m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	}
}

void dae::RenderComponent::Update()
{
	
}

void dae::RenderComponent::FixedUpdate()
{

}

void dae::RenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const glm::vec2& pos = m_pTransformComponent->GetPosition();
		switch (m_RenderMode)
		{
		case dae::RenderComponent::RenderMode::LeftTop:
			dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
			break;
		case dae::RenderComponent::RenderMode::CenterTop:
			dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x - m_pTexture->GetWidth()/2, pos.y);
			break;
		case dae::RenderComponent::RenderMode::RightTop:
			dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x - m_pTexture->GetWidth(), pos.y);
			break;
		case dae::RenderComponent::RenderMode::LeftCenter:
			dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y - m_pTexture->GetHeight()/2);
			break;
		case dae::RenderComponent::RenderMode::CenterCenter:
			dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x - m_pTexture->GetWidth()/2, pos.y - m_pTexture->GetHeight() / 2);
			break;
		case dae::RenderComponent::RenderMode::RightCenter:
			dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x - m_pTexture->GetWidth(), pos.y - m_pTexture->GetHeight() / 2);
			break;
		case dae::RenderComponent::RenderMode::LeftBottom:
			dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y - m_pTexture->GetHeight());
			break;
		case dae::RenderComponent::RenderMode::CenterBottom:
			dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x - m_pTexture->GetWidth()/2, pos.y - m_pTexture->GetHeight());
			break;
		case dae::RenderComponent::RenderMode::RightBottom:
			dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x - m_pTexture->GetWidth(), pos.y - m_pTexture->GetHeight());
			break;
		default:
			dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x , pos.y);
			break;
		}
	}
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
}