#pragma once
#include "Component.h"

namespace dae
{
	class PlatformComponent : public Component
	{
	public:
		PlatformComponent(GameObject* pOwner, GameObject* pPlayerObject);
		~PlatformComponent() override = default;
		
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		PlatformComponent(const PlatformComponent& other) = delete;
		PlatformComponent(PlatformComponent&& other) = delete;
		PlatformComponent& operator=(const PlatformComponent& other) = delete;
		PlatformComponent& operator=(PlatformComponent&& other) = delete;
	private:
	};
}