#pragma once
#include "Component.h"
#include "MrPepperComponent.h"

namespace dae
{
	class TransformComponent;
	class RenderComponent;
	class CollisionComponent;

	enum class TileType
	{
		NormalPlatform,
		LadderPlatform,
		Ladder
	};

	class TileComponent : public Component
	{
		friend void MrPepperComponent::Update();
	public:
		TileComponent(GameObject*, TileType tileType);
		~TileComponent() override = default;
		
		void Update() override;
		void FixedUpdate() override{};
		void Render() const override{};
		void LateUpdate() override;

		int GetPlatformMargin()const { return m_PlatformMargin; }
		CollisionComponent* GetCollider() const { return m_pCollisionComponent; }
		TileType GetTileType() const { return m_TileType; }

		TileComponent(const TileComponent& other) = delete;
		TileComponent(TileComponent&& other) = delete;
		TileComponent& operator=(const TileComponent& other) = delete;
		TileComponent& operator=(TileComponent&& other) = delete;

		static std::vector<TileComponent*> m_pTileComponents;
	private:
		CollisionComponent* m_pCollisionComponent;
		RenderComponent* m_pRenderComponent;

		std::vector <CollisionComponent*> m_pActorColliders;
		std::vector <TransformComponent*> m_pActorTransformComponents;

		TileType m_TileType;
		const int m_PlatformMargin = {10};
	};
}
