#pragma once
#include "Command.h"
namespace dae
{
	class MoveCommand : public Command
	{
	public:
		MoveCommand(GameObject* actor);
		~MoveCommand() override = default;
		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) noexcept = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) noexcept = delete;

		void Execute() override;
	};
}