#pragma once
#include "Component.h"
#include "GameObject.h"

//Holds the transform
namespace dae
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent(GameObject* pOwner, const glm::vec2& position);
		~TransformComponent() override = default;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		glm::vec2 GetPosition() const;
		void SetPosition(const glm::vec2& position);
		void Translate(const glm::vec2& translation);
	private:
		glm::vec2 m_Position;
	};
}