#include "MiniginPCH.h"
#include "GameObject.h"

#include "Component.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for(auto& pComp : m_pComponents)
	{
		delete pComp;
		pComp = nullptr;
	}
}

void dae::GameObject::Update()
{
	for (const auto pComp : m_pComponents)
	{
		pComp->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (const auto pComp : m_pComponents)
	{
		pComp->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
	//Gotta check if there is a beter solution to check this because a dynamic cast in hot code pad is not good
	for (const auto pComp : m_pComponents)
	{
		if (dynamic_cast<RenderComponent*>(pComp))
			pComp->Render();
	}
}

void dae::GameObject::SetTexture(const std::string & filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}