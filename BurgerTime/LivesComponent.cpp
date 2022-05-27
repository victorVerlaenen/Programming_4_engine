#include "BurgerTimePCH.h"
#include "LivesComponent.h"
#include "TextComponent.h"

dae::LivesComponent::LivesComponent(GameObject* pOwner)
	:Component(pOwner)
	, m_pTextComponent{ GetOwner()->GetComponent<TextComponent>() }
{
	m_pTextComponent->SetText("Lives: " + std::to_string(m_Lives));
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
		m_pTextComponent->SetText("Lives: " + std::to_string(m_Lives));
	}
}