#pragma once
#include "Transform.h"
#include "SceneObject.h"

class Component;
namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject : public SceneObject
	{
	public:
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);


		
		template <typename T>
		void AddComponent(T* pComponent)
		{
			for (auto pComp : m_pComponents)
				if (dynamic_cast<T*>(pComp))
					return;
			m_pComponents.push_back(pComponent);
		}
		template <typename T>
		T* GetComponent() const
		{
			for (auto pComp : m_pComponents)
			{
				T* obj = dynamic_cast<T*>(pComp);
				if (obj)
					return obj;
			}
			return nullptr;
		}
		template <typename T>
		void RemoveComponent()
		{
			for (int i{}; i < m_pComponents.size(); ++i)
				if (dynamic_cast<T>(*m_pComponents[i]))
					m_pComponents.erase(m_pComponents.begin() + i);
		}



		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_Texture{};
		std::vector<Component*> m_pComponents;
	};
}
