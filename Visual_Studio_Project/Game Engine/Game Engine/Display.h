#pragma once

#include <SDL.h>
#include <string>
#include <GL/glew.h>


class Display
{
private:
	int width;
	int height;
	SDL_Window* window;
	SDL_GLContext glcontext;
	bool is_closed;
public:
	Display(int width, int height,const std::string& window_title);
	void Update();
	bool isClosed();
	~Display();
};

