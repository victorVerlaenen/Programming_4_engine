#pragma once
#include <functional>
struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		void Initialize();
		void Cleanup();

		void Run(std::function<void()> loadFunction);
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		int m_WindowWidth{ 876 };
		int m_WindowHeight{ 750 };
		float m_FixedTimeStep{ .02f };
	};
}