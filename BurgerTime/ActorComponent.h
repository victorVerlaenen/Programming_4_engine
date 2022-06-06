#pragma once
#include "Subject.h"
#include "Component.h"

namespace dae
{
	class State;
	class CollisionComponent;
	class TransformComponent;
	class ActorComponent : public Component, public Subject
	{
	public:
		ActorComponent(GameObject* pOwner, bool isPlayer);
		virtual ~ActorComponent() override = default;

		void Update() override = 0;
		void FixedUpdate() override = 0;
		void Render() const override = 0;
		void LateUpdate() override = 0;

		void MoveToGround();

		void Reset();

		bool GetIsPlayer() const { return m_IsPlayer; }
		bool GetIsOnLadder() const { return m_IsOnLadder; }
		bool GetIsGrounded() const { return m_IsGrounded; }
		bool GetCantClimbDown() const { return m_CantClimbdown; }
		bool GetCantClimbUp() const { return m_CantClimbUp; }
		CollisionComponent* GetCollider() const { return m_pCollisionComponent; }
		TransformComponent* GetTransform() const { return m_pTransformComponent; }

		void SetFixPosition(const glm::vec2& pos) { m_FixPosition = pos; }
		void SetState(std::shared_ptr<State> pState);
		void SetGroundYPos(float value) { m_GroundYPos = value; }
		void SetIsGrounded(bool value) { m_IsGrounded = value; }
		void SetIsOnLadder(bool value) { m_IsOnLadder = value; }
		void SetColliding(bool value) { m_Colliding = value; }
		void SetCantClimbDown(bool value) { m_CantClimbdown = value; }
		void SetCantClimbUp(bool value) { m_CantClimbUp = value; }
		void SetIsPastPlatform(bool value) { m_IsPastPlatform = value; }

		ActorComponent(const ActorComponent& other) = delete;
		ActorComponent(ActorComponent&& other) = delete;
		ActorComponent& operator=(const ActorComponent& other) = delete;
		ActorComponent& operator=(ActorComponent&& other) = delete;

		static std::vector<ActorComponent*> m_pActorComponents;
	protected:
		CollisionComponent* m_pCollisionComponent;
		TransformComponent* m_pTransformComponent;

		std::shared_ptr<State> m_pState;
		std::shared_ptr<State> m_pPrevState;

		bool m_IsPlayer;

		float m_GroundYPos{ 0 };
		bool m_IsGrounded = false;
		bool m_IsOnLadder = false;
		bool m_CantClimbdown = true;
		bool m_CantClimbUp = true;
		bool m_Colliding = false;
		bool m_IsPastPlatform = true;
		glm::vec2 m_FixPosition{};
		glm::vec2 m_StartingPos;
	};
}