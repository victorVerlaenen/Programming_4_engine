#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Texture2D.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "RenderComponent.h"
#include <string>

TextComponent::TextComponent(std::shared_ptr<dae::GameObject> pOwner, const std::string& text, std::shared_ptr<dae::Font> pFont, const SDL_Color& color)
	:Component{ pOwner }
	, m_Text{ text }
	, m_pFont{ pFont }
	, m_Color{color}
{

}

void TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		const auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);

		m_TextTexture = std::make_shared<dae::Texture2D>(texture);
		m_pOwner.lock()->GetComponent<RenderComponent>()->SetTexture(m_TextTexture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::FixedUpdate()
{

}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

dae::Texture2D* TextComponent::GetTexture() const
{
	return m_TextTexture.get();
}