#pragma once
#include "Component.h"
#include "Font.h"
#include "GameObject.h"

class RenderComponent;

//Makes the texture from text
class TextComponent : public Component
{
public:
	TextComponent(dae::GameObject* pOwner, const std::string& text, std::shared_ptr<dae::Font> pFont, const SDL_Color& color);
	virtual ~TextComponent() override = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	void SetText(const std::string& text);
	dae::Texture2D* GetTexture() const;
private:
	bool m_NeedsUpdate;
	std::string m_Text;
	const SDL_Color m_Color;
	std::shared_ptr<dae::Font> m_pFont;
	std::shared_ptr<dae::Texture2D> m_TextTexture;
	RenderComponent* m_pRenderComponent;

};