#include "MiniginPCH.h"
#include "XBoxOneController.h"
#include <Windows.h>
#include <Xinput.h>

dae::XBoxOneController::XBoxOneController(int controllerIndex)
	: pImpl(std::make_unique<XBoxOneControllerImpl>(controllerIndex))
{

}

dae::XBoxOneController::XBoxOneControllerImpl::XBoxOneControllerImpl(int controllerIndex)
	: m_ControllerIndex(controllerIndex)
{

}

void dae::XBoxOneController::ProcessInput() const
{
	pImpl->ProcessInput();
}

void dae::XBoxOneController::XBoxOneControllerImpl::ProcessInput()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

void dae::XBoxOneController::HandleInput() const
{
	pImpl->HandleInput();
}

void dae::XBoxOneController::XBoxOneControllerImpl::HandleInput()
{
	for (auto it = m_ConsoleCommands.begin(); it != m_ConsoleCommands.end(); ++it)
	{
		if (it->first.first == ButtonState::Down)
		{
			if (IsDown(static_cast<unsigned int>(it->first.second)))
			{
				it->second->Execute();
			}
		}
		if (it->first.first == ButtonState::Up)
		{
			if (IsUp(static_cast<unsigned int>(it->first.second)))
			{
				it->second->Execute();
			}
		}
		if (it->first.first == ButtonState::Pressed)
		{
			if (IsPressed(static_cast<unsigned int>(it->first.second)))
			{
				it->second->Execute();
			}
		}
	}
}

bool dae::XBoxOneController::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}

bool dae::XBoxOneController::XBoxOneControllerImpl::IsPressed(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}

bool dae::XBoxOneController::IsDown(ControllerButton button) const
{
	return pImpl->IsDown(static_cast<unsigned int>(button));
}

bool dae::XBoxOneController::XBoxOneControllerImpl::IsDown(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}

bool dae::XBoxOneController::IsUp(ControllerButton button) const
{
	return pImpl->IsUp(static_cast<unsigned int>(button));
}

bool dae::XBoxOneController::XBoxOneControllerImpl::IsUp(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;
}

void dae::XBoxOneController::AddCommand(ButtonState state, ControllerButton button, std::unique_ptr<Command> command) const
{
	return pImpl->AddCommand(state, button, std::move(command));
}

void dae::XBoxOneController::XBoxOneControllerImpl::AddCommand(ButtonState state, ControllerButton button, std::unique_ptr<Command> command)
{
	m_ConsoleCommands.insert({ ControllerKey{ state, button }, std::move(command) });
}