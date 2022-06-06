#include "MiniginPCH.h"
#include "LoggedAudioSystem.h"

dae::LoggedAudioSystem::LoggedAudioSystem(AudioSystem* wrappedAudioSystem)
	: m_WrappedAudioSystem(wrappedAudioSystem)
{
	Log("AudioSystem created");
	if(wrappedAudioSystem == nullptr)
	{
		m_WrappedAudioSystem = new NullAudioSystem{};
	}
}

dae::LoggedAudioSystem::~LoggedAudioSystem()
{
	Log("AudioSystem destroyed");
	delete m_WrappedAudioSystem;
	m_WrappedAudioSystem = nullptr;
}

void dae::LoggedAudioSystem::PlaySound(const std::string& filePath, bool looped, int volume)
{
	Log("Play sound");
	m_WrappedAudioSystem->PlaySound(filePath, looped, volume);
}

void dae::LoggedAudioSystem::CheckQueue()
{
	Log("Check queue");
	m_WrappedAudioSystem->CheckQueue();
}

void dae::LoggedAudioSystem::Log(const std::string& message) const
{
	std::cout << message << std::endl;
}
