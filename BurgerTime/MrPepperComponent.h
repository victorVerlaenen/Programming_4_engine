#pragma once
#include "Component.h"
#include "State.h"
#include "Subject.h"

namespace dae
{
	class TileComponent;
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
		void FixedUpdate() override;
		void Render() const override;

		void SetStoppable(bool value) { m_Stoppable = value; }
		bool GetStoppable() const { return m_Stoppable; }

		bool GetIsOnLadder() const { return m_IsOnLadder; }
		bool GetIsGrounded() const { return m_IsGrounded; }
		std::shared_ptr<State> GetState() const { return m_pState; }
		std::shared_ptr<State> GetPrevState() const { return m_pPrevState; }

		void SetState(std::shared_ptr<State> pState);
		void SetIsOnLadder(bool value) { m_IsOnLadder = value; }
		void SetIsGrounded(bool value) { m_IsGrounded = value; }

		MrPepperComponent(const MrPepperComponent& other) = delete;
		MrPepperComponent(MrPepperComponent&& other) = delete;
		MrPepperComponent& operator=(const MrPepperComponent& other) = delete;
		MrPepperComponent& operator=(MrPepperComponent&& other) = delete;
	private:
		void CheckForWorldCollision();
		
		std::vector<CollisionComponent*> m_pTileColliders;
		std::vector<TileComponent*> m_pTileComponents;
		PlayerControllerComponent* m_pPlayerControllerComponent;
		CollisionComponent* m_pCollisionComponent;
		TransformComponent* m_pTransformComponent;
		std::shared_ptr<State> m_pState;
		std::shared_ptr<State> m_pPrevState;
		bool m_Stoppable = true;
		bool m_IsGrounded = false;
		bool m_IsOnLadder = false;
		glm::vec2 m_Gravity{ 0,9.81f *2 };
	};
}

