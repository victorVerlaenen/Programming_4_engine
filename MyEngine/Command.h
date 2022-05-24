#pragma once
namespace dae
{
	class GameObject;
	class Command
	{
	public:
		Command(GameObject* actor);
		virtual ~Command() = default;
		Command(const Command& other) = delete;
		Command(Command&& other) noexcept = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) noexcept = delete;

		virtual void Execute() = 0;
	private:
		GameObject* m_Actor;
	protected:
		GameObject* GetActor() const;
	};
}
