#include "MiniginPCH.h"
#include "FPSComponent.h"

FPSComponent::FPSComponent(dae::GameObject* pOwner)
	:Component{ pOwner }
	, m_pTextComponent{ GetOwner()->GetComponent<TextComponent>() }
{

}

void FPSComponent::Update()
{
	m_FramesPerSecond = static_cast<int>(1 / Time::GetInstance().GetDeltaTime());
	m_pTextComponent->SetText("FPS: " + std::to_string(m_FramesPerSecond));
}

void FPSComponent::FixedUpdate()
{

}

void FPSComponent::Render() const
{
	
}