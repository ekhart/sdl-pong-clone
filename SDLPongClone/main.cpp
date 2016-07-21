#include <iostream>
#include <string>
#include <SDL.h>

#include "res_path.h"
#include "cleanup.h"

using namespace std;

int main(int, char**) {

	// startin sdl
	if (SDL_Init(SDL_INIT_VIDEO)) {
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
	}

	// opening a window
	auto *window = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (!window) {
		cout << "SDL_CreateWindow error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 2;
	}

	// creating a renderer
	auto flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	auto *renderer = SDL_CreateRenderer(window, -1, flags);
	if (renderer == nullptr) {
		cleanup(window);
		cout << "SDL_CreateRenderer error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 3;
	}

	// Loading a Bitmap Image
	string imagePath = "hello.bmp";
	SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
	if (!bmp) {
		cleanup(renderer, window);
		cout << "SDL_LoadBMP error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 4;
	}

	auto *texture = SDL_CreateTextureFromSurface(renderer, bmp);
	SDL_FreeSurface(bmp);
	if (!texture) {
		cleanup(renderer, window);
		cout << "SDL_CreateTextureFromSurface error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 5;
	}

	// Drawing the Texture
	for (int i = 0; i < 3; ++i) {
		// first clear the renderer
		SDL_RenderClear(renderer);
		// draw the texture
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		// update the screen
		SDL_RenderPresent(renderer);
		// take a quick break after all that hard work
		SDL_Delay(1000);
	}

	// Cleaning Up
	cleanup(texture, renderer, window);
	SDL_Quit();

	return 0;
}