#include "MiniginPCH.h"
#include "Component.h"

Component::Component(std::shared_ptr<dae::GameObject> pOwner)
	:m_pOwner{pOwner}
{
	
}