#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class RenderComponent;
	class LivesComponent : public Component, public Observer
	{
	public:
		LivesComponent(GameObject* pOwner);
		~LivesComponent() override = default;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void OnNotify(GameObject* actor,const Event& event) override;

		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) = delete;
	private:
		int m_Lives = 5;
		RenderComponent* m_pRenderComponent;
	};
}
