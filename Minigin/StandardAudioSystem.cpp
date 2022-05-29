#include "MiniginPCH.h"
#include "StandardAudioSystem.h"
#include "AudioSystem.h"

dae::StandardAudioSystem::StandardAudioSystem()
{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, MIX_CHANNELS);
	m_Thread = std::thread([this] { this->CheckQueue(); });
}

dae::StandardAudioSystem::~StandardAudioSystem()
{
	m_DoContinue = false;

	m_Thread.join();
	for (size_t i = 0; i < m_PlayedSounds.size(); i++)
	{
		delete m_PlayedSounds[i];
		m_PlayedSounds[i] = nullptr;
	}

	Mix_CloseAudio();
}

void dae::StandardAudioSystem::RegisterSound(const std::string& filePath)
{
	m_Sounds.emplace(new Audio(filePath));
}

void dae::StandardAudioSystem::CheckQueue()
{
	while(m_DoContinue == true)
	{
		if(m_Sounds.empty() == false)
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_Sounds.front()->Load();
			m_Sounds.front()->Play();
			m_PlayedSounds.emplace_back(m_Sounds.front());

			m_Sounds.pop();
		}
	}
}
