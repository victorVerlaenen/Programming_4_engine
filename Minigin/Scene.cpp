#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;
unsigned int Scene::m_Layers = 0;

Scene::Scene(const std::string& name) : m_Name(name)
{
	m_Objects.push_back(std::vector<std::shared_ptr<GameObject>>{});
	;
}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>&object,unsigned int layer)
{
	while (layer > m_Layers)
	{
		//add layer if needed
		m_Objects.push_back(std::vector<std::shared_ptr<GameObject>>{});
		m_Layers++;
	}
	m_Objects[layer].push_back(object);
}

void Scene::Update()
{
	for (auto& layer : m_Objects)
	{
		for (auto& object : layer)
		{
			object->Update();
		}
	}
}

void Scene::FixedUpdate()
{
	for (auto& layer : m_Objects)
	{
		for (auto& object : layer)
		{
			object->FixedUpdate();
		}
	}
}

void Scene::LateUpdate()
{
	for (auto& layer : m_Objects)
	{
		for (auto& object : layer)
		{
			object->LateUpdate();
		}
	}
}

void Scene::Render() const
{
	for (const auto& layer : m_Objects)
	{
		for (auto& object : layer)
		{
			object->Render();
		}
	}
}

