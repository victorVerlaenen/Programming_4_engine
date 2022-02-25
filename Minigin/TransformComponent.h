#pragma once
#include "Component.h"
#include "GameObject.h"

//Holds the transform
class TransformComponent : public Component
{
public:
	TransformComponent(std::shared_ptr<dae::GameObject> pOwner, const glm::vec2& position);
	virtual ~TransformComponent() override = default;

	void Update( ) override;
	void FixedUpdate( ) override;

	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

	glm::vec2 GetPosition() const;
	void SetPosition(const glm::vec2& position);
private:
	glm::vec2 m_Position;
};