#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner, const std::string& filename)
	:Component{pOwner}
	,m_pTransformComponent{ GetOwner()->GetComponent<TransformComponent>() }
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
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
}