#pragma once
#include "Command.h"
namespace dae
{
	class DieCommand : public Command
	{
	public:
		DieCommand(GameObject* actor);
		~DieCommand() override = default;
		DieCommand(const DieCommand& other) = delete;
		DieCommand(DieCommand&& other) noexcept = delete;
		DieCommand& operator=(const DieCommand& other) = delete;
		DieCommand& operator=(DieCommand&& other) noexcept = delete;

		void Execute() override;
	};
}