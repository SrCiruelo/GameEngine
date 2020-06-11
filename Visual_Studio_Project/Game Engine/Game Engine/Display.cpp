#include "Display.h"
#include <stdexcept>

Display::Display(int width, int height, const std::string& window_title) :width{ width }, height{ height }, is_closed{false}{

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	window = SDL_CreateWindow(
		window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);


	if (window == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}

	glcontext = SDL_GL_CreateContext(window);

	GLenum err = glewInit();

	if (GLEW_OK != err) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		printf("%s", glewGetErrorString(err));
		throw std::runtime_error("Glew no se ha podido inicializar");
	}
	glViewport(0, 0, 640, 480);
}

void Display::Update() {

	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			is_closed = true;
		}
	}
	SDL_GL_SwapWindow(window);
}

bool Display::isClosed() {
	return is_closed;
}

Display::~Display() {
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}