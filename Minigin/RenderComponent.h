#pragma once
#include "Component.h"
#include "Texture2D.h"

namespace dae
{
	class TransformComponent;
	class Texture2D;
	class RenderComponent : public Component
	{
	public:
		enum class RenderMode
		{
			LeftTop,
			CenterTop,
			RightTop,
			LeftCenter,
			CenterCenter,
			RightCenter,
			LeftBottom,
			CenterBottom,
			RightBottom
		};
		RenderComponent(GameObject* pOwner, RenderMode renderMode = RenderMode::LeftTop, const std::string& filename = {});
		~RenderComponent() override = default;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void SetTexture(std::shared_ptr<Texture2D> pTexture);
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		TransformComponent* m_pTransformComponent;
		RenderMode m_RenderMode;
	};
}