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
		RenderComponent(GameObject* pOwner, int width, int height, RenderMode renderMode = RenderMode::LeftTop, const std::string& filename = {});
		~RenderComponent() override = default;

		void Update() override {};
		void FixedUpdate() override {};
		void Render() const override;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void SetTexture(std::shared_ptr<Texture2D> pTexture);
	protected:
		std::shared_ptr<Texture2D> m_pTexture;
		TransformComponent* m_pTransformComponent;
		RenderMode m_RenderMode;
		int m_Scale;
		int m_Width;
		int m_Height;
		bool m_IsScaled;
	};
}