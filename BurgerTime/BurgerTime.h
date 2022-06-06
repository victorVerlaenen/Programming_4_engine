#pragma once
struct SDL_Window;
namespace dae
{
	class LivesComponent;
	class ScoreComponent;
	enum class Ingedient;
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
		std::shared_ptr<GameObject> AddPlayer(Scene& scene, LivesComponent* pLivesComponent, const glm::vec2& pos) const;
		void AddEnemy(Scene& scene, LivesComponent* pLivesComponent, const glm::vec2& pos) const;
		std::shared_ptr<GameObject> AddScoreDisplay(Scene& scene) const;
		std::shared_ptr<GameObject> AddLivesDisplay(Scene& scene) const;
		void AddPlayerTwo(Scene& scene) const;
		void LoadMap(Scene& scene, const std::string& mapFile) const;
		glm::vec2 AddPlatform(Scene& scene, const glm::vec2& pos, TileType type) const;
		void AddIngredient(Scene& scene, const glm::vec2& pos, Ingedient type, GameObject* pPlayerObject, ScoreComponent* pScoreComponent) const;
		void AddPlate(Scene& scene, const glm::vec2& pos) const;

		int m_WindowWidth{ 876 };
		int m_WindowHeight{ 750 };
	};
}

