#pragma once
#include "GameObject.h"
namespace dae
{
	class Observer
	{
	public:
		enum class Event
		{
			EVENT_ACTOR_DIED,
			EVENT_PLAYER_POINTS
		};

		Observer() = default;
		virtual ~Observer() = default;

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;

		virtual void OnNotify(GameObject* actor,const Event& event) = 0;
	};
}

