#include "BurgerTimePCH.h"
#include "MrPepperComponent.h"
#include "PlayerControllerComponent.h"
#include "PointsCommand.h"
#include "DieCommand.h"
#include "IdleState.h"
#include "MoveCommand.h"
#include "StopCommand.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"

dae::MrPepperComponent::MrPepperComponent(GameObject* pOwner, bool isPlayer)
	:ActorComponent(pOwner, isPlayer)
	, m_pPlayerControllerComponent{ GetOwner()->GetComponent<PlayerControllerComponent>() }
{
	Initialize();
}

void dae::MrPepperComponent::Initialize()
{
	//Testing
	m_pPlayerControllerComponent->AddCommand(ButtonState::Down, ControllerButton::X, std::make_unique<PointsCommand>(GetOwner()));
	m_pPlayerControllerComponent->AddCommand(ButtonState::Down, ControllerButton::A, std::make_unique<DieCommand>(GetOwner()));

	//Movement
	m_pPlayerControllerComponent->AddCommand(ButtonState::Down, ControllerButton::Left, std::make_unique<MoveCommand>(GetOwner(), MoveDirection::Left));
	m_pPlayerControllerComponent->AddCommand(ButtonState::Up, ControllerButton::Left, std::make_unique<StopCommand>(GetOwner()));

	m_pPlayerControllerComponent->AddCommand(ButtonState::Down, ControllerButton::Right, std::make_unique<MoveCommand>(GetOwner(), MoveDirection::Right));
	m_pPlayerControllerComponent->AddCommand(ButtonState::Up, ControllerButton::Right, std::make_unique<StopCommand>(GetOwner()));

	m_pPlayerControllerComponent->AddCommand(ButtonState::Down, ControllerButton::Up, std::make_unique<MoveCommand>(GetOwner(), MoveDirection::Up));
	m_pPlayerControllerComponent->AddCommand(ButtonState::Up, ControllerButton::Up, std::make_unique<StopCommand>(GetOwner()));

	m_pPlayerControllerComponent->AddCommand(ButtonState::Down, ControllerButton::Down, std::make_unique<MoveCommand>(GetOwner(), MoveDirection::Down));
	m_pPlayerControllerComponent->AddCommand(ButtonState::Up, ControllerButton::Down, std::make_unique<StopCommand>(GetOwner()));
}

void dae::MrPepperComponent::Update()
{
	
}

void dae::MrPepperComponent::LateUpdate()
{
	if (m_IsGrounded == false)
	{
		m_CantClimbdown = false;
	}
	if (m_Colliding == false)
	{
		SetState(std::make_shared<IdleState>(GetOwner()));
	}

	if (m_IsPastPlatform == true)
	{
		m_pTransformComponent->SetPosition(m_FixPosition);
	}
	m_pState->Update();
}
