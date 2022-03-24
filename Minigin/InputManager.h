#pragma once
#include "Singleton.h"
#include <memory>
#include <vector>
#include "XBoxOneController.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		~InputManager() override = default;
		InputManager(const InputManager & other) = delete;
		InputManager(InputManager && other) noexcept = delete;
		InputManager& operator=(const InputManager & other) = delete;
		InputManager& operator=(InputManager && other) noexcept = delete;

		bool ProcessInput() const;
		void HandleInput() const;
		void AddController(unsigned controllerIndex);

		void AddCommand(int controllerIdx, ButtonState state, ControllerButton button, std::unique_ptr<Command> command) const;
	private:
		std::vector<std::unique_ptr<XBoxOneController>> m_Controllers{};
		const int m_MaxControllers{ 4 };
	};

}
