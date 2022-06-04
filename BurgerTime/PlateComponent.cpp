#include "BurgerTimePCH.h"
#include "PlateComponent.h"
#include "CollisionComponent.h"

std::vector<dae::PlateComponent*> dae::PlateComponent::m_pPlateComponents = {};

dae::PlateComponent::PlateComponent(GameObject* pOwner)
	:Component(pOwner)
	, m_pCollisionComponent(pOwner->GetComponent<CollisionComponent>())
{
	m_pPlateComponents.push_back(this);
}
