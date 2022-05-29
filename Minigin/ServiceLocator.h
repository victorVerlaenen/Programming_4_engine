#pragma once
namespace dae
{
	class NullAudioSystem;
	class AudioSystem;

	class ServiceLocator final
	{
	public:
		ServiceLocator() = default;
		~ServiceLocator() = default;

		ServiceLocator(const ServiceLocator& other) = delete;
		ServiceLocator(ServiceLocator&& other) noexcept = delete;
		ServiceLocator& operator=(const ServiceLocator& other) = delete;
		ServiceLocator& operator=(ServiceLocator&& other) noexcept = delete;

		static void Initialize();
		static AudioSystem& GetAudioSystem();
		static void RegisterAudioSystem(AudioSystem* audioSystem);
		static void CleanUp();
	private:
		static AudioSystem* m_pAudioSystem;
		static NullAudioSystem m_DefaultAudioSystem;
	};
}

