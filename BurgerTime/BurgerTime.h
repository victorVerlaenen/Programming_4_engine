#pragma once
struct SDL_Window;
namespace dae
{
	enum class TileType;
	class TransformComponent;
	class RenderComponent;
	class GameObject;
	class Scene;
	class BurgerTime
	{
	public:
		BurgerTime();
		~BurgerTime();

		BurgerTime(const BurgerTime& other) = delete;
		BurgerTime(BurgerTime&& other) = delete;
		BurgerTime& operator=(const BurgerTime& other) = delete;
		BurgerTime& operator=(BurgerTime&& other) = delete;

		void LoadBurgerTime() const;
	private:
		void AddDAELogo(Scene& scene) const;
		void AddText(Scene& scene, const std::string& text, const glm::vec2& pos, const SDL_Color& textColor, unsigned int fontSize) const;
		void AddFPSCounter(Scene& scene, const glm::vec2& pos, const SDL_Color& textColor) const;
		GameObject* AddPlayerOne(Scene& scene) const;
		void AddPlayerTwo(Scene& scene) const;
		void AddPlatforms(Scene& scene) const;
		glm::vec2 AddPlatform(Scene& scene, const glm::vec2& pos, TileType type) const;

		SDL_Window* m_Window{};
		int m_WindowWidth{ 876 };
		int m_WindowHeight{ 750 };
	};
}

