/*
 * main.cpp
 *
 *  Created on: Dec 5, 2015
 *      Author: bdero
 */

#include <iostream>
#include "SDL2/SDL.h"

int main(int argc, char **argv) {
	SDL_Window *window = nullptr;

	SDL_Surface *windowSurface = nullptr;
	SDL_Surface *imageSurface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error initializing video: " << SDL_GetError() << std::endl;
	} else {
		window = SDL_CreateWindow(
				"Window",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				640, 480,
				SDL_WINDOW_SHOWN);

		if (window == NULL) {
			std::cout << "Error creating SDL window: " << SDL_GetError() << std::endl;
		} else {
			windowSurface = SDL_GetWindowSurface(window);
			imageSurface = SDL_LoadBMP("images/test.bmp");

			if (imageSurface == NULL) {
				std::cout << "Unable to load image: " << SDL_GetError() << std::endl;
			} else {
				SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);

				SDL_UpdateWindowSurface(window);
				SDL_Delay(2000);
			}
		}
	}

	SDL_FreeSurface(imageSurface);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

