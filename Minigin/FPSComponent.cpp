#include "MiniginPCH.h"
#include "FPSComponent.h"

FPSComponent::FPSComponent(std::shared_ptr<dae::GameObject> pOwner)
	:Component{ pOwner }
{

}

void FPSComponent::Update(float deltaTime)
{
	m_FramesPerSecond = static_cast<int>(1 / deltaTime);
	//On hotcode path, need to check this
	m_pOwner.lock()->GetComponent<TextComponent>()->SetText("FPS: " + std::to_string(m_FramesPerSecond));
}