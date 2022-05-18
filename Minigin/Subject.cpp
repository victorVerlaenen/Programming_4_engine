#include "MiniginPCH.h"
#include "Subject.h"

void dae::Subject::Notify(GameObject* actor, const Observer::Event& event)
{
	for (auto pObserver : m_pObservers)
	{
		pObserver->OnNotify(actor, event);
	}
}
