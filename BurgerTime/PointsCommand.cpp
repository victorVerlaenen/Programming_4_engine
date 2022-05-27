#include "BurgerTimePCH.h"
#include "PointsCommand.h"
#include "MrPepperComponent.h"

dae::PointsCommand::PointsCommand(GameObject* actor)
	:Command(actor)
{
}

void dae::PointsCommand::Execute()
{
	GetActor()->GetComponent<MrPepperComponent>()->Notify(GetActor(), Observer::Event::EVENT_PLAYER_POINTS);
}