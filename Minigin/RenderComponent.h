#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Texture2D.h"

class TransformComponent;
class Texture2D;
//Renders the texture
class RenderComponent : public Component
{
public:
	RenderComponent(dae::GameObject* pOwner);
	~RenderComponent() override = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;
	
	void SetTexture(std::shared_ptr<dae::Texture2D> pTexture);
private:
	std::shared_ptr<dae::Texture2D> m_pTexture;
	TransformComponent* m_pTransformComponent;
};