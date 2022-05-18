#include "MiniginPCH.h"
#include "Command.h"
#include "GameObject.h"

dae::Command::Command(GameObject* actor)
	:m_Actor{actor}
{
	
}

dae::GameObject* dae::Command::GetActor() const
{
	return m_Actor;
}
