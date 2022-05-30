#pragma once
#include "Command.h"
namespace dae
{
	class MrPepperComponent;

	enum class MoveDirection
	{
		Left,
		Right,
		Up,
		Down
	};
	class MoveCommand : public Command
	{
	public:

		MoveCommand(GameObject* actor, MoveDirection moveDirection);
		~MoveCommand() override = default;
		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) noexcept = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) noexcept = delete;

		void Execute() override;
	private:
		MoveDirection m_MoveDirection;
		MrPepperComponent* m_pMrPepperComponent;
	};
}