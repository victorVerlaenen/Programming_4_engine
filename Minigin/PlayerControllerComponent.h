#pragma once
#include "Component.h"
#include "XBoxOneController.h"

namespace dae
{
	class PlayerControllerComponent : public Component
	{
	public:
		PlayerControllerComponent(GameObject* pOwner);
		~PlayerControllerComponent() override = default;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		PlayerControllerComponent(const PlayerControllerComponent& other) = delete;
		PlayerControllerComponent(PlayerControllerComponent&& other) = delete;
		PlayerControllerComponent& operator=(const PlayerControllerComponent& other) = delete;
		PlayerControllerComponent& operator=(PlayerControllerComponent&& other) = delete;

		void AddCommand(ButtonState state, ControllerButton button, std::unique_ptr<Command> command);
	private:
		int m_ControllerIndex;
	};
}

