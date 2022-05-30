#pragma once
#include "Command.h"
namespace dae
{
	class MrPepperComponent;
	
	class StopCommand : public Command
	{
	public:

		StopCommand(GameObject* actor);
		~StopCommand() override = default;
		StopCommand(const StopCommand& other) = delete;
		StopCommand(StopCommand&& other) noexcept = delete;
		StopCommand& operator=(const StopCommand& other) = delete;
		StopCommand& operator=(StopCommand&& other) noexcept = delete;

		void Execute() override;
	private:
		MrPepperComponent* m_pMrPepperComponent;
	};
}