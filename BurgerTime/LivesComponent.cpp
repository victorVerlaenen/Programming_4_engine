#include "BurgerTimePCH.h"
#include "LivesComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"

dae::LivesComponent::LivesComponent(GameObject* pOwner)
	:Component(pOwner)
	, m_pRenderComponent{ GetOwner()->GetComponent<RenderComponent>() }
{
	m_pRenderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Lives_" + std::to_string(m_Lives) + ".png"));
}

void dae::LivesComponent::Update()
{

}

void dae::LivesComponent::FixedUpdate()
{
}

void dae::LivesComponent::Render() const
{
}

void dae::LivesComponent::OnNotify(GameObject*, const Event& event)
{
	if (event == Observer::Event::EVENT_ACTOR_DIED)
	{
		m_Lives--;
		if (m_Lives <= 0)
		{
			m_pRenderComponent->SetTexture(nullptr);
			return;
		}
		m_pRenderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Lives_" + std::to_string(m_Lives) + ".png"));
	}
}