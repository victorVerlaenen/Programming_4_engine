#include "MiniginPCH.h"
#include "LoggedAudioSystem.h"
#include "NullAudioSystem.h"

dae::LoggedAudioSystem::LoggedAudioSystem(AudioSystem* wrappedAudioSystem = new NullAudioSystem{})
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

void dae::LoggedAudioSystem::RegisterSound(const std::string& filePath)
{
	Log("Register sound");
	m_WrappedAudioSystem->RegisterSound(filePath);
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
