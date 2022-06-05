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
	m_Position = m_pTransformComponent->GetPosition();
	SetPos(m_RenderMode, m_Position);
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
	m_Position = m_pTransformComponent->GetPosition();
	SetPos(m_RenderMode, m_Position);
}

void dae::SpriteRenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{

		SDL_Rect srcRect;
		srcRect.w = m_FrameWidth;
		srcRect.h = m_FrameHeight;
		srcRect.x = srcRect.w * m_CurrentCol;
		srcRect.y = srcRect.h * (m_NrOfRows - 1 - m_CurrentRow);

		SDL_Rect destRect;
		destRect.x = static_cast<int>(m_Position.x);
		destRect.y = static_cast<int>(m_Position.y);

		destRect.w = srcRect.w * m_Scale;
		destRect.h = srcRect.h * m_Scale;
		Renderer::GetInstance().RenderTexture(*m_pTexture, destRect, srcRect);
	}
}

void dae::SpriteRenderComponent::SetSprite(std::shared_ptr<Texture2D> pTexture, int nrOfRows, int nrOfColumns, const int scale)
{
	m_pTexture = pTexture;
	m_NrOfRows = nrOfRows;
	m_NrOfColumns = nrOfColumns;
	m_Scale = scale;
	m_CurrentCol = 0;
	m_CurrentRow = 0;
	m_NrOfFrames = nrOfColumns * nrOfRows;
	m_CurrentFrame = 0;
	m_FrameWidth = m_pTexture->GetWidth() / nrOfColumns;
	m_FrameHeight = m_pTexture->GetHeight() / nrOfRows;
}
