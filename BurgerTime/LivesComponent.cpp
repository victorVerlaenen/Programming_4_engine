#include "BurgerTimePCH.h"
#include "LivesComponent.h"

#include "ActorComponent.h"
#include "AudioSystem.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"

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
	if (event == Event::EVENT_ACTOR_DIED)
	{
		m_Lives--;
		if (m_Lives <= 0)
		{
			m_pRenderComponent->SetTexture(nullptr);

			ServiceLocator::GetAudioSystem().PlaySound("Game_Over.mp3", false);
			std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours(std::numeric_limits<int>::max()));
		}
		m_pRenderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Lives_" + std::to_string(m_Lives) + ".png"));
		ServiceLocator::GetAudioSystem().PlaySound("Lose_Life.mp3", false);
		for(const auto actor : ActorComponent::m_pActorComponents)
		{
			actor->Reset();
		}
	}
}