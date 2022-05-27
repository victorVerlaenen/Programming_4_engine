#include "BurgerTimePCH.h"
#include "MrPepperComponent.h"
#include "PlayerControllerComponent.h"
#include "PointsCommand.h"
#include "DieCommand.h"

dae::MrPepperComponent::MrPepperComponent(GameObject* pOwner)
	:Component(pOwner)
	, m_pPlayerControllerComponent{ GetOwner()->GetComponent<PlayerControllerComponent>() }
{
	m_pPlayerControllerComponent->AddCommand(ButtonState::Down, ControllerButton::X, std::make_unique<PointsCommand>(GetOwner()));
	m_pPlayerControllerComponent->AddCommand(ButtonState::Down, ControllerButton::A, std::make_unique<DieCommand>(GetOwner()));
}

void dae::MrPepperComponent::Update()
{
}

void dae::MrPepperComponent::FixedUpdate()
{
}

void dae::MrPepperComponent::Render() const
{
}
