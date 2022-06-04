#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class TileComponent;
	class TransformComponent;
	class RenderComponent;
	class CollisionComponent;

	enum class Ingedient
	{
		TopBun,
		Cheese,
		Patty,
		Tomato,
		Lettuce,
		BottomBun
	};

	enum class IngedientState
	{
		OnPlatform,
		Falling,
		Collected
	};

	class IngredientComponent : public Component, public Subject
	{
	public:
		IngredientComponent(GameObject* pOwner, GameObject* pPlayerObject, Ingedient ingredientType);
		~IngredientComponent() override = default;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		CollisionComponent* GetCollider() const { return m_pCollisionComponent; }

		IngredientComponent(const IngredientComponent& other) = delete;
		IngredientComponent(IngredientComponent&& other) = delete;
		IngredientComponent& operator=(const IngredientComponent& other) = delete;
		IngredientComponent& operator=(IngredientComponent&& other) = delete;

		static std::vector<IngredientComponent*> m_pIngredients;
	private:
		std::vector<CollisionComponent*> m_pTileColliders;
		std::vector<TileComponent*> m_pTileComponents;

		CollisionComponent* m_pPlayerCollisionComponent;
		TransformComponent* m_pPlayerTransformComponent;

		CollisionComponent* m_pCollisionComponent;
		RenderComponent* m_pRenderComponent;
		TransformComponent* m_pTransformComponent;
		
		IngedientState m_IngredientState;

		float m_Timer{ 0.f };
		const float m_FallingCooldown{ 1.f };
	};
}
