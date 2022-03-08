#pragma once
#include "Component.h"
#include "GameObject.h"

namespace dae
{
	class ImGuiComponent : public Component
	{
	public:
		ImGuiComponent(GameObject* pOwner, SDL_Window* pWindow);
		~ImGuiComponent() override;

		void Init(SDL_Window* pWindow);
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;


		ImGuiComponent(const ImGuiComponent& other) = delete;
		ImGuiComponent(ImGuiComponent&& other) = delete;
		ImGuiComponent& operator=(const ImGuiComponent& other) = delete;
		ImGuiComponent& operator=(ImGuiComponent&& other) = delete;
	private:
		struct Transform
		{
			float matrix[16] = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1 };
		};
		class GameObject3D
		{
		public:
			Transform transform;
			int ID;
		};
		class GameObject3DAlt
		{
		public:
			Transform* transform;
			int ID;
		};

		SDL_Window* m_pWindow{ nullptr };

		void Exercise1();
		void Exercise2();

		std::vector<float> m_XData = { 2,4,8,16,32,64,128,256,512,1024 };

		int m_SamplesPlotOne{ 1 };
		std::vector<float> m_YDataPlotOne = { 0,0,0,0,0,0,0,0,0,0 };
		float m_ScaleMaxPlotOne{ 0 };

		int m_SamplesPlotTwoAndThree{ 1 };
		std::vector<float> m_YDataPlotTwo = { 0,0,0,0,0,0,0,0,0,0 };
		std::vector<float> m_YDataPlotThree = { 0,0,0,0,0,0,0,0,0,0 };
		float m_ScaleMaxPlotTwo{ 0 };
		float m_ScaleMaxPlotThree{ 0 };
	};
}