#include "BurgerTimePCH.h"
#include "DieCommand.h"
#include "GameObject.h"
#include "MrPepperComponent.h"

dae::DieCommand::DieCommand(GameObject* actor)
	:Command(actor)
{
}

void dae::DieCommand::Execute()
{
	GetActor()->GetComponent<MrPepperComponent>()->Notify(GetActor(), Observer::Event::EVENT_ACTOR_DIED);
}
