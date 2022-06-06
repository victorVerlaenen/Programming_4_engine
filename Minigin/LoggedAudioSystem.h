#pragma once
#include "AudioSystem.h"
#include "NullAudioSystem.h"

namespace dae
{
	class LoggedAudioSystem final : public AudioSystem
	{
	public:
		LoggedAudioSystem(AudioSystem* wrappedAudioSystem = new NullAudioSystem{});
		~LoggedAudioSystem() override;

		LoggedAudioSystem(const LoggedAudioSystem& other) = delete;
		LoggedAudioSystem(LoggedAudioSystem&& other) noexcept = delete;
		LoggedAudioSystem& operator=(const LoggedAudioSystem& other) = delete;
		LoggedAudioSystem& operator=(LoggedAudioSystem&& other) noexcept = delete;

		void PlaySound(const std::string& filePath, bool looped, int volume = -1) override;
		void CheckQueue() override;
	private:
		void Log(const std::string& message) const;
		AudioSystem* m_WrappedAudioSystem;
	};
}

