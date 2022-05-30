#pragma once
#include "Component.h"
#include "State.h"
#include "Subject.h"

namespace dae
{
	class PlayerControllerComponent;
	class MrPepperComponent : public Component, public Subject
	{
	public:
		MrPepperComponent(GameObject* pOwner);
		~MrPepperComponent() override = default;

		void Initialize();
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;
		void SetState(std::shared_ptr<State> pState);

		MrPepperComponent(const MrPepperComponent& other) = delete;
		MrPepperComponent(MrPepperComponent&& other) = delete;
		MrPepperComponent& operator=(const MrPepperComponent& other) = delete;
		MrPepperComponent& operator=(MrPepperComponent&& other) = delete;
	private:
		PlayerControllerComponent* m_pPlayerControllerComponent;
		std::shared_ptr<State> m_pState;
	};
}

