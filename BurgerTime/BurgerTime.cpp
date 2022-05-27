#include "BurgerTimePCH.h"
#include "BurgerTime.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"

#include "Component.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "ImGuiComponent.h"
#include "PlayerControllerComponent.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include "MrPepperComponent.h"

#include "DieCommand.h"
#include "PointsCommand.h"

void dae::BurgerTime::LoadBurgerTime()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//TextureObject
	const auto textureObject = std::make_shared<GameObject>();
	textureObject->AddComponent(new TransformComponent{ textureObject.get(), glm::vec2{216,180} });
	textureObject->AddComponent(new RenderComponent{ textureObject.get(), "logo.png" });
	scene.Add(textureObject);

	//TextObject
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto textObject = std::make_shared<GameObject>();
	textObject->AddComponent(new TransformComponent{ textObject.get(), glm::vec2{80,20} });
	textObject->AddComponent(new RenderComponent{ textObject.get() });
	textObject->AddComponent(new TextComponent{ textObject.get() , font, SDL_Color{255, 255, 255},"Programming 4 Assignment" });
	scene.Add(textObject);

	//FPSCounterObject
	const auto FPSCounterObject = std::make_shared<GameObject>();
	const auto fontFPS = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	FPSCounterObject->AddComponent(new TransformComponent{ FPSCounterObject.get(), glm::vec2{10,10} });
	FPSCounterObject->AddComponent(new RenderComponent{ FPSCounterObject.get() });
	FPSCounterObject->AddComponent(new TextComponent{ FPSCounterObject.get() , fontFPS, SDL_Color{255, 255, 0} });
	FPSCounterObject->AddComponent(new FPSComponent{ FPSCounterObject.get() });
	scene.Add(FPSCounterObject);

	//ImGuiObject
	const auto imGuiObject = std::make_shared<GameObject>();
	imGuiObject->AddComponent(new ImGuiComponent{ imGuiObject.get(), m_Window });
	scene.Add(imGuiObject);


	////////////
	// PLAYER 1
	// ************
	//LivesDisplayObject
	const auto livesObject = std::make_shared<GameObject>();
	livesObject->AddComponent(new TransformComponent{ livesObject.get(), glm::vec2{10, m_WindowHeight - 80} });
	livesObject->AddComponent(new RenderComponent{ livesObject.get() });
	livesObject->AddComponent(new TextComponent{ livesObject.get(), fontFPS, SDL_Color{255, 255, 0} });
	auto pLivesComponent = livesObject->AddComponent(new LivesComponent{ livesObject.get() });
	scene.Add(livesObject);

	//ScoreDisplayObject
	const auto scoreObject = std::make_shared<GameObject>();
	scoreObject->AddComponent(new TransformComponent{ scoreObject.get(), glm::vec2{10, m_WindowHeight - 60} });
	scoreObject->AddComponent(new RenderComponent{ scoreObject.get() });
	scoreObject->AddComponent(new TextComponent{ scoreObject.get(), fontFPS, SDL_Color{255, 255, 0} });
	auto pScoreComponent = scoreObject->AddComponent(new ScoreComponent{ scoreObject.get() });
	scene.Add(scoreObject);

	//PlayerOneObject
	const auto playerOneObject = std::make_shared<GameObject>();
	auto pPlayerControllerComponent = playerOneObject->AddComponent(new PlayerControllerComponent{ playerOneObject.get() });
	pPlayerControllerComponent->AddCommand(ButtonState::Down, ControllerButton::X, std::make_unique<PointsCommand>(playerOneObject.get()));
	pPlayerControllerComponent->AddCommand(ButtonState::Down, ControllerButton::A, std::make_unique<DieCommand>(playerOneObject.get()));
	auto pMrPepperComponent = playerOneObject->AddComponent(new MrPepperComponent{ playerOneObject.get() });
	pMrPepperComponent->AddObserver(pLivesComponent);
	pMrPepperComponent->AddObserver(pScoreComponent);
	scene.Add(playerOneObject);

	////////////
	// PLAYER 2
	// ************
	//LivesDisplayObject
	const auto lives2Object = std::make_shared<GameObject>();
	lives2Object->AddComponent(new TransformComponent{ lives2Object.get(), glm::vec2{10, m_WindowHeight - 40} });
	lives2Object->AddComponent(new RenderComponent{ lives2Object.get() });
	lives2Object->AddComponent(new TextComponent{ lives2Object.get(), fontFPS, SDL_Color{0, 255, 0} });
	auto pLives2Component = lives2Object->AddComponent(new LivesComponent{ lives2Object.get() });
	scene.Add(lives2Object);

	//ScoreDisplayObject
	const auto score2Object = std::make_shared<GameObject>();
	score2Object->AddComponent(new TransformComponent{ score2Object.get(), glm::vec2{10, m_WindowHeight - 20} });
	score2Object->AddComponent(new RenderComponent{ score2Object.get() });
	score2Object->AddComponent(new TextComponent{ score2Object.get(), fontFPS, SDL_Color{0, 255, 0} });
	auto pScore2Component = score2Object->AddComponent(new ScoreComponent{ score2Object.get() });
	scene.Add(score2Object);

	//PlayerOneObject
	const auto playerTwoObject = std::make_shared<GameObject>();
	auto pPlayerTwoControllerComponent = playerTwoObject->AddComponent(new PlayerControllerComponent{ playerTwoObject.get() });
	pPlayerTwoControllerComponent->AddCommand(ButtonState::Down, ControllerButton::X, std::make_unique<PointsCommand>(playerOneObject.get()));
	pPlayerTwoControllerComponent->AddCommand(ButtonState::Down, ControllerButton::A, std::make_unique<DieCommand>(playerOneObject.get()));
	auto pMrPepper2Component = playerTwoObject->AddComponent(new MrPepperComponent{ playerTwoObject.get() });
	pMrPepper2Component->AddObserver(pLives2Component);
	pMrPepper2Component->AddObserver(pScore2Component);
	scene.Add(playerTwoObject);
}
