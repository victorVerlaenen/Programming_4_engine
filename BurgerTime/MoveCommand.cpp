#include "BurgerTimePCH.h"
#include "MoveCommand.h"

#include "GameObject.h"
#include "MoveState.h"
#include "MrPepperComponent.h"

dae::MoveCommand::MoveCommand(GameObject* actor, MoveDirection moveDirection)
	:Command(actor)
	, m_MoveDirection(moveDirection)
	//, m_pMrPepperComponent(actor->GetComponent<MrPepperComponent>())
{
}

void dae::MoveCommand::Execute()
{
	auto mrPepperComp = GetActor()->GetComponent<MrPepperComponent>();
	mrPepperComp->SetState(std::make_shared<MoveState>(GetActor(), m_MoveDirection, 80.f));
}
