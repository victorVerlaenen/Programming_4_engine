#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner)
	:RenderComponent(pOwner, RenderMode::LeftTop, {})
{
}

dae::RenderComponent::RenderComponent(GameObject* pOwner, RenderMode renderMode, const std::string& filename)
	: RenderComponent(pOwner, 1, renderMode, filename)
{
}

dae::RenderComponent::RenderComponent(GameObject* pOwner, const int scale, RenderMode renderMode, const std::string& filename)
	: Component{ pOwner }
	, m_pTransformComponent{ GetOwner()->GetComponent<TransformComponent>() }
	, m_RenderMode{ renderMode }
	, m_Scale(scale)
	, m_pTexture(nullptr)
	, m_IsScaled(true)
	, m_Width(0)
	, m_Height(0)
{
	if (!filename.empty())
	{
		m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	}
}

dae::RenderComponent::RenderComponent(GameObject* pOwner, int width, int height, RenderMode renderMode, const std::string& filename)
	:Component(pOwner)
	, m_pTransformComponent{ GetOwner()->GetComponent<TransformComponent>() }
	, m_RenderMode{ renderMode }
	, m_Scale(0)
	, m_pTexture(nullptr)
	, m_IsScaled(false)
	, m_Width(width)
	, m_Height(height)
{
	if (!filename.empty())
	{
		m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	}
}

void dae::RenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const glm::vec2& pos = m_pTransformComponent->GetPosition();
		if(m_IsScaled)
		{
			Renderer::GetInstance().RenderTexture(*m_pTexture, m_RenderMode, pos.x, pos.y, m_Scale);
		}
		else
		{
			Renderer::GetInstance().RenderTexture(*m_pTexture, m_RenderMode, pos.x, pos.y, static_cast<float>( m_Width), static_cast<float>(m_Height));
		}
	}
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
}