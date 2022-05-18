#pragma once
#include "Command.h"
namespace dae
{
	class JumpCommand : public Command
	{
	public:
		JumpCommand(GameObject* actor);
		~JumpCommand() override = default;
		JumpCommand(const JumpCommand& other) = delete;
		JumpCommand(JumpCommand&& other) noexcept = delete;
		JumpCommand& operator=(const JumpCommand& other) = delete;
		JumpCommand& operator=(JumpCommand&& other) noexcept = delete;

		void Execute() override;
	};
}
