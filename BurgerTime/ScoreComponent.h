#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class TextComponent;
	class ScoreComponent : public Component, public Observer
	{
	public:
		ScoreComponent(GameObject* pOwner);
		~ScoreComponent() override = default;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void OnNotify(GameObject* actor, const Event& event) override;

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;
	private:
		int m_Score{ 0 };
		TextComponent* m_pTextComponent;
	};
}
