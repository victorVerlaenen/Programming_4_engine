#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Texture2D.h"
#include <SDL_ttf.h>
#include "GameObject.h"
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "Component.h"
#include <string>

TextComponent::TextComponent(dae::GameObject* pOwner, const std::string& text, dae::Font* pFont)
	:Component{ pOwner }
	, m_Text{ text }
	, m_pFont{ pFont }
{

}

void TextComponent::Update(float)
{
	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	std::shared_ptr<dae::Texture2D> m_TextTexture;
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
}

std::shared_ptr<dae::Texture2D> TextComponent::GetTexture() const
{
	return m_TextTexture;
}