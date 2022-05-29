#include "MiniginPCH.h"
#include "ServiceLocator.h"
#include "AudioSystem.h"
#include "NullAudioSystem.h"

dae::NullAudioSystem dae::ServiceLocator::m_DefaultAudioSystem{};
dae::AudioSystem* dae::ServiceLocator::m_pAudioSystem{ nullptr };

void dae::ServiceLocator::Initialize()
{
	m_pAudioSystem = &m_DefaultAudioSystem;
}

dae::AudioSystem& dae::ServiceLocator::GetAudioSystem()
{
	return *m_pAudioSystem;
}

void dae::ServiceLocator::RegisterAudioSystem(AudioSystem* audioSystem)
{
	if (m_pAudioSystem != &m_DefaultAudioSystem)
	{
		delete m_pAudioSystem;
		m_pAudioSystem = nullptr;
	}

	if (audioSystem == nullptr)
	{
		m_pAudioSystem = &m_DefaultAudioSystem;
		return;
	}
	m_pAudioSystem = audioSystem;
}

void dae::ServiceLocator::CleanUp()
{
	delete m_pAudioSystem;
	m_pAudioSystem = nullptr;
}
