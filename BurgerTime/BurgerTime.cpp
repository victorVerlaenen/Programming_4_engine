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
	auto playerObj = AddPlayerOne(scene);
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
	scoreObject->AddComponent(new TransformComponent{ scoreObject.get(), glm::vec2{m_WindowWidth/2 - 20, 10} });
	scoreObject->AddComponent(new RenderComponent{ scoreObject.get(), 1, RenderMode::LeftTop });
	scoreObject->AddComponent(new TextComponent{ scoreObject.get(), font, SDL_Color{0, 255, 0} });
	auto pScoreComponent = scoreObject->AddComponent(new ScoreComponent{ scoreObject.get() });
	scene.Add(scoreObject);

	//PlayerOneObject
	const auto playerObject = std::make_shared<GameObject>(&scene);
	playerObject->AddComponent(new TransformComponent{ playerObject.get(), glm::vec2{m_WindowWidth / 2, m_WindowHeight / 2 - 20} });
	//playerObject->AddComponent(new RenderComponent{ playerObject.get(), 3, RenderMode::CenterBottom, "Idle.png" });
	playerObject->AddComponent(new SpriteRenderComponent{ playerObject.get(), "Running.png", 1, 4, 3, RenderMode::CenterBottom });
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
	const auto platform1 = std::make_shared<GameObject>(&scene);
	auto platform1transform = platform1->AddComponent(new TransformComponent{ platform1.get(), glm::vec2{m_WindowWidth / 2 , m_WindowHeight/2} });
	auto platform1Render = platform1->AddComponent(new RenderComponent{ platform1.get(), 3 });
	platform1->AddComponent(new CollisionComponent{ platform1.get()});
	platform1->AddComponent(new TileComponent{ platform1.get(), TileType::NormalPlaform });
	scene.Add(platform1);

	const auto platform2 = std::make_shared<GameObject>(&scene);
	auto platform2transform = platform2->AddComponent(new TransformComponent{ platform2.get(), platform1transform->GetPosition() + glm::vec2{platform1Render->GetTextureWidth() ,0} });
	auto platform2Render = platform2->AddComponent(new RenderComponent{ platform2.get(), 3 });
	platform2->AddComponent(new CollisionComponent{ platform2.get() });
	platform2->AddComponent(new TileComponent{ platform2.get(), TileType::LadderPlatform });
	scene.Add(platform2);

	const auto platform3 = std::make_shared<GameObject>(&scene);
	auto platform3transform = platform3->AddComponent(new TransformComponent{ platform3.get(),  platform2transform->GetPosition() + glm::vec2{0,platform2Render->GetTextureHeight()} });
	auto platform3Render = platform3->AddComponent(new RenderComponent{ platform3.get(), 3 });
	platform3->AddComponent(new CollisionComponent{ platform3.get() });
	platform3->AddComponent(new TileComponent{ platform3.get(), TileType::Ladder });
	scene.Add(platform3);

	const auto platform4 = std::make_shared<GameObject>(&scene);
	auto platform4transform = platform4->AddComponent(new TransformComponent{ platform4.get(),  platform3transform->GetPosition() + glm::vec2{0,platform2Render->GetTextureHeight()} });
	auto platform4Render = platform4->AddComponent(new RenderComponent{ platform4.get(), 3 });
	platform4->AddComponent(new CollisionComponent{ platform4.get() });
	platform4->AddComponent(new TileComponent{ platform4.get(), TileType::Ladder });
	scene.Add(platform4);

	const auto platform5 = std::make_shared<GameObject>(&scene);
	auto platform5transform = platform5->AddComponent(new TransformComponent{ platform5.get(),  platform4transform->GetPosition() + glm::vec2{0,platform2Render->GetTextureHeight()} });
	auto platform5Render = platform5->AddComponent(new RenderComponent{ platform5.get(), 3 });
	platform5->AddComponent(new CollisionComponent{ platform5.get() });
	platform5->AddComponent(new TileComponent{ platform5.get(), TileType::NormalPlaform });
	scene.Add(platform5);
}