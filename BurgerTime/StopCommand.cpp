#include "BurgerTimePCH.h"
#include "StopCommand.h"

#include "GameObject.h"
#include "IdleState.h"
#include "MrPepperComponent.h"

dae::StopCommand::StopCommand(GameObject* actor)
	:Command(actor)
	//, m_pMrPepperComponent(actor->GetComponent<MrPepperComponent>())
{
}

void dae::StopCommand::Execute()
{
	GetActor()->GetComponent<MrPepperComponent>()->SetState(std::make_shared<IdleState>(GetActor()));
}
