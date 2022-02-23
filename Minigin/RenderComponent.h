#pragma once
#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"

//Renders the texture
class Texture2D;
class RenderComponent : public Component
{
public:
	RenderComponent(dae::Texture2D* pTexture, TransformComponent* pTransform, std::shared_ptr<dae::GameObject> pOwner);
	~RenderComponent() override = default;

	void Update(float deltaTime) override;

	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;
	
	void Render() const;
private:
	dae::Texture2D* m_pTexture;
	TransformComponent* m_pTransform;
};