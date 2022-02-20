#include "MiniginPCH.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(dae::GameObject* pOwner)
{
	m_pOwner = pOwner;
}