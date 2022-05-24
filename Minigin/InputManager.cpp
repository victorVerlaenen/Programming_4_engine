#include "MiniginPCH.h"
#include "InputManager.h"

bool dae::InputManager::ProcessInput() const
{
	for (size_t controllerIdx{ 0 }; controllerIdx < m_Controllers.size(); ++controllerIdx)
	{
		m_Controllers[controllerIdx]->ProcessInput();
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}


void dae::InputManager::HandleInput() const
{
	for (size_t controllerIdx{ 0 }; controllerIdx < m_Controllers.size(); ++controllerIdx)
	{
		m_Controllers[controllerIdx]->HandleInput();
	}
}

void dae::InputManager::AddController(unsigned controllerIndex)
{
	if (m_Controllers.size() == m_MaxControllers)
	{
		return;
	}
	auto controller = std::make_unique<XBoxOneController>(controllerIndex);
	m_Controllers.push_back(std::move(controller));
}

void dae::InputManager::AddCommand(int controllerIdx, ButtonState state, ControllerButton button, std::unique_ptr<Command> command) const
{
	m_Controllers[controllerIdx]->AddCommand(state, button, std::move(command));
}

int dae::InputManager::GetNextControllerIndex() const
{
	return static_cast<int>(m_Controllers.size());
}
