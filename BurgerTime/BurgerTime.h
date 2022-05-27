#pragma once
struct SDL_Window;
namespace dae
{
	class BurgerTime
	{
	public:
		BurgerTime() = default;
		~BurgerTime() = default;

		BurgerTime(const BurgerTime& other) = delete;
		BurgerTime(BurgerTime&& other) = delete;
		BurgerTime& operator=(const BurgerTime& other) = delete;
		BurgerTime& operator=(BurgerTime&& other) = delete;

		void LoadBurgerTime();
	private:
		SDL_Window* m_Window{};
		int m_WindowWidth{ 640 };
		int m_WindowHeight{ 480 };
	};
}

