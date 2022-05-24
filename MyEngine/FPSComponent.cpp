#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"

dae::FPSComponent::FPSComponent(GameObject* pOwner)
	:Component{ pOwner }
	, m_pTextComponent{ GetOwner()->GetComponent<TextComponent>() }
{

}

void dae::FPSComponent::Update()
{
	m_FramesPerSecond = static_cast<int>(1 / Time::GetInstance().GetDeltaTime());
	m_pTextComponent->SetText("FPS: " + std::to_string(m_FramesPerSecond));
}

void dae::FPSComponent::FixedUpdate()
{

}

void dae::FPSComponent::Render() const
{
	
}