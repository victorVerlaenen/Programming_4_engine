#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"


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
		m_WindowWidth,
		m_WindowHeight,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(std::function<void()> loadFunction)
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	//LoadGame();
	loadFunction();

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
			Clock::GetInstance().SetDeltaTime(deltaTime);
			lag += deltaTime;

			doContinue = input.ProcessInput();
			input.HandleInput();
			while (lag >= Clock::GetInstance().GetFixedDeltaTime())
			{
				sceneManager.FixedUpdate();
				lag -= Clock::GetInstance().GetFixedDeltaTime();
			}
			sceneManager.Update();
			sceneManager.LateUpdate();
			renderer.Render();

			lastTime = currentTime;
		}
	}

	Cleanup();
}
