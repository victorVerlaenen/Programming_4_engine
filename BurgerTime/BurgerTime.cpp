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

	//AddDAELogo(scene);
	//AddText(scene, "Programming 4 Assignment", glm::vec2{ 80,20 }, SDL_Color{ 255, 255, 255 }, 36);

	AddFPSCounter(scene, glm::vec2{ 10,10 }, SDL_Color{ 255, 255, 0 });

	AddPlayerOne(scene);
	//AddPlayerTwo(scene);

	//ImGuiObject
	/*const auto imGuiObject = std::make_shared<GameObject>();
	imGuiObject->AddComponent(new ImGuiComponent{ imGuiObject.get(), m_Window });
	scene.Add(imGuiObject);*/
}

void dae::BurgerTime::AddDAELogo(Scene& scene) const
{
	const auto textureObject = std::make_shared<GameObject>();
	textureObject->AddComponent(new TransformComponent{ textureObject.get(), glm::vec2{216,180} });
	textureObject->AddComponent(new RenderComponent{ textureObject.get(), RenderComponent::RenderMode::LeftTop, "logo.png" });
	scene.Add(textureObject);
}

void dae::BurgerTime::AddText(Scene& scene, const std::string& text, const glm::vec2& pos, const SDL_Color& textColor, unsigned int fontSize) const
{
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", fontSize);
	const auto textObject = std::make_shared<GameObject>();
	textObject->AddComponent(new TransformComponent{ textObject.get(), pos });
	textObject->AddComponent(new RenderComponent{ textObject.get() });
	textObject->AddComponent(new TextComponent{ textObject.get() , font, textColor, text });
	scene.Add(textObject);
}

void dae::BurgerTime::AddFPSCounter(Scene& scene, const glm::vec2& pos, const SDL_Color& textColor) const
{
	const auto FPSCounterObject = std::make_shared<GameObject>();
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	FPSCounterObject->AddComponent(new TransformComponent{ FPSCounterObject.get(), pos });
	FPSCounterObject->AddComponent(new RenderComponent{ FPSCounterObject.get() });
	FPSCounterObject->AddComponent(new TextComponent{ FPSCounterObject.get() , font, textColor });
	FPSCounterObject->AddComponent(new FPSComponent{ FPSCounterObject.get() });
	scene.Add(FPSCounterObject);
}

void dae::BurgerTime::AddPlayerOne(Scene& scene) const
{
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//LivesDisplayObject
	const auto livesObject = std::make_shared<GameObject>();
	livesObject->AddComponent(new TransformComponent{ livesObject.get(), glm::vec2{10, m_WindowHeight - 10} });
	livesObject->AddComponent(new RenderComponent{ livesObject.get(), RenderComponent::RenderMode::LeftBottom });
	auto pLivesComponent = livesObject->AddComponent(new LivesComponent{ livesObject.get() });
	scene.Add(livesObject);

	//ScoreDisplayObject
	const auto scoreObject = std::make_shared<GameObject>();
	scoreObject->AddComponent(new TransformComponent{ scoreObject.get(), glm::vec2{m_WindowWidth/2 - 20, 10} });
	scoreObject->AddComponent(new RenderComponent{ scoreObject.get(), RenderComponent::RenderMode::LeftTop });
	scoreObject->AddComponent(new TextComponent{ scoreObject.get(), font, SDL_Color{0, 255, 0} });
	auto pScoreComponent = scoreObject->AddComponent(new ScoreComponent{ scoreObject.get() });
	scene.Add(scoreObject);

	//PlayerOneObject
	const auto playerObject = std::make_shared<GameObject>();
	playerObject->AddComponent(new PlayerControllerComponent{ playerObject.get() });
	auto pMrPepperComponent = playerObject->AddComponent(new MrPepperComponent{ playerObject.get() });
	pMrPepperComponent->AddObserver(pLivesComponent);
	pMrPepperComponent->AddObserver(pScoreComponent);
	scene.Add(playerObject);
}

void dae::BurgerTime::AddPlayerTwo(Scene& scene) const
{
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//LivesDisplayObject
	const auto livesObject = std::make_shared<GameObject>();
	livesObject->AddComponent(new TransformComponent{ livesObject.get(), glm::vec2{10, m_WindowHeight - 90} });
	livesObject->AddComponent(new RenderComponent{ livesObject.get() });
	livesObject->AddComponent(new TextComponent{ livesObject.get(), font, SDL_Color{255, 255, 0} });
	auto pLivesComponent = livesObject->AddComponent(new LivesComponent{ livesObject.get() });
	scene.Add(livesObject);

	//ScoreDisplayObject
	const auto scoreObject = std::make_shared<GameObject>();
	scoreObject->AddComponent(new TransformComponent{ scoreObject.get(), glm::vec2{10, m_WindowHeight - 70} });
	scoreObject->AddComponent(new RenderComponent{ scoreObject.get() });
	scoreObject->AddComponent(new TextComponent{ scoreObject.get(), font, SDL_Color{255, 255, 0} });
	auto pScoreComponent = scoreObject->AddComponent(new ScoreComponent{ scoreObject.get() });
	scene.Add(scoreObject);

	//PlayerOneObject
	const auto playerObject = std::make_shared<GameObject>();
	playerObject->AddComponent(new PlayerControllerComponent{ playerObject.get() });
	auto pMrPepperComponent = playerObject->AddComponent(new MrPepperComponent{ playerObject.get() });
	pMrPepperComponent->AddObserver(pLivesComponent);
	pMrPepperComponent->AddObserver(pScoreComponent);
	scene.Add(playerObject);
}