#include "BurgerTimePCH.h"
#include "BurgerTime.h"
#include <fstream>

#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "IngredientComponent.h"
#include "PlayerControllerComponent.h"
#include "LivesComponent.h"
#include "LoggedAudioSystem.h"
#include "ScoreComponent.h"
#include "MrPepperComponent.h"
#include "NullAudioSystem.h"
#include "PlateComponent.h"
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
	
	LoadMap(scene, "Map_1.txt");
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


std::shared_ptr<dae::GameObject> dae::BurgerTime::AddPlayer(Scene& scene, LivesComponent* pLivesComponent, const glm::vec2& pos) const
{
	//PlayerOneObject
	auto playerObject = std::make_shared<GameObject>(&scene);
	playerObject->AddComponent(new TransformComponent{ playerObject.get(),pos });
	//playerObject->AddComponent(new RenderComponent{ playerObject.get(), 3, RenderMode::CenterBottom, "Idle.png" });
	playerObject->AddComponent(new SpriteRenderComponent{ playerObject.get(), "Idle.png", 1, 1, 3, RenderMode::CenterBottom });
	playerObject->AddComponent(new CollisionComponent{ playerObject.get() });
	playerObject->AddComponent(new PlayerControllerComponent{ playerObject.get() });
	const auto pMrPepperComponent = playerObject->AddComponent(new MrPepperComponent{ playerObject.get(), true });
	pMrPepperComponent->AddObserver(pLivesComponent);
	scene.Add(playerObject, 2);

	return playerObject;
}

void dae::BurgerTime::AddEnemy(Scene& scene, LivesComponent* pLivesComponent, const glm::vec2& pos) const
{
	auto enemyObject = std::make_shared<GameObject>(&scene);
	enemyObject->AddComponent(new TransformComponent{ enemyObject.get(),pos });
	enemyObject->AddComponent(new SpriteRenderComponent{ enemyObject.get(), "Idle.png", 1, 1, 3, RenderMode::CenterBottom });
	enemyObject->AddComponent(new CollisionComponent{ enemyObject.get() });
	const auto enemyComponent = enemyObject->AddComponent(new EnemyComponent{ enemyObject.get(), false });
	enemyComponent->AddObserver(pLivesComponent);
	scene.Add(enemyObject, 2);
}

std::shared_ptr<dae::GameObject> dae::BurgerTime::AddLivesDisplay(Scene& scene) const
{
	//LivesDisplayObject
	auto livesObject = std::make_shared<GameObject>(&scene);
	livesObject->AddComponent(new TransformComponent{ livesObject.get(), glm::vec2{10, m_WindowHeight - 10} });
	livesObject->AddComponent(new RenderComponent{ livesObject.get(), 3, RenderMode::LeftBottom });
	livesObject->AddComponent(new LivesComponent{ livesObject.get() });
	scene.Add(livesObject);

	return livesObject;
}

std::shared_ptr<dae::GameObject> dae::BurgerTime::AddScoreDisplay(Scene& scene) const
{
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//ScoreDisplayObject
	auto scoreObject = std::make_shared<GameObject>(&scene);
	scoreObject->AddComponent(new TransformComponent{ scoreObject.get(), glm::vec2{m_WindowWidth / 2 - 20, 10} });
	scoreObject->AddComponent(new RenderComponent{ scoreObject.get(), 1, RenderMode::LeftTop });
	scoreObject->AddComponent(new TextComponent{ scoreObject.get(), font, SDL_Color{0, 255, 0} });
	scoreObject->AddComponent(new ScoreComponent{ scoreObject.get() });
	scene.Add(scoreObject);

	return scoreObject;
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
	auto pMrPepperComponent = playerObject->AddComponent(new MrPepperComponent{ playerObject.get(), true });
	pMrPepperComponent->AddObserver(pLivesComponent);
	pMrPepperComponent->AddObserver(pScoreComponent);
	scene.Add(playerObject);
}

void dae::BurgerTime::LoadMap(Scene& scene, const std::string& mapFile) const
{
	const auto pScoreObject = AddScoreDisplay(scene);
	const auto pLivesObject = AddLivesDisplay(scene);

	auto pScoreComponent = pScoreObject->GetComponent<ScoreComponent>();
	auto pLivesComponent = pLivesObject->GetComponent<LivesComponent>();

	std::shared_ptr<GameObject> pPlayerObject;

	auto inputFile = ResourceManager::GetInstance().LoadFile(mapFile);
	std::string line;

	glm::vec2 tileWidth;
	glm::vec2 tileHeight;
	glm::vec2 prevPos;
	auto tileType{ TileType::NormalPlatform };
	glm::vec2 startPos;

	if (!inputFile.is_open())
	{
		std::cout << "Could not open file: " << mapFile << std::endl;
		return;
	}

	while (std::getline(inputFile, line))
	{
		if (line == "TopBun")
		{
			AddIngredient(scene, prevPos + (tileWidth / 2.f), Ingedient::TopBun, pPlayerObject.get(), pScoreComponent);
			continue;
		}
		if (line == "Lettuce")
		{
			AddIngredient(scene, prevPos + (tileWidth / 2.f), Ingedient::Lettuce, pPlayerObject.get(), pScoreComponent);
			continue;
		}
		if (line == "Patty")
		{
			AddIngredient(scene, prevPos + (tileWidth / 2.f), Ingedient::Patty, pPlayerObject.get(), pScoreComponent);
			continue;
		}
		if (line == "BottomBun")
		{
			AddIngredient(scene, prevPos + (tileWidth / 2.f), Ingedient::BottomBun, pPlayerObject.get(), pScoreComponent);
			continue;
		}
		if (line == "Plate")
		{
			AddPlate(scene, glm::vec2{ prevPos.x + (tileWidth.x / 2.f), m_WindowHeight - 10 });
			continue;
		}
		std::string tempReader, offsetType, amount;
		std::istringstream lineStream{ line };
		while (std::getline(lineStream, tempReader, ';'))
		{
			if (tempReader == "w" || tempReader == "h" || tempReader == "hw" || tempReader == "b" || tempReader == "p" || tempReader == "e")
			{
				offsetType = tempReader;
				continue;
			}
			if (tempReader == "NormalPlatform")
			{
				tileType = TileType::NormalPlatform;
				continue;
			}
			if (tempReader == "LadderPlatform")
			{
				tileType = TileType::LadderPlatform;
				continue;
			}
			if (tempReader == "Ladder")
			{
				tileType = TileType::Ladder;
				continue;
			}
			amount = tempReader;
		}

		if (offsetType == "b")
		{
			startPos.x = std::stof(amount.substr(0, amount.find(',')));
			startPos.y = std::stof(amount.substr(amount.find(',') + 1));

			const auto firstPlatform = std::make_shared<GameObject>(&scene);
			const auto platformTransform = firstPlatform->AddComponent(new TransformComponent{ firstPlatform.get(), startPos });
			const auto platformRender = firstPlatform->AddComponent(new RenderComponent{ firstPlatform.get(), 3 });
			firstPlatform->AddComponent(new CollisionComponent{ firstPlatform.get() });
			firstPlatform->AddComponent(new TileComponent{ firstPlatform.get(), tileType });
			scene.Add(firstPlatform);

			tileWidth = glm::vec2{ platformRender->GetTextureWidth(),0 };
			tileHeight = glm::vec2{ 0,platformRender->GetTextureHeight() };

			prevPos = platformTransform->GetPosition();
			continue;
		}
		if(offsetType == "p")
		{
			pPlayerObject = AddPlayer(scene, pLivesComponent, glm::vec2{ std::stof(amount.substr(0, amount.find(','))) ,std::stof(amount.substr(amount.find(',') + 1)) });
			continue;
		}
		if (offsetType == "e")
		{
			AddEnemy(scene, pLivesComponent, glm::vec2{ std::stof(amount.substr(0, amount.find(','))) ,std::stof(amount.substr(amount.find(',') + 1)) });
			continue;
		}
		if (offsetType == "w")
		{
			prevPos = AddPlatform(scene, prevPos + (tileWidth * std::stof(amount)), tileType);
			continue;
		}
		if (offsetType == "h")
		{
			prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + (tileHeight * std::stof(amount)), tileType);
			continue;
		}
		if (offsetType == "hw")
		{
			prevPos = AddPlatform(scene, glm::vec2{ startPos.x ,prevPos.y } + tileHeight + (tileWidth * std::stof(amount)), tileType);
		}
	}
	ServiceLocator::GetAudioSystem().PlaySound("Main_Track.mp3", true);
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

void dae::BurgerTime::AddPlate(Scene& scene, const glm::vec2& pos) const
{
	const auto plate = std::make_shared<GameObject>(&scene);
	plate->AddComponent(new TransformComponent{ plate.get(), pos });
	plate->AddComponent(new RenderComponent{ plate.get(), 3, RenderMode::CenterBottom, "Plate.png" });
	plate->AddComponent(new CollisionComponent{ plate.get() });
	plate->AddComponent(new PlateComponent{ plate.get() });
	scene.Add(plate);
}

void dae::BurgerTime::AddIngredient(Scene& scene, const glm::vec2& pos, Ingedient type, GameObject* pPlayerObject, ScoreComponent* pScoreComponent) const
{
	const auto ingredient = std::make_shared<GameObject>(&scene);
	ingredient->AddComponent(new TransformComponent{ ingredient.get(),pos });
	ingredient->AddComponent(new RenderComponent{ ingredient.get(), 3, RenderMode::CenterBottom });
	ingredient->AddComponent(new CollisionComponent{ ingredient.get() });
	const auto ingredientComp = ingredient->AddComponent(new IngredientComponent{ ingredient.get(), pPlayerObject, type });
	ingredientComp->AddObserver(pScoreComponent);
	scene.Add(ingredient, 1);
}
