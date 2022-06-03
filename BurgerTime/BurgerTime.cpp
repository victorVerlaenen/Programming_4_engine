#include "BurgerTimePCH.h"
#include "BurgerTime.h"

#include "CollisionComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "PlayerControllerComponent.h"
#include "LivesComponent.h"
#include "LoggedAudioSystem.h"
#include "ScoreComponent.h"
#include "MrPepperComponent.h"
#include "NullAudioSystem.h"
#include "ServiceLocator.h"
#include "SpriteRenderComponent.h"
#include "StandardAudioSystem.h"
#include "TileComponent.h"


dae::BurgerTime::BurgerTime()
{
	ServiceLocator::Initialize();
	ServiceLocator::RegisterAudioSystem(new StandardAudioSystem{});
	//ServiceLocator::RegisterAudioSystem(new LoggedAudioSystem{});
}

dae::BurgerTime::~BurgerTime()
{
	ServiceLocator::CleanUp();
}

void dae::BurgerTime::LoadBurgerTime() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	AddFPSCounter(scene, glm::vec2{ 10,10 }, SDL_Color{ 255, 255, 0 });

	AddPlatforms(scene);
	AddPlayerOne(scene);
	//AddPlayerTwo(scene);


	//ImGuiObject
	/*const auto imGuiObject = std::make_shared<GameObject>();
	imGuiObject->AddComponent(new ImGuiComponent{ imGuiObject.get(), m_Window });
	scene.Add(imGuiObject);*/
}

void dae::BurgerTime::AddDAELogo(Scene& scene) const
{
	const auto textureObject = std::make_shared<GameObject>(&scene);
	textureObject->AddComponent(new TransformComponent{ textureObject.get(), glm::vec2{216,180} });
	textureObject->AddComponent(new RenderComponent{ textureObject.get(), 1, RenderMode::LeftTop, "logo.png" });
	scene.Add(textureObject);
}

void dae::BurgerTime::AddText(Scene& scene, const std::string& text, const glm::vec2& pos, const SDL_Color& textColor, unsigned int fontSize) const
{
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", fontSize);
	const auto textObject = std::make_shared<GameObject>(&scene);
	textObject->AddComponent(new TransformComponent{ textObject.get(), pos });
	textObject->AddComponent(new RenderComponent{ textObject.get() });
	textObject->AddComponent(new TextComponent{ textObject.get() , font, textColor, text });
	scene.Add(textObject);
}

void dae::BurgerTime::AddFPSCounter(Scene& scene, const glm::vec2& pos, const SDL_Color& textColor) const
{
	const auto FPSCounterObject = std::make_shared<GameObject>(&scene);
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	FPSCounterObject->AddComponent(new TransformComponent{ FPSCounterObject.get(), pos });
	FPSCounterObject->AddComponent(new RenderComponent{ FPSCounterObject.get() });
	FPSCounterObject->AddComponent(new TextComponent{ FPSCounterObject.get() , font, textColor });
	FPSCounterObject->AddComponent(new FPSComponent{ FPSCounterObject.get() });
	scene.Add(FPSCounterObject);
}

dae::GameObject* dae::BurgerTime::AddPlayerOne(Scene& scene) const
{
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//LivesDisplayObject
	const auto livesObject = std::make_shared<GameObject>(&scene);
	livesObject->AddComponent(new TransformComponent{ livesObject.get(), glm::vec2{10, m_WindowHeight - 10} });
	livesObject->AddComponent(new RenderComponent{ livesObject.get(), 3, RenderMode::LeftBottom });
	auto pLivesComponent = livesObject->AddComponent(new LivesComponent{ livesObject.get() });
	scene.Add(livesObject);

	//ScoreDisplayObject
	const auto scoreObject = std::make_shared<GameObject>(&scene);
	scoreObject->AddComponent(new TransformComponent{ scoreObject.get(), glm::vec2{m_WindowWidth / 2 - 20, 10} });
	scoreObject->AddComponent(new RenderComponent{ scoreObject.get(), 1, RenderMode::LeftTop });
	scoreObject->AddComponent(new TextComponent{ scoreObject.get(), font, SDL_Color{0, 255, 0} });
	auto pScoreComponent = scoreObject->AddComponent(new ScoreComponent{ scoreObject.get() });
	scene.Add(scoreObject);

	//PlayerOneObject
	const auto playerObject = std::make_shared<GameObject>(&scene);
	playerObject->AddComponent(new TransformComponent{ playerObject.get(), glm::vec2{62 ,100} });
	//playerObject->AddComponent(new RenderComponent{ playerObject.get(), 3, RenderMode::CenterBottom, "Idle.png" });
	playerObject->AddComponent(new SpriteRenderComponent{ playerObject.get(), "Idle.png", 1, 1, 3, RenderMode::CenterBottom });
	playerObject->AddComponent(new CollisionComponent{ playerObject.get() });
	playerObject->AddComponent(new PlayerControllerComponent{ playerObject.get() });
	auto pMrPepperComponent = playerObject->AddComponent(new MrPepperComponent{ playerObject.get() });
	pMrPepperComponent->AddObserver(pLivesComponent);
	pMrPepperComponent->AddObserver(pScoreComponent);
	scene.Add(playerObject);

	return playerObject.get();
}

void dae::BurgerTime::AddPlayerTwo(Scene& scene) const
{
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//LivesDisplayObject
	const auto livesObject = std::make_shared<GameObject>(&scene);
	livesObject->AddComponent(new TransformComponent{ livesObject.get(), glm::vec2{10, m_WindowHeight - 90} });
	livesObject->AddComponent(new RenderComponent{ livesObject.get() });
	livesObject->AddComponent(new TextComponent{ livesObject.get(), font, SDL_Color{255, 255, 0} });
	auto pLivesComponent = livesObject->AddComponent(new LivesComponent{ livesObject.get() });
	scene.Add(livesObject);

	//ScoreDisplayObject
	const auto scoreObject = std::make_shared<GameObject>(&scene);
	scoreObject->AddComponent(new TransformComponent{ scoreObject.get(), glm::vec2{10, m_WindowHeight - 70} });
	scoreObject->AddComponent(new RenderComponent{ scoreObject.get() });
	scoreObject->AddComponent(new TextComponent{ scoreObject.get(), font, SDL_Color{255, 255, 0} });
	auto pScoreComponent = scoreObject->AddComponent(new ScoreComponent{ scoreObject.get() });
	scene.Add(scoreObject);

	//PlayerOneObject
	const auto playerObject = std::make_shared<GameObject>(&scene);
	playerObject->AddComponent(new PlayerControllerComponent{ playerObject.get() });
	auto pMrPepperComponent = playerObject->AddComponent(new MrPepperComponent{ playerObject.get() });
	pMrPepperComponent->AddObserver(pLivesComponent);
	pMrPepperComponent->AddObserver(pScoreComponent);
	scene.Add(playerObject);
}

void dae::BurgerTime::AddPlatforms(Scene& scene) const
{
	const glm::vec2 startPos = glm::vec2{ 30 , 100 };

	const auto firstPlatform = std::make_shared<GameObject>(&scene);
	const auto platformTransform = firstPlatform->AddComponent(new TransformComponent{ firstPlatform.get(), startPos });
	const auto platformRender = firstPlatform->AddComponent(new RenderComponent{ firstPlatform.get(), 3 });
	firstPlatform->AddComponent(new CollisionComponent{ firstPlatform.get() });
	firstPlatform->AddComponent(new TileComponent{ firstPlatform.get(), TileType::LadderPlatform });
	scene.Add(firstPlatform);

	const auto tileWidth = glm::vec2{ platformRender->GetTextureWidth(),0 };
	const auto tileHeight = glm::vec2{ 0,platformRender->GetTextureHeight() };

	glm::vec2 prevPos = platformTransform->GetPosition();

	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::LadderPlatform);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 4.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);
	prevPos = AddPlatform(scene, prevPos + (tileWidth * 2.f), TileType::Ladder);

	prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight, TileType::NormalPlaform);
	for (int i{}; i < 17; i++)
	{
		prevPos = AddPlatform(scene, prevPos + tileWidth, TileType::NormalPlaform);
	}
}

glm::vec2 dae::BurgerTime::AddPlatform(Scene& scene, const glm::vec2& pos, TileType type) const
{
	const auto platform = std::make_shared<GameObject>(&scene);
	const auto platformTransform = platform->AddComponent(new TransformComponent{ platform.get(), pos });
	platform->AddComponent(new RenderComponent{ platform.get(), 3 });
	platform->AddComponent(new CollisionComponent{ platform.get() });
	platform->AddComponent(new TileComponent{ platform.get(), type });
	scene.Add(platform);

	return platformTransform->GetPosition();
}

