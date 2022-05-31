#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class PhysicsBodyComponent : public Component, public Subject
	{
	public:
		PhysicsBodyComponent(GameObject* pOwner);
		~PhysicsBodyComponent() override = default;
		
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		PhysicsBodyComponent(const PhysicsBodyComponent& other) = delete;
		PhysicsBodyComponent(PhysicsBodyComponent&& other) = delete;
		PhysicsBodyComponent& operator=(const PhysicsBodyComponent& other) = delete;
		PhysicsBodyComponent& operator=(PhysicsBodyComponent&& other) = delete;
	private:
	};
}