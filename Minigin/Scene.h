#pragma once

#include "SceneManager.h"

namespace dae
{
	//class SceneObject;
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object, unsigned int layer = 0);

		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render() const;

		std::vector < std::vector < std::shared_ptr<GameObject>>> GetObjects() const { return m_Objects; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector<std::vector<std::shared_ptr<GameObject>>> m_Objects{};

		static unsigned int m_IdCounter;
		static unsigned int m_Layers;
	};

}
