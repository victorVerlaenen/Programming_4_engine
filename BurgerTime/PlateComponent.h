#pragma once
#include "Component.h"

namespace dae
{
	class CollisionComponent;


	class PlateComponent : public dae::Component
	{
	public:
		PlateComponent(GameObject* pOwner);
		~PlateComponent() override = default;

		void Update() override{};
		void FixedUpdate() override {};
		void Render() const override {};
		
		CollisionComponent* GetCollider() const { return m_pCollisionComponent; }

		PlateComponent(const PlateComponent& other) = delete;
		PlateComponent(PlateComponent&& other) = delete;
		PlateComponent& operator=(const PlateComponent& other) = delete;
		PlateComponent& operator=(PlateComponent&& other) = delete;

		static std::vector<PlateComponent*> m_pPlateComponents;
	private:
		CollisionComponent* m_pCollisionComponent;
	};
}
