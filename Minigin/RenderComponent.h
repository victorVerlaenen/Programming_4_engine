#pragma once
#include "Component.h"

class Texture2D;
class RenderComponent : public Component
{
public:
	RenderComponent(dae::GameObject* pOwner);
	virtual ~RenderComponent() = default;

	virtual void Update(float deltaTime) override;

	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;

	void SetTexture(dae::Texture2D* pTexture);
	void Render() const;
private:
	dae::Texture2D* m_pTexture;
};