#include "MiniginPCH.h"
#include "Renderer.h"

#include <chrono>

#include "SceneManager.h"
#include "Texture2D.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);
	
	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, RenderMode renderMode, const float x, const float y, const int scale) const
{
	SDL_Rect dst{};
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w *= static_cast<int>(scale);
	dst.h *= static_cast<int>(scale);

	SetDestRect(renderMode, dst);
	
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, RenderMode renderMode, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	SetDestRect(renderMode, dst);

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, RenderMode renderMode, SDL_Rect destRect) const
{
	SDL_Rect dst = destRect;
	SetDestRect(renderMode, dst);

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, RenderMode renderMode, SDL_Rect destRect, SDL_Rect srcRect) const
{
	SDL_Rect src = srcRect;

	SDL_Rect dst = destRect;
	SetDestRect(renderMode, dst);

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

void dae::Renderer::SetDestRect(RenderMode renderMode, SDL_Rect& destRect) const
{
	switch (renderMode)
	{
	case RenderMode::CenterCenter:
		destRect.x = (destRect.x - destRect.w / 2);
	case RenderMode::LeftCenter:
		destRect.y = (destRect.y - destRect.h / 2);
		break;
	case RenderMode::CenterBottom:
		destRect.y = (destRect.y - destRect.h);
	case RenderMode::CenterTop:
		destRect.x = (destRect.x - destRect.w / 2);
		break;
	case RenderMode::RightBottom:
		destRect.x = (destRect.x - destRect.w);
	case RenderMode::LeftBottom:
		destRect.y = (destRect.y - destRect.h);
		break;
	case RenderMode::RightCenter:
		destRect.y = (destRect.y - destRect.h / 2);
	case RenderMode::RightTop:
		destRect.x = (destRect.x - destRect.w);
		break;
	case RenderMode::LeftTop:
	default:
		break;
	}
}
