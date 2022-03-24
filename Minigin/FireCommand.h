#pragma once
#include <iostream>
#include "Command.h"

class FireCommand : public Command
{
public:
	FireCommand() = default;
	~FireCommand() override = default;
	FireCommand(const FireCommand& other) = delete;
	FireCommand(FireCommand&& other) noexcept = delete;
	FireCommand& operator=(const FireCommand& other) = delete;
	FireCommand& operator=(FireCommand&& other) noexcept = delete;

	void Execute() override { std::cout << "Fire\n"; }
};

