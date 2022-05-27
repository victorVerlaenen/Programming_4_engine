#include "BurgerTimePCH.h"
#include "MoveCommand.h"

#include "GameObject.h"
#include "TransformComponent.h"

dae::MoveCommand::MoveCommand(GameObject* actor)
	:Command(actor)
{
}

void dae::MoveCommand::Execute()
{

}
