#pragma once
#include "Renderer.h"
#include <iostream>
int main(int argc, char* argv[]) {
	 std::cout << "Hello World";


	 Renderer r;
	 r.Initialize();

	 r.CreateWindow("ray trace", 400, 400);

	 bool quit = false;
	 while (!quit) {
		 SDL_Event event;
		 SDL_PollEvent(&event);
		 switch (event.type) {
		 case SDL_QUIT:
			 quit = true;
			 break;
		 }

	 }

	 r.ShutDown();

	 return 0;
}