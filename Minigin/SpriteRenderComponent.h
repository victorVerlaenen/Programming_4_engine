#pragma once
#include "RenderComponent.h"

namespace dae
{
	class SpriteRenderComponent final : public RenderComponent
	{
	public:
		SpriteRenderComponent(GameObject* pOwner, const std::string& filename, int nrOfRows, int nrOfColumns, int scale = 1, RenderMode renderMode = RenderMode::LeftTop);
		~SpriteRenderComponent() override = default;

		void Update() override;
		void FixedUpdate() override {};
		void Render() const override;
		void SetSprite(std::shared_ptr<Texture2D> pTexture, int nrOfRows, int nrOfColumns, const int scale);
		int GetTextureWidth() const override { return m_FrameWidth * m_Scale; }
		int GetTextureHeight() const override { return m_FrameHeight * m_Scale; }

		SpriteRenderComponent(const SpriteRenderComponent& other) = delete;
		SpriteRenderComponent(SpriteRenderComponent&& other) noexcept = delete;
		SpriteRenderComponent& operator=(const SpriteRenderComponent& other) = delete;
		SpriteRenderComponent& operator=(SpriteRenderComponent&& other) noexcept = delete;
	private:
		int m_NrOfRows;
		int m_NrOfColumns;
		int m_NrOfFrames;

		int m_CurrentFrame;
		int m_CurrentRow;
		int m_CurrentCol;

		int m_FrameWidth;
		int m_FrameHeight;

		float m_ElapsedTime;
		float m_AnimationSpeed{ 15.f };
	};
}

