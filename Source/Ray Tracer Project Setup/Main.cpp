#pragma once
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"

#include <iostream>

int main(int argc, char* argv[]) {
	 std::cout << "Hello World";


	 Renderer r;
	 r.Initialize();

	 ray::seedRandom((int)time(nullptr));

	 r.CreateWindow("ray trace", 400, 300);
	 Canvas canvas(400, 300, r);

	 float aspectRatio = (float)canvas.Getsize().x / (float)canvas.Getsize().y;
	 std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	 Scene scene(20); // sky color could be set with the top and bottom color
	 scene.SetCamera(camera);

	// create material
	 auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	 auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	 // create objects -> add to scene
	 for (int i = 0; i < 10; i++)
	 {
		 //std::shared_ptr<Material> material = (<use rand() and %to randomly pick the material>) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		 std::shared_ptr<Material> material = (rand() % 2) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		 auto sphere = std::make_unique<Sphere>(ray::randomInUnitSphere(), 0.1f, material);
		 scene.AddObject(std::move(sphere));
	 }

	 canvas.Clear({ 0, 0, 0, 1 });
	 scene.Render(canvas, 50);
	 canvas.Update();

	 bool quit = false;
	 while (!quit) {
	
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