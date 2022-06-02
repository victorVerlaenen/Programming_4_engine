#pragma once
#include "Transform.h"
//#include "SceneObject.h"

namespace dae
{
	class Scene;
	class Component;
	class GameObject final
	{
	public:
		void Update();
		void FixedUpdate();
		void Render() const;
		Scene* GetScene() const { return m_pScene; }
		
		template <typename T>
		T* AddComponent(T* pComponent)
		{
			for (auto pComp : m_pComponents)
				if (dynamic_cast<T*>(pComp))
					return nullptr;
			m_pComponents.push_back(pComponent);
			return pComponent;
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
		
		GameObject(Scene* pScene);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<Component*> m_pComponents;
		Scene* m_pScene;
	};
}
