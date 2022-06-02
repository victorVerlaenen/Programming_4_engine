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
	auto mrPepperComp = GetActor()->GetComponent<MrPepperComponent>();
	/*if (mrPepperComp->GetPrevState()->GetType() == "Move" && mrPepperComp->GetState()->GetType() == "Move")
	{
		return;
	}*/
	mrPepperComp->SetState(std::make_shared<IdleState>(GetActor()));
}
