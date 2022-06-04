#pragma once
#include "Component.h"
#include "box2d/box2d.h"

namespace dae
{
	class SpriteRenderComponent;
	class RenderComponent;
	struct Rect
	{
		int xPos;
		int yPos;
		int width;
		int height;
	};
	class CollisionComponent : public Component
	{
	public:
		CollisionComponent(GameObject* pOwner, int xPos, int yPos, int width, int height);
		CollisionComponent(GameObject* pOwner, int xPos, int yPos);
		CollisionComponent(GameObject* pOwner);
		~CollisionComponent() override = default;
		
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;
		void AddPlaformMargin(int margin);

		Rect GetShape() const { return m_Shape; }
		bool IsOverlapping(const Rect& otherShape) const;
		bool IsOverlapping(const glm::vec2& point) const;
		bool IsBetween(const Rect& otherShape) const;

		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) = delete;
	private:
		Rect m_Shape;
		int m_Margin{ 0 };
		Rect m_TestShape{ 0,0,100,400 };
		RenderComponent* m_pRenderComponent{nullptr};
		SpriteRenderComponent* m_pSpriteRenderComponent{nullptr};
	};
}