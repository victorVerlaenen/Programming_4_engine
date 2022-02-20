#pragma once
#include "Component.h"
#include "Font.h"

class Font;
class TextComponent : public Component
{
public:
	TextComponent(dae::GameObject* pOwner, const std::string& text, dae::Font* pFont);
	virtual ~TextComponent() = default;

	virtual void Update(float deltaTime) override;

	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	void SetText(const std::string& text);
	std::shared_ptr<dae::Texture2D> GetTexture() const;
private:
	std::string m_Text;
	dae::Font* m_pFont;
	std::shared_ptr<dae::Texture2D> m_TextTexture;
};