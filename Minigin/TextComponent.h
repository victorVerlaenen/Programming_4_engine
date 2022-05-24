#pragma once
#include "Component.h"
#include "Font.h"
#include "GameObject.h"


namespace dae
{
	class RenderComponent;
	class Texture2D;
	class TextComponent : public Component
	{
	public:
		TextComponent(GameObject* pOwner, std::shared_ptr<Font> pFont, const SDL_Color& color, const std::string& text = "Empty");
		virtual ~TextComponent() override = default;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void SetText(const std::string& text);
		Texture2D* GetTexture() const;
	private:
		bool m_NeedsUpdate{ true };
		std::string m_Text;
		const SDL_Color m_Color;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_TextTexture;
		RenderComponent* m_pRenderComponent;

	};
}