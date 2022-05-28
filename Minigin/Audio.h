#pragma once
namespace dae
{
	class Audio final
	{
	public:
		Audio() = default;
		~Audio() = default;

		Audio(const Audio& other) = delete;
		Audio(Audio&& other) noexcept = delete;
		Audio& operator=(const Audio& other) = delete;
		Audio& operator=(Audio&& other) noexcept = delete;

		void Play() const;
		void Load() const;

		void SetVolume(float volume);
		int GetVolume() const;
	private:
		class AudioImpl;
		AudioImpl* pImlp{ };
	};
}

class dae::Audio::AudioImpl
{
public:
	AudioImpl(const std::string& path);
	~AudioImpl();

	bool Play();
	void Load();

	void SetVolume(int volume);
	int GetVolume() const;
private:
	//Mix_Chunk* m_pChunk{};
	std::string m_Path;
};