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

dae::MrPepperComponent::MrPepperComponent(GameObject* pOwner)
	:Component(pOwner)
	, m_pPlayerControllerComponent{ GetOwner()->GetComponent<PlayerControllerComponent>() }
	, m_pCollisionComponent(GetOwner()->GetComponent<CollisionComponent>())
	, m_pTransformComponent(GetOwner()->GetComponent<TransformComponent>())
	, m_pState(nullptr)
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

	m_pState = std::make_shared<IdleState>(GetOwner());
	m_pPrevState = std::make_shared<IdleState>(GetOwner());
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

	if (m_IsGrounded == false && m_IsOnLadder == false)
	{
		m_pTransformComponent->Translate(m_Gravity * Clock::GetInstance().GetDeltaTime());
	}
	m_pState->Update();
}

void dae::MrPepperComponent::MoveToGround()
{
	m_pTransformComponent->SetPosition(glm::vec2{ m_pTransformComponent->GetPosition().x, m_GroundYPos });
}

void dae::MrPepperComponent::SetState(std::shared_ptr<State> pState)
{
	m_pPrevState = m_pState;
	if (m_pState != nullptr)
	{
		m_pState->OnExit();
	}
	m_pState = pState;
	m_pState->OnEnter();
}