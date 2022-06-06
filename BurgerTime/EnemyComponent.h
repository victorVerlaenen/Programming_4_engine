#pragma once
#include "ActorComponent.h"
#include "Subject.h"
#include "Component.h"

namespace dae
{
	class EnemyComponent : public ActorComponent
	{
	public:
		EnemyComponent(GameObject* pOwner, bool isPlayer);
		virtual ~EnemyComponent() override = default;
		
		void Update() override;
		void FixedUpdate() override {}
		void Render() const override {}
		void LateUpdate() override;
		
		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) = delete;
	private:
		void SetMovementDirection();

		std::vector<TransformComponent*> m_pPlayerTransforms;
		std::vector<CollisionComponent*> m_pPlayerColliders;

		float m_Timer{ 0.f };
		const float m_ChangeCooldown{ .4f };
	};
}