#include "BurgerTimePCH.h"
#include "DieCommand.h"

#include "AudioSystem.h"
#include "GameObject.h"
#include "MrPepperComponent.h"
#include "ServiceLocator.h"

dae::DieCommand::DieCommand(GameObject* actor)
	:Command(actor)
{
}

void dae::DieCommand::Execute()
{
	GetActor()->GetComponent<MrPepperComponent>()->Notify(GetActor(), Observer::Event::EVENT_ACTOR_DIED);
	ServiceLocator::GetAudioSystem().RegisterSound("Lose_Life.mp3");
}
