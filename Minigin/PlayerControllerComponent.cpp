#include "MiniginPCH.h"
#include "PlayerControllerComponent.h"
#include "InputManager.h"

dae::PlayerControllerComponent::PlayerControllerComponent(GameObject* pOwner)
	:Component(pOwner)
{
	m_ControllerIndex = InputManager::GetInstance().GetNextControllerIndex();
	InputManager::GetInstance().AddController(m_ControllerIndex);
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

void dae::PlayerControllerComponent::AddCommand(ButtonState state, ControllerButton button, std::unique_ptr<Command> command)
{
	InputManager::GetInstance().AddCommand(m_ControllerIndex, state, button, std::move(command));
}
