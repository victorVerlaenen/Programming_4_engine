#pragma once
#include "Component.h"

namespace dae
{
	class MrPepperComponent;
	class TransformComponent;
	class RenderComponent;
	class CollisionComponent;

	enum class TileType
	{
		NormalPlaform,
		LadderPlatform,
		Ladder
	};

	class TileComponent : public Component
	{
	public:
		TileComponent(GameObject* pOwner, TileType tileType);
		~TileComponent() override = default;
		
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;
		int GetPlatformMargin()const { return m_PlatformMargin; }
		TileType GetTileType() const { return m_TileType; }

		TileComponent(const TileComponent& other) = delete;
		TileComponent(TileComponent&& other) = delete;
		TileComponent& operator=(const TileComponent& other) = delete;
		TileComponent& operator=(TileComponent&& other) = delete;
	private:
		CollisionComponent* m_pCollisionComponent;
		CollisionComponent* m_pPlayerCollisionComponent;
		RenderComponent* m_pRenderComponent;
		TransformComponent* m_pPlayerTransformComponent;
		MrPepperComponent* m_pMrPepperComponent;
		TileType m_TileType;
		const int m_PlatformMargin = {4};
	};
}