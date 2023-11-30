#pragma once
#include "Renderer.h"
#include <iostream>
#include "Random.h"
#include "Canvas.h"
int main(int argc, char* argv[]) {
	 std::cout << "Hello World";


	 Renderer r;
	 r.Initialize();

	 ray::seedRandom((int)time(nullptr));

	 r.CreateWindow("ray trace", 400, 300);
	 Canvas canvas(400, 300, r);


	 bool quit = false;
	 while (!quit) {
		 canvas.Clear({ 0, 0, 0, 1 });
		 for (int i = 0; i < 10000; i++) canvas.DrawPoint({ ray::random(0, canvas.Getsize().x), ray::random(0, canvas.Getsize().y) }, { ray::random(0,1),  ray::random(0,1), ray::random(0,1) , 1 });
		 canvas.Update();

		 r.PresentCanvas(canvas);
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