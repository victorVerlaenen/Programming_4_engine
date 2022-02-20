#pragma once
#include "Component.h"
#include "glm/glm.hpp"

class TransformComponent : public Component
{
public:
	TransformComponent(dae::GameObject* pOwner, const glm::vec2& position);
	virtual ~TransformComponent() = default;


	virtual void Update(float deltaTime) override;

	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

	glm::vec2 GetPosition() const;
	void SetPosition(const glm::vec2& position);
private:
	glm::vec2 m_Position;
};