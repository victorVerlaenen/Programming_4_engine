#pragma once
#include "Component.h"
#include "State.h"
#include "Subject.h"

namespace dae
{
	class CollisionComponent;
	class TransformComponent;
	class PlayerControllerComponent;
	class MrPepperComponent : public Component, public Subject
	{
	public:
		MrPepperComponent(GameObject* pOwner);
		~MrPepperComponent() override = default;

		void Initialize();
		void Update() override;
		void FixedUpdate() override {};
		void Render() const override {};
		void LateUpdate() override;

		void MoveToGround();

		bool GetIsOnLadder() const { return m_IsOnLadder; }
		bool GetIsGrounded() const { return m_IsGrounded; }
		bool GetCantClimbDown() const { return m_CantClimbdown; }

		void SetState(std::shared_ptr<State> pState);
		void SetGroundYPos(float value) { m_GroundYPos = value; }
		void SetIsGrounded(bool value) { m_IsGrounded = value; }
		void SetIsOnLadder(bool value) { m_IsOnLadder = value; }
		void SetColliding(bool value) { m_Colliding = value; }
		void SetCantClimbDown(bool value) { m_CantClimbdown = value; }

		MrPepperComponent(const MrPepperComponent& other) = delete;
		MrPepperComponent(MrPepperComponent&& other) = delete;
		MrPepperComponent& operator=(const MrPepperComponent& other) = delete;
		MrPepperComponent& operator=(MrPepperComponent&& other) = delete;
	private:
		PlayerControllerComponent* m_pPlayerControllerComponent;

		CollisionComponent* m_pCollisionComponent;
		TransformComponent* m_pTransformComponent;

		std::shared_ptr<State> m_pState;
		std::shared_ptr<State> m_pPrevState;

		float m_GroundYPos{ 0 };
		bool m_IsGrounded = false;
		bool m_IsOnLadder = false;
		bool m_CantClimbdown = true;
		bool m_Colliding = false;
		const glm::vec2 m_Gravity{ 0,9.81f * 2 };
	};
}

