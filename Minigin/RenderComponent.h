#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Texture2D.h"

namespace dae
{
	class TransformComponent;
	class Texture2D;
	class RenderComponent : public Component
	{
	public:
		
		RenderComponent(GameObject* pOwner);
		RenderComponent(GameObject* pOwner, RenderMode renderMode, const std::string& filename = {});
		RenderComponent(GameObject* pOwner, int scale, RenderMode renderMode = RenderMode::LeftTop, const std::string& filename = {});
		~RenderComponent() override = default;

		virtual void Update() override;
		void FixedUpdate() override {};
		void Render() const override;
		virtual int GetTextureWidth() const { return m_Width * m_Scale; }
		virtual int GetTextureHeight() const { return m_Height * m_Scale; }
		glm::vec2 GetPosition() const;
		RenderMode GetRenderMode() const { return m_RenderMode; }

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void SetTexture(std::shared_ptr<Texture2D> pTexture);
	protected:
		void SetPos(RenderMode renderMode, glm::vec2& pos) const;
		std::shared_ptr<Texture2D> m_pTexture;
		TransformComponent* m_pTransformComponent;
		RenderMode m_RenderMode;
		glm::vec2 m_Position;
		int m_Scale;
		int m_Width;
		int m_Height;
	};
}