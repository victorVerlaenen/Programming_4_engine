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
{
	if (!filename.empty())
	{
		m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
		m_Width = m_pTexture->GetWidth();
		m_Height = m_pTexture->GetHeight();
	}
}

void dae::RenderComponent::Update()
{
	m_Position = m_pTransformComponent->GetPosition();
	SetPos(m_RenderMode, m_Position);
}

void dae::RenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, m_Position.x, m_Position.y, m_Scale);
	}
}

glm::vec2 dae::RenderComponent::GetPosition() const
{
	return m_Position;
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
	m_Width = m_pTexture->GetWidth();
	m_Height = m_pTexture->GetHeight();
}


void dae::RenderComponent::SetPos(RenderMode renderMode, glm::vec2& pos) const
{
	switch (renderMode)
	{
	case RenderMode::CenterCenter:
		pos.x = (pos.x - GetTextureWidth() / 2.f);
	case RenderMode::LeftCenter:
		pos.y = (pos.y - GetTextureHeight() / 2.f);
		break;
	case RenderMode::CenterBottom:
		pos.y = (pos.y - GetTextureHeight());
	case RenderMode::CenterTop:
		pos.x = (pos.x - GetTextureWidth() / 2.f);
		break;
	case RenderMode::RightBottom:
		pos.x = (pos.x - GetTextureWidth());
	case RenderMode::LeftBottom:
		pos.y = (pos.y - GetTextureHeight());
		break;
	case RenderMode::RightCenter:
		pos.y = (pos.y - GetTextureHeight() / 2.f);
	case RenderMode::RightTop:
		pos.x = (pos.x - GetTextureWidth());
		break;
	case RenderMode::LeftTop:
	default:
		break;
	}
}
