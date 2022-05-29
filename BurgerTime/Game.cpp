#include "BurgerTimePCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "BurgerTime.h"

int main(int, char* [])
{
	dae::Minigin engine;
	dae::BurgerTime game;


	engine.Run([ObjectPtr = &game] { ObjectPtr->LoadBurgerTime(); });

	return 0;
}