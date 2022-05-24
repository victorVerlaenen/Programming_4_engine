#include "MiniginPCH.h"
#include "PlayerControllerComponent.h"
#include "InputManager.h"
#include "DieCommand.h"
#include "PointsCommand.h"

dae::PlayerControllerComponent::PlayerControllerComponent(GameObject* pOwner)
	:Component(pOwner)
{
	m_ControllerIndex = InputManager::GetInstance().GetNextControllerIndex();
	InputManager::GetInstance().AddController(m_ControllerIndex);
	InputManager::GetInstance().AddCommand(m_ControllerIndex, ButtonState::Down, ControllerButton::A, std::make_unique<DieCommand>(pOwner));
	InputManager::GetInstance().AddCommand(m_ControllerIndex, ButtonState::Down, ControllerButton::X, std::make_unique<PointsCommand>(pOwner));
}

void dae::PlayerControllerComponent::Update()
{

}

void dae::PlayerControllerComponent::FixedUpdate()
{

}

void dae::PlayerControllerComponent::Render() const
{

}
