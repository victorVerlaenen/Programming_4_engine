#pragma once
#include "ActorComponent.h"
#include "State.h"

namespace dae
{
	class PlayerControllerComponent;
	class MrPepperComponent : public ActorComponent
	{
	public:
		MrPepperComponent(GameObject* pOwner, bool isPlayer);
		~MrPepperComponent() override = default;

		void Initialize();
		void Update() override;
		void FixedUpdate() override {}
		void Render() const override {}
		void LateUpdate() override;

		MrPepperComponent(const MrPepperComponent& other) = delete;
		MrPepperComponent(MrPepperComponent&& other) = delete;
		MrPepperComponent& operator=(const MrPepperComponent& other) = delete;
		MrPepperComponent& operator=(MrPepperComponent&& other) = delete;
	private:
		PlayerControllerComponent* m_pPlayerControllerComponent;
	};
}

