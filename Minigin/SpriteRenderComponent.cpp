#include "MiniginPCH.h"
#include "SpriteRenderComponent.h"
#include "TransformComponent.h"

dae::SpriteRenderComponent::SpriteRenderComponent(GameObject* pOwner, const std::string& filename, int nrOfRows, int nrOfColumns, const int scale, RenderMode renderMode)
	:RenderComponent(pOwner, scale, renderMode, filename)
	, m_NrOfRows(nrOfRows)
	, m_NrOfColumns(nrOfColumns)
	, m_NrOfFrames(nrOfRows* nrOfColumns)
	, m_CurrentFrame(0)
	, m_CurrentRow(0)
	, m_CurrentCol(0)
	, m_ElapsedTime(0)
{
	m_FrameWidth = m_pTexture->GetWidth() / nrOfColumns;
	m_FrameHeight = m_pTexture->GetHeight() / nrOfRows;
}

dae::SpriteRenderComponent::SpriteRenderComponent(GameObject* pOwner, const std::string& filename, int nrOfRows, int nrOfColumns, int width, int height, RenderMode renderMode)
	:RenderComponent(pOwner, width, height, renderMode, filename)
	, m_NrOfRows(nrOfRows)
	, m_NrOfColumns(nrOfColumns)
	, m_NrOfFrames(nrOfRows* nrOfColumns)
	, m_CurrentFrame(0)
	, m_CurrentRow(0)
	, m_CurrentCol(0)
	, m_ElapsedTime(0)
{
	m_FrameWidth = m_pTexture->GetWidth() / nrOfColumns;
	m_FrameHeight = m_pTexture->GetHeight() / nrOfRows;
}

void dae::SpriteRenderComponent::Update()
{
	m_ElapsedTime += Clock::GetInstance().GetDeltaTime();
	if (m_ElapsedTime >= 1 / m_AnimationSpeed)
	{
		m_ElapsedTime = 0;
		m_CurrentFrame++;
		m_CurrentFrame %= m_NrOfFrames;
		m_CurrentRow = m_CurrentFrame / m_NrOfColumns;
		m_CurrentCol = m_CurrentFrame % m_NrOfColumns;


	}
}

void dae::SpriteRenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const glm::vec2& pos = m_pTransformComponent->GetPosition();
		SDL_Rect srcRect;
		srcRect.w = m_FrameWidth;
		srcRect.h = m_FrameHeight;
		srcRect.x = srcRect.w * m_CurrentCol;
		srcRect.y = srcRect.h * (m_NrOfRows - 1 - m_CurrentRow);

		SDL_Rect destRect;
		destRect.x = static_cast<int>(pos.x);
		destRect.y = static_cast<int>(pos.y);
		if (m_IsScaled)
		{
			destRect.w = srcRect.w * m_Scale;
			destRect.h = srcRect.h * m_Scale;
		}
		else
		{
			destRect.w = m_Width;
			destRect.h = m_Height;
		}
		Renderer::GetInstance().RenderTexture(*m_pTexture, m_RenderMode, destRect, srcRect);
	}
}

void dae::SpriteRenderComponent::SetSprite(std::shared_ptr<Texture2D> pTexture, int nrOfRows, int nrOfColumns, const int scale)
{
	m_pTexture = pTexture;
	m_NrOfRows = nrOfRows;
	m_NrOfColumns = nrOfColumns;
	m_Scale = scale;
	m_IsScaled = true;
	m_CurrentCol = 0;
	m_CurrentRow = 0;
	m_NrOfFrames = nrOfColumns * nrOfRows;
	m_CurrentFrame = 0;
}
