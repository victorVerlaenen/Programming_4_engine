#include "BurgerTimePCH.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
#include "EnemyMoveState.h"
#include "IdleState.h"
#include "Scene.h"
#include "State.h"
#include "TransformComponent.h"


dae::EnemyComponent::EnemyComponent(GameObject* pOwner, bool isPlayer)
	:ActorComponent(pOwner, isPlayer)
{
	for (const auto actor : m_pActorComponents)
	{
		if (actor->GetIsPlayer() == true)
		{
			m_pPlayerColliders.push_back(actor->GetCollider());
			m_pPlayerTransforms.push_back(actor->GetTransform());
		}
	}
}

void dae::EnemyComponent::Update()
{


}

void dae::EnemyComponent::LateUpdate()
{
	if (m_IsGrounded == false)
	{
		m_CantClimbdown = false;
	}
	if (m_Colliding == false)
	{

	}

	if (m_IsPastPlatform == true)
	{
		m_pTransformComponent->SetPosition(m_FixPosition);
		if (m_pState->GetType() == "MoveLeft")
		{
			SetState(std::make_shared<EnemyMoveState>(GetOwner(), MoveDirection::Right, 60.f));
		}
		else
		{
			SetState(std::make_shared<EnemyMoveState>(GetOwner(), MoveDirection::Left, 60.f));
		}
	}

	SetMovementDirection();

	m_pState->Update();
}

void dae::EnemyComponent::SetMovementDirection()
{
	m_Timer += Clock::GetInstance().GetDeltaTime();
	if (m_Timer >= m_ChangeCooldown)
	{
		for (const auto playerTransform : m_pPlayerTransforms)
		{
			//if enemy hits middle of player
			if (m_pCollisionComponent->IsOverlapping(playerTransform->GetPosition() - glm::vec2{ 0, m_pPlayerColliders[0]->GetShape().height / 2 }))
			{
				Notify(GetOwner(), Observer::Event::EVENT_ACTOR_DIED);
			}
			//only change state when platform is reached
			if (m_IsGrounded == true)
			{
				if (m_IsOnLadder == true)
				{
					// Player is above enemy
					if (m_pTransformComponent->GetPosition().y > playerTransform->GetPosition().y + 10 && m_CantClimbUp == false)
					{
						if (m_pState->GetType() != "MoveDown")
						{
							SetState(std::make_shared<EnemyMoveState>(GetOwner(), MoveDirection::Up, 60.f));
							std::cout << "Move Up\n";
							m_Timer = 0;
							break;
						}
					}
					// Player is below enemy
					if (m_pTransformComponent->GetPosition().y < playerTransform->GetPosition().y - 10 && m_CantClimbdown == false)
					{
						if (m_pState->GetType() != "MoveUp")
						{
							SetState(std::make_shared<EnemyMoveState>(GetOwner(), MoveDirection::Down, 60.f));
							std::cout << "Move Down\n";
							m_Timer = 0;
							break;
						}
					}
				}

				
				if (m_pState->GetType() != "MoveLeft" && m_pState->GetType() != "MoveRight")
				{
					if (m_pTransformComponent->GetPosition().x > playerTransform->GetPosition().x)// Player is left of enemy
					{

						SetState(std::make_shared<EnemyMoveState>(GetOwner(), MoveDirection::Left, 60.f));
						MoveToGround();
						std::cout << "Move Left\n";
						m_Timer = 0;
						break;
					}
					if (m_pTransformComponent->GetPosition().x < playerTransform->GetPosition().x)// Player is right of enemy
					{

						SetState(std::make_shared<EnemyMoveState>(GetOwner(), MoveDirection::Right, 60.f));
						MoveToGround();
						std::cout << "Move Right\n";
						m_Timer = 0;
						break;
					}
				}
			}
		}
	}
}