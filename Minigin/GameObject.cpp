#include "MiniginPCH.h"
#include "GameObject.h"

#include "Component.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for(auto pComp : m_pComponents)
	{
		pComp->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	if(m_Texture != nullptr)
	{
		
	const auto& pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}