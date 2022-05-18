#pragma once
#include <map>
#include <memory>
#include <Windows.h>
#include <Xinput.h>
#include "Command.h"

namespace dae
{
	enum class ButtonState
	{
		Down = 0,
		Up = 1,
		Pressed = 2,
		Stick = 3
	};
	enum class ControllerButton
	{
		Up = 0x0001,
		Down = 0x0002,
		Left = 0x0004,
		Right = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LeftThumb = 0x0040,
		RightThumb = 0x0080,
		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,
		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000
	};

	class XBoxOneController final
	{
	public:

		void ProcessInput() const;
		void HandleInput() const;

		void AddCommand(ButtonState state, ControllerButton button, std::unique_ptr<Command> command) const;

		explicit XBoxOneController(int controllerIndex);
		~XBoxOneController() = default;

		XBoxOneController(const XBoxOneController& other) = delete;
		XBoxOneController(XBoxOneController&& other) noexcept = delete;
		XBoxOneController& operator=(const XBoxOneController& other) = delete;
		XBoxOneController& operator=(XBoxOneController&& other) noexcept = delete;

	private:
		class XBoxOneControllerImpl;
		std::unique_ptr<XBoxOneControllerImpl> pImpl;

		bool IsPressed(ControllerButton button) const;
		bool IsDown(ControllerButton button) const;
		bool IsUp(ControllerButton button) const;
	};
}

class dae::XBoxOneController::XBoxOneControllerImpl
{
public:
	using ControllerKey = std::pair<ButtonState, ControllerButton>;
	using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;
	ControllerCommandsMap m_ConsoleCommands;

	void ProcessInput();
	void HandleInput();

	bool IsPressed(unsigned int button) const;
	bool IsDown(unsigned int button) const;
	bool IsUp(unsigned int button) const;

	void AddCommand(ButtonState state, ControllerButton button, std::unique_ptr<Command> command);

	explicit XBoxOneControllerImpl(int controllerIndex);
	~XBoxOneControllerImpl() = default;

	XBoxOneControllerImpl(const XBoxOneControllerImpl& other) = delete;
	XBoxOneControllerImpl(XBoxOneControllerImpl&& other) noexcept = delete;
	XBoxOneControllerImpl& operator=(const XBoxOneControllerImpl& other) = delete;
	XBoxOneControllerImpl& operator=(XBoxOneControllerImpl&& other) noexcept = delete;
private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	int m_ControllerIndex;
};