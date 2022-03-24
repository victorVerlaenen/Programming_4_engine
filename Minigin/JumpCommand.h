#pragma once
#include <iostream>
#include "Command.h"

class JumpCommand : public Command
{
public:
	JumpCommand() = default;
	~JumpCommand() override = default;
	JumpCommand(const JumpCommand& other) = delete;
	JumpCommand(JumpCommand&& other) noexcept = delete;
	JumpCommand& operator=(const JumpCommand& other) = delete;
	JumpCommand& operator=(JumpCommand&& other) noexcept = delete;

	void Execute() override { std::cout << "Jump\n"; }
};

