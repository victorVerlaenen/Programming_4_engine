#include "MiniginPCH.h"
#include "GameObject.h"
#include "Component.h"
#include "RenderComponent.h"

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
	//Gotta check if there is a beter solution to check this because a dynamic cast in hot code pad is not good
	for (const auto pComp : m_pComponents)
	{
		//if (dynamic_cast<RenderComponent*>(pComp))
			pComp->Render();
	}
}