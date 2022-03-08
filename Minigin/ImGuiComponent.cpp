#include "MiniginPCH.h"
#include "ImGuiComponent.h"
#include <chrono>
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_opengl2.h"
#include "Imgui/imgui_impl_sdl.h"
#include "Imgui/imgui_plot.h"

dae::ImGuiComponent::ImGuiComponent(GameObject* pOwner, SDL_Window* pWindow)
	:Component{ pOwner }
	, m_pWindow{ pWindow }
{
	Init(m_pWindow);
}

void dae::ImGuiComponent::Init(SDL_Window* pWindow)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(pWindow, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::ImGuiComponent::Update()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();

	Exercise1();
	Exercise2();
}

void dae::ImGuiComponent::FixedUpdate()
{

}

void dae::ImGuiComponent::Render() const
{
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void dae::ImGuiComponent::Exercise1()
{
	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(250, 250), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Exercise 1"))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	ImGui::InputInt("#samples", &m_SamplesPlotOne);
	if (ImGui::Button("Trash the cache") && m_SamplesPlotOne >= 1)
	{
		m_YDataPlotOne.clear();
		const int bufferLength{ int(std::pow(2,26)) };
		int* buffer = new int[bufferLength] {};
		for (int i{}; i < bufferLength; i++)
		{
			buffer[i] = 5;
		}

		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;
		float deltaTime;
		for (int j{ 1 }; j <= 1024; j *= 2)
		{
			float avg{};
			for (int k{}; k < m_SamplesPlotOne; k++)
			{
				startTime = std::chrono::high_resolution_clock::now();
				for (int i{ 0 }; i < bufferLength; i += j) buffer[i] *= 2;
				endTime = std::chrono::high_resolution_clock::now();
				deltaTime = float(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count());
				avg += deltaTime;
			}
			avg /= m_SamplesPlotOne;
			//std::cout << j << " (" << count << " samples): " << avg << std::endl;
			m_YDataPlotOne.push_back(avg);
		}
		std::vector<float> sortedYCopy{ m_YDataPlotOne };
		std::sort(sortedYCopy.begin(), sortedYCopy.end(), std::greater<float>());
		m_ScaleMaxPlotOne = sortedYCopy[0];
		delete[] buffer;
	}

	ImGui::PlotConfig conf;
	conf.values.xs = m_XData.data(); // this line is optional
	conf.values.ys = m_YDataPlotOne.data();
	conf.values.count = 10;
	conf.values.color = ImColor{ 255,255,0 };
	conf.scale.min = 0;
	conf.scale.max = m_ScaleMaxPlotOne;
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = true;
	conf.grid_y.show = true;
	conf.frame_size = ImVec2(200, 200);
	conf.line_thickness = 2.f;

	ImGui::Plot("PlotOne", conf);

	ImGui::End();
}

void dae::ImGuiComponent::Exercise2()
{
	ImGui::SetNextWindowPos(ImVec2(270, 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(250, 250), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Exercise 2"))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	ImGui::InputInt("#samples", &m_SamplesPlotTwoAndThree);
	if (ImGui::Button("Trash the cache with GameObject3D") && m_SamplesPlotTwoAndThree >= 1)
	{
		m_YDataPlotTwo.clear();
		const int bufferLength{ int(std::pow(2,26)) };
		GameObject3D* objectBuffer = new GameObject3D[bufferLength]{};
		for (int i{}; i < bufferLength; i++)
		{
			objectBuffer[i].ID = 5;
		}

		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;
		float deltaTime;
		for (int j{ 1 }; j <= 1024; j *= 2)
		{
			float avg{};
			for (int k{}; k < m_SamplesPlotTwoAndThree; k++)
			{
				startTime = std::chrono::high_resolution_clock::now();
				for (int i{ 0 }; i < bufferLength; i += j) objectBuffer[i].ID *= 2;
				endTime = std::chrono::high_resolution_clock::now();
				deltaTime = float(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count());
				avg += deltaTime;
			}
			avg /= m_SamplesPlotTwoAndThree;
			m_YDataPlotTwo.push_back(avg);
		}
		std::vector<float> sortedYCopy{ m_YDataPlotTwo };
		std::sort(sortedYCopy.begin(), sortedYCopy.end(), std::greater<float>());
		m_ScaleMaxPlotTwo = sortedYCopy[0];

		delete[] objectBuffer;
	}
	ImGui::PlotConfig conf2;
	conf2.values.xs = m_XData.data(); // this line is optional
	conf2.values.ys = m_YDataPlotTwo.data();
	conf2.values.count = 10;
	conf2.values.color = ImColor{ 255,0,255 };
	conf2.scale.min = 0;
	conf2.scale.max = m_ScaleMaxPlotTwo;
	conf2.tooltip.show = true;
	conf2.tooltip.format = "x=%.2f, y=%.2f";
	conf2.grid_x.show = true;
	conf2.grid_y.show = true;
	conf2.frame_size = ImVec2(200, 200);
	conf2.line_thickness = 2.f;

	ImGui::Plot("Plot", conf2);


	//AltObject
	if (ImGui::Button("Trash the cache with GameObject3DAlt") && m_SamplesPlotTwoAndThree >= 1)
	{
		m_YDataPlotThree.clear();
		const int bufferLength{ int(std::pow(2,26)) };
		GameObject3DAlt* objectBuffer = new GameObject3DAlt[bufferLength]{};
		for (int i{}; i < bufferLength; i++)
		{
			objectBuffer[i].ID = 5;
		}

		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;
		float deltaTime;
		for (int j{ 1 }; j <= 1024; j *= 2)
		{
			float avg{};
			for (int k{}; k < m_SamplesPlotTwoAndThree; k++)
			{
				startTime = std::chrono::high_resolution_clock::now();
				for (int i{ 0 }; i < bufferLength; i += j) objectBuffer[i].ID *= 2;
				endTime = std::chrono::high_resolution_clock::now();
				deltaTime = float(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count());
				avg += deltaTime;
			}
			avg /= m_SamplesPlotTwoAndThree;
			//std::cout << j << " (" << count << " samples): " << avg << std::endl;
			m_YDataPlotThree.push_back(avg);
		}
		std::vector<float> sortedYCopy{ m_YDataPlotThree };
		std::sort(sortedYCopy.begin(), sortedYCopy.end(), std::greater<float>());
		m_ScaleMaxPlotThree = sortedYCopy[0];

		delete[] objectBuffer;
	}
	ImGui::PlotConfig conf3;
	conf3.values.xs = m_XData.data(); // this line is optional
	conf3.values.ys = m_YDataPlotThree.data();
	conf3.values.count = 10;
	conf3.values.color = ImColor{ 0,255,255 };
	conf3.scale.min = 0;
	conf3.scale.max = m_ScaleMaxPlotThree;
	conf3.tooltip.show = true;
	conf3.tooltip.format = "x=%.2f, y=%.2f";
	conf3.grid_x.show = true;
	conf3.grid_y.show = true;
	conf3.frame_size = ImVec2(200, 200);
	conf3.line_thickness = 2.f;

	ImGui::Plot("Plot", conf3);

	//Combined
	ImGui::Text("Combined");
	const float* yDataCombined[] = { m_YDataPlotTwo.data(), m_YDataPlotThree.data() };
	ImU32 colors[2] = { ImColor{255,0,255}, ImColor{0,255,255} };

	ImGui::PlotConfig conf4;
	conf4.values.xs = m_XData.data(); // this line is optional
	conf4.values.ys_list = yDataCombined;
	conf4.values.ys_count = 2;
	conf4.values.count = 10;
	conf4.values.colors = colors;
	conf4.scale.min = 0;
	conf4.scale.max = std::max(m_ScaleMaxPlotThree, m_ScaleMaxPlotTwo);
	conf4.tooltip.show = true;
	conf4.tooltip.format = "x=%.2f, y=%.2f";
	conf4.grid_x.show = true;
	conf4.grid_y.show = true;
	conf4.frame_size = ImVec2(200, 200);
	conf4.line_thickness = 2.f;

	ImGui::Plot("Plot", conf4);
	ImGui::End();
}

dae::ImGuiComponent::~ImGuiComponent()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}