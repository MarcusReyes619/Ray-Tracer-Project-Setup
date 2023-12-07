#pragma once
#include <string>
#include <SDL.h>
class Renderer{

public:
	Renderer() = default;
	bool Initialize();
	void ShutDown();
	bool CreateWindow(const std::string& title, int width, int height);
	void PresentCanvas(const class Canvas& canvas);


	friend class Canvas;

private:
	SDL_Renderer* m_renderer = nullptr;
	SDL_Window* m_window = nullptr;

	int m_width = 0;
	int m_height = 0;

};	