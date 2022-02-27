#include "MiniginPCH.h"
#include "Renderer.h"

#include <chrono>

#include "SceneManager.h"
#include "Texture2D.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_opengl2.h"
#include "Imgui/imgui_impl_sdl.h"
#include "Imgui/imgui_plot.h"
//#include "Imgui/imgui_plot.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();
	ShowExcersise1();
	ShowExcersise2();
	//ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_Renderer);
}

//Using globals for now, gotta ask teacher about this
//I guess it should not be in the renderer maybe
int count{ 1 };
std::vector<float> xData = { 2,4,8,16,32,64,128,256,512,1024 };
std::vector<float> yData = { 0,0,0,0,0,0,0,0,0,0 };
float scaleMax;

void dae::Renderer::ShowExcersise1() const
{
	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(250, 250), ImGuiCond_FirstUseEver);
	
	if (!ImGui::Begin("Exercise 1"))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	ImGui::InputInt("#samples", &count);
	if (ImGui::Button("Trash the cache") && count >= 1)
	{
		yData.clear();
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
			for (int k{}; k < count; k++)
			{
				startTime = std::chrono::high_resolution_clock::now();
				for (int i{ 0 }; i < bufferLength; i += j) buffer[i] *= 2;
				endTime = std::chrono::high_resolution_clock::now();
				deltaTime = float(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count());
				avg += deltaTime;
			}
			avg /= count;
			//std::cout << j << " (" << count << " samples): " << avg << std::endl;
			yData.push_back(avg);
		}
		std::vector<float> sortedYCopy{ yData };
		std::sort(sortedYCopy.begin(), sortedYCopy.end(), std::greater<float>());
		scaleMax = sortedYCopy[0];
		delete[] buffer;
	}
	ImGui::PlotConfig conf;
	conf.values.xs = xData.data(); // this line is optional
	conf.values.ys = yData.data();
	conf.values.count = 10;
	conf.values.color = ImColor{ 255,255,0 };
	conf.scale.min = 0;
	conf.scale.max = scaleMax;
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = true;
	conf.grid_y.show = true;
	conf.frame_size = ImVec2(200, 200);
	conf.line_thickness = 2.f;

	ImGui::Plot("Plot", conf);

	ImGui::End();
}

int count2{ 1 };
std::vector<float> yData2 = { 0,0,0,0,0,0,0,0,0,0 };
std::vector<float> yData3 = { 0,0,0,0,0,0,0,0,0,0 };
float scaleMax2;
float scaleMax3;

void dae::Renderer::ShowExcersise2() const
{
	ImGui::SetNextWindowPos(ImVec2(270, 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(250, 250), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Exercise 2"))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	ImGui::InputInt("#samples", &count2);
	if (ImGui::Button("Trash the cache with GameObject3D") && count2 >= 1)
	{
		yData2.clear();
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
			for (int k{}; k < count2; k++)
			{
				startTime = std::chrono::high_resolution_clock::now();
				for (int i{ 0 }; i < bufferLength; i += j) objectBuffer[i].ID *= 2;
				endTime = std::chrono::high_resolution_clock::now();
				deltaTime = float(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count());
				avg += deltaTime;
			}
			avg /= count2;
			yData2.push_back(avg);
		}
		std::vector<float> sortedYCopy{ yData2 };
		std::sort(sortedYCopy.begin(), sortedYCopy.end(), std::greater<float>());
		scaleMax2 = sortedYCopy[0];

		delete[] objectBuffer;
	}
	ImGui::PlotConfig conf2;
	conf2.values.xs = xData.data(); // this line is optional
	conf2.values.ys = yData2.data();
	conf2.values.count = 10;
	conf2.values.color = ImColor{ 255,0,255 };
	conf2.scale.min = 0;
	conf2.scale.max = scaleMax2;
	conf2.tooltip.show = true;
	conf2.tooltip.format = "x=%.2f, y=%.2f";
	conf2.grid_x.show = true;
	conf2.grid_y.show = true;
	conf2.frame_size = ImVec2(200, 200);
	conf2.line_thickness = 2.f;

	ImGui::Plot("Plot", conf2);


	//AltObject
	if (ImGui::Button("Trash the cache with GameObject3DAlt") && count2 >= 1)
	{
		yData3.clear();
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
			for (int k{}; k < count2; k++)
			{
				startTime = std::chrono::high_resolution_clock::now();
				for (int i{ 0 }; i < bufferLength; i += j) objectBuffer[i].ID *= 2;
				endTime = std::chrono::high_resolution_clock::now();
				deltaTime = float(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count());
				avg += deltaTime;
			}
			avg /= count2;
			//std::cout << j << " (" << count << " samples): " << avg << std::endl;
			yData3.push_back(avg);
		}
		std::vector<float> sortedYCopy{ yData3 };
		std::sort(sortedYCopy.begin(), sortedYCopy.end(), std::greater<float>());
		scaleMax3 = sortedYCopy[0];

		delete[] objectBuffer;
	}
	ImGui::PlotConfig conf3;
	conf3.values.xs = xData.data(); // this line is optional
	conf3.values.ys = yData3.data();
	conf3.values.count = 10;
	conf3.values.color = ImColor{ 0,255,255 };
	conf3.scale.min = 0;
	conf3.scale.max = scaleMax3;
	conf3.tooltip.show = true;
	conf3.tooltip.format = "x=%.2f, y=%.2f";
	conf3.grid_x.show = true;
	conf3.grid_y.show = true;
	conf3.frame_size = ImVec2(200, 200);
	conf3.line_thickness = 2.f;

	ImGui::Plot("Plot", conf3);

	//Combined
	ImGui::Text("Combined");
	const float* yDataCombined[] = { yData2.data(), yData3.data() };
	ImU32 colors[2] = { ImColor{255,0,255}, ImColor{0,255,255}};

	ImGui::PlotConfig conf4;
	conf4.values.xs = xData.data(); // this line is optional
	conf4.values.ys_list = yDataCombined;
	conf4.values.ys_count = 2;
	conf4.values.count = 10;
	conf4.values.colors = colors;
	conf4.scale.min = 0;
	conf4.scale.max = std::max(scaleMax3, scaleMax2);
	conf4.tooltip.show = true;
	conf4.tooltip.format = "x=%.2f, y=%.2f";
	conf4.grid_x.show = true;
	conf4.grid_y.show = true;
	conf4.frame_size = ImVec2(200, 200);
	conf4.line_thickness = 2.f;

	ImGui::Plot("Plot", conf4);
	ImGui::End();
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}
