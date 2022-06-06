#include "BurgerTimePCH.h"
#include "ActorComponent.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "IdleState.h"
#include "State.h"

std::vector<dae::ActorComponent*> dae::ActorComponent::m_pActorComponents = {};

dae::ActorComponent::ActorComponent(GameObject* pOwner, bool isPlayer)
	:Component(pOwner)
	, m_pCollisionComponent(GetOwner()->GetComponent<CollisionComponent>())
	, m_pTransformComponent(GetOwner()->GetComponent<TransformComponent>())
	, m_pState(std::make_shared<IdleState>(pOwner))
	, m_pPrevState(std::make_shared<IdleState>(pOwner))
	, m_IsPlayer(isPlayer)
{
	m_pActorComponents.push_back(this);
	m_StartingPos = m_pTransformComponent->GetPosition();
}


void dae::ActorComponent::MoveToGround()
{
	m_pTransformComponent->SetPosition(glm::vec2{ m_pTransformComponent->GetPosition().x, m_GroundYPos });
}

void dae::ActorComponent::Reset()
{
	m_pTransformComponent->SetPosition(m_StartingPos);
}

void dae::ActorComponent::SetState(std::shared_ptr<State> pState)
{
	m_pPrevState = m_pState;
	if (m_pState != nullptr)
	{
		m_pState->OnExit();
	}
	m_pState = pState;
	m_pState->OnEnter();
}
