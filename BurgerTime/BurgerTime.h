#pragma once
struct SDL_Window;
namespace dae
{
	class Scene;
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
		void AddDAELogo(Scene& scene) const;
		void AddText(Scene& scene, const std::string& text, const glm::vec2& pos, const SDL_Color& textColor, unsigned int fontSize) const;
		void AddFPSCounter(Scene& scene, const glm::vec2& pos, const SDL_Color& textColor) const;
		void AddPlayerOne(Scene& scene) const;
		void AddPlayerTwo(Scene& scene) const;

		SDL_Window* m_Window{};
		int m_WindowWidth{ 640 };
		int m_WindowHeight{ 480 };
	};
}

