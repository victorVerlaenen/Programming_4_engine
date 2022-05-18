#pragma once
#include "Observer.h"
#include <vector>
namespace dae
{
	class Subject
	{
	public:
		Subject() = default;
		virtual ~Subject() = default;

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

		template <typename T>
		void AddObserver(T* pObeserver)
		{
			for (auto pObs : m_pObservers)
				if (dynamic_cast<T*>(pObs))
					return;
			m_pObservers.push_back(pObeserver);
		}
		template <typename T>
		void RemoveObserver()
		{
			for (int i{}; i < m_pObservers.size(); ++i)
				if (dynamic_cast<T>(*m_pObservers[i]))
					m_pObservers.erase(m_pObservers.begin() + i);
		}

		void Notify(GameObject* actor, const Observer::Event& event);
	protected:
	private:
		std::vector<Observer*> m_pObservers;
	};
}

