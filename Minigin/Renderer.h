#pragma once
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	enum class RenderMode
	{
		LeftTop,
		CenterTop,
		RightTop,
		LeftCenter,
		CenterCenter,
		RightCenter,
		LeftBottom,
		CenterBottom,
		RightBottom
	};
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_clearColor{};
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Update();
		void Destroy();

		void RenderTexture(const Texture2D& texture, RenderMode renderMode, float x, float y, int scale = 1) const;
		void RenderTexture(const Texture2D& texture, RenderMode renderMode, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, RenderMode renderMode, SDL_Rect destRect) const;
		void RenderTexture(const Texture2D& texture, RenderMode renderMode, SDL_Rect destRect, SDL_Rect srcRect) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	private:
		void SetDestRect(RenderMode renderMode, SDL_Rect& destRect) const;
	};
}