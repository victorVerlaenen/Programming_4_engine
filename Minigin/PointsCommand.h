#pragma once
#include "Command.h"
namespace dae
{
	class PointsCommand : public Command
	{
	public:
		PointsCommand(GameObject* actor);
		~PointsCommand() override = default;
		PointsCommand(const PointsCommand& other) = delete;
		PointsCommand(PointsCommand&& other) noexcept = delete;
		PointsCommand& operator=(const PointsCommand& other) = delete;
		PointsCommand& operator=(PointsCommand&& other) noexcept = delete;

		void Execute() override;
	};
}

