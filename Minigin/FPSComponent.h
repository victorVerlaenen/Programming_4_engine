#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;
	class FPSComponent : public Component
	{
	public:
		FPSComponent(GameObject* pOwner);
		~FPSComponent() override = default;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;
	private:
		int m_FramesPerSecond;
		TextComponent* m_pTextComponent;
	};
}