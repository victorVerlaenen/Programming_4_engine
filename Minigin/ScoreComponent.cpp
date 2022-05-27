#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pOwner)
	:Component(pOwner)
	, m_pTextComponent{ GetOwner()->GetComponent<TextComponent>() }
{
	m_pTextComponent->SetText("SCORE: " + std::to_string(m_Score));
}

void dae::ScoreComponent::Update()
{
	
}

void dae::ScoreComponent::FixedUpdate()
{
}

void dae::ScoreComponent::Render() const
{
}

void dae::ScoreComponent::OnNotify(GameObject*, const Event& event)
{
	if (event == Observer::Event::EVENT_PLAYER_POINTS)
	{
		m_Score += 50;
		m_pTextComponent->SetText("SCORE: " + std::to_string(m_Score));
	}
}