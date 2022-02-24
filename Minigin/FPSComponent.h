#pragma once
#include "Component.h"
#include "TextComponent.h"

class FPSComponent : public Component
{
public:
	FPSComponent(std::shared_ptr<dae::GameObject> pOwner);
	~FPSComponent() override = default;

	void Update(float deltaTime) override;
	void Render() const override {};

	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) = delete;
private:
	int m_OldFramesPerSecond;
	int m_FramesPerSecond;
	std::shared_ptr<TextComponent> m_pTextComponent;
};

