#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Texture2D.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "RenderComponent.h"
#include <string>

dae::TextComponent::TextComponent(GameObject* pOwner, std::shared_ptr<Font> pFont, const SDL_Color& color, const std::string& text)
	:Component{ pOwner }
	, m_Text{ text }
	, m_pFont{ pFont }
	, m_Color{color}
	, m_pRenderComponent{ GetOwner()->GetComponent<RenderComponent>() }
{
	
}

void dae::TextComponent::Update()
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
		m_pRenderComponent->SetTexture(m_TextTexture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::FixedUpdate()
{

}

void dae::TextComponent::Render() const
{
	
}


void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

dae::Texture2D* dae::TextComponent::GetTexture() const
{
	return m_TextTexture.get();
}