#pragma once
#include <iostream>
#include "Command.h"

class DuckCommand : public Command
{
public:
	DuckCommand() = default;
	~DuckCommand() override = default;
	DuckCommand(const DuckCommand& other) = delete;
	DuckCommand(DuckCommand&& other) noexcept = delete;
	DuckCommand& operator=(const DuckCommand& other) = delete;
	DuckCommand& operator=(DuckCommand&& other) noexcept = delete;

	void Execute() override { std::cout << "Duck\n"; }
};

