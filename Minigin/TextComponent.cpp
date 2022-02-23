#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Texture2D.h"
#include <SDL_ttf.h>
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "Component.h"
#include <string>

TextComponent::TextComponent(std::shared_ptr<dae::GameObject> pOwner, const std::string& text, dae::Font* pFont)
	:Component{ pOwner }
	, m_Text{ text }
	, m_pFont{ pFont }
{

}

void TextComponent::Update(float)
{
	//At the moment always true (testing purpose)
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
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

		m_TextTexture = (dae::Texture2D*)texture;
		m_pOwner.lock()->GetComponent<RenderComponent>()->SetTexture(m_TextTexture);
		//m_NeedsUpdate = false;
	}
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

dae::Texture2D* TextComponent::GetTexture() const
{
	return m_TextTexture;
}