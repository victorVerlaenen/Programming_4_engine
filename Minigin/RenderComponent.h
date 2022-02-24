#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Texture2D.h"

//Renders the texture
class Texture2D;
class RenderComponent : public Component
{
public:
	RenderComponent(std::shared_ptr<dae::GameObject> pOwner);
	~RenderComponent() override = default;

	void Update(float deltaTime) override;
	void FixedUpdate(float fixedTimeStep) override;
	void Render() const override;

	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;
	
	void SetTexture(std::shared_ptr<dae::Texture2D> pTexture);
private:
	std::shared_ptr<dae::Texture2D> m_pTexture;
};