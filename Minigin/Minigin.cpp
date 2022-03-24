#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"

#include "TransformComponent.h"
#include "FPSComponent.h"
#include "ImGuiComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		640,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//TextureObject
	auto go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent{ go.get(), glm::vec2{216,180} });
	go->AddComponent(new RenderComponent{ go.get(), "logo.png" });
	scene.Add(go);

	//TextObject
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent{ go.get(), glm::vec2{80,20} });
	go->AddComponent(new RenderComponent{ go.get()});
	go->AddComponent(new TextComponent{ go.get() , font, SDL_Color{255, 255, 255},"Programming 4 Assignment" });
	scene.Add(go);

	//FPSCounterObject
	go = std::make_shared<GameObject>();
	const auto fontFPS = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	go->AddComponent(new TransformComponent{ go.get(), glm::vec2{10,10} });
	go->AddComponent(new RenderComponent{ go.get() });
	go->AddComponent(new TextComponent{ go.get() , fontFPS, SDL_Color{255, 255, 0},"Test" });
	go->AddComponent(new FPSComponent{ go.get() });
	scene.Add(go);

	//ImGuiObject
	go = std::make_shared<GameObject>();
	go->AddComponent(new ImGuiComponent{ go.get(), m_Window });
	scene.Add(go);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		const auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		const auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.f;
		chrono::steady_clock::time_point currentTime{};
		float deltaTime{ 0 };
		while (doContinue)
		{
			currentTime = std::chrono::high_resolution_clock::now();
			deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			Time::GetInstance().SetDeltaTime(deltaTime);
			lag += deltaTime;

			doContinue = input.ProcessInput();
			input.HandleInput();
			while(lag >= Time::GetInstance().GetFixedDeltaTime())
			{
				sceneManager.FixedUpdate();
				lag -= Time::GetInstance().GetFixedDeltaTime();
			}
			sceneManager.Update();
			renderer.Render();

			lastTime = currentTime;
		}
	}

	Cleanup();
}
