#include "BurgerTimePCH.h"
#include "ScoreComponent.h"

#include <thread>

#include "AudioSystem.h"
#include "IngredientComponent.h"
#include "ServiceLocator.h"
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
	if (event == Event::EVENT_PLAYER_POINTS)
	{
		m_Score += 50;
		m_pTextComponent->SetText("SCORE: " + std::to_string(m_Score));
		for(const auto ingredient : IngredientComponent::m_pIngredients)
		{
			if (ingredient->GetIngredientState() != IngedientState::Collected)
				return;
		}
		ServiceLocator::GetAudioSystem().PlaySound("Level_Complete.mp3", false);
		std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours(std::numeric_limits<int>::max()));
	}
}