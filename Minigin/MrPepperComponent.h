#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class MrPepperComponent : public Component, public Subject
	{
	public:
		MrPepperComponent(GameObject* pOwner);
		~MrPepperComponent() override = default;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		MrPepperComponent(const MrPepperComponent& other) = delete;
		MrPepperComponent(MrPepperComponent&& other) = delete;
		MrPepperComponent& operator=(const MrPepperComponent& other) = delete;
		MrPepperComponent& operator=(MrPepperComponent&& other) = delete;
	};
}

