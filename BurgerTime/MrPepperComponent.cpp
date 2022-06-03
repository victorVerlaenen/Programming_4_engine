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
#include "Scene.h"
#include "TileComponent.h"

dae::MrPepperComponent::MrPepperComponent(GameObject* pOwner)
	:Component(pOwner)
	, m_pPlayerControllerComponent{ GetOwner()->GetComponent<PlayerControllerComponent>() }
	, m_pTransformComponent(GetOwner()->GetComponent<TransformComponent>())
	, m_pCollisionComponent(GetOwner()->GetComponent<CollisionComponent>())
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

	const auto objects = GetOwner()->GetScene()->GetObjects();
	for (auto object : objects)
	{
		if (object->GetComponent<TileComponent>() != nullptr)
		{
			m_pTileComponents.emplace_back(object->GetComponent<TileComponent>());
			m_pTileColliders.emplace_back(object->GetComponent<CollisionComponent>());
		}
	}
}

void dae::MrPepperComponent::Update()
{
	CheckForWorldCollision();
	if (m_IsGrounded == false && m_IsOnLadder == false)
	{
		m_pTransformComponent->Translate(m_Gravity * Clock::GetInstance().GetDeltaTime());
	}
	m_pState->Update();
	//std::cout << "Trans Pos: " << GetOwner()->GetComponent<TransformComponent>()->GetPosition().x << ", " << GetOwner()->GetComponent<TransformComponent>()->GetPosition().y << std::endl;
}

void dae::MrPepperComponent::FixedUpdate()
{
	
}

void dae::MrPepperComponent::Render() const
{
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

void dae::MrPepperComponent::CheckForWorldCollision()
{
	bool ladder = false;
	bool grounded = false;
	bool colliding = false;
	bool cantClimbDown = true;
	for (size_t i{}; i < m_pTileColliders.size(); i++)
	{
		if (m_pTileColliders[i]->IsOverlapping(m_pCollisionComponent->GetShape()))
		{
			if (m_pTileComponents[i]->GetTileType() != TileType::Ladder)
			{

				if (std::abs(m_pTransformComponent->GetPosition().y - m_pTileColliders[i]->GetShape().yPos) <= m_pTileComponents[i]->GetPlatformMargin()*2)
				{
					if (m_pTileComponents[i]->GetTileType() == TileType::LadderPlatform)
					{
						cantClimbDown = false;
					}
					grounded = true;
					m_GroundYPos = static_cast<float>(m_pTileColliders[i]->GetShape().yPos + m_pTileComponents[i]->GetPlatformMargin());
				}
			}

			if (m_pTileComponents[i]->GetTileType() == TileType::LadderPlatform || m_pTileComponents[i]->GetTileType() == TileType::Ladder)
			{
				if (m_pCollisionComponent->IsBetween(m_pTileColliders[i]->GetShape()))
				{
					ladder = true;

				}
			}
			colliding = true;
		}
	}
	if (grounded == false)
	{
		cantClimbDown = false;
	}
	m_CantClimbdown = cantClimbDown;
	SetIsGrounded(grounded);
	SetIsOnLadder(ladder);
	if (colliding == false)
	{
		SetState(std::make_shared<IdleState>(GetOwner()));
	}
}