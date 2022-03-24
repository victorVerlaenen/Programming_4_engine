#pragma once
#include <iostream>
#include "Command.h"

class FartCommand : public Command
{
public:
	FartCommand() = default;
	~FartCommand() override = default;
	FartCommand(const FartCommand& other) = delete;
	FartCommand(FartCommand&& other) noexcept = delete;
	FartCommand& operator=(const FartCommand& other) = delete;
	FartCommand& operator=(FartCommand&& other) noexcept = delete;

	void Execute() override { std::cout << "Fart\n"; }
};

