#pragma once
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Mesh.h"

#include <iostream>

const int width = 400;
const int height = 300;
const int samples = 200;
const int depth = 6;



void InitScene01(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.Getsize().x / canvas.Getsize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = ray::random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ ray::random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ ray::random(0.5f, 1.0f) }, ray::random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, ray::random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ ray::random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = ray::random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + ray::random(-0.5f, 0.5f), radius, z + ray::random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.Getsize().x / canvas.Getsize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
}

void InitScene03(Scene& scene, const Canvas& canvas) {

	float aspectRatio = canvas.Getsize().x / canvas.Getsize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);
	scene.SetCamera(camera);

	auto material = std::make_shared<Lambertian>(color3_t{ 1 });
	/*auto mesh = std::make_unique<Mesh>(material);
	mesh->Load("models/cube-1.obj", (glm::vec3{ 1, 0, 0 }, glm::vec3{0, 1, 0 }, glm::vec3{ 1, 1, 1 }));
	scene.AddObject(std::move(mesh));*/


	//back
	auto backWall = std::make_unique<Mesh>(material);
	backWall->Load("models/quad-1.obj", glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 1, 0 }, glm::vec3{ 18, 18, 1 });
	scene.AddObject(std::move(backWall));


	//left
	material =std::make_shared<Lambertian>(color3_t{ 1.0f, 0, 0 });
	auto wallLeft = std::make_unique<Mesh>(material);
	wallLeft->Load("models/quad-1.obj", glm::vec3{ -4.0f, 0.0f, 0.0f }, glm::vec3{ 180, 270, 0 }, glm::vec3{ 11.99f, 12.0f, 0.5f });
	scene.AddObject(std::move(wallLeft));

	//right
	material = std::make_shared<Lambertian>(color3_t{ 0, 1.0f, 0 });
	auto wallRight = std::make_unique<Mesh>(material);
	wallRight->Load("models/quad-1.obj", glm::vec3{ 4.0f, 0.0f, 0.0f }, glm::vec3{ 180, 90, 0 }, glm::vec3{ 11.99f, 12.0f, 0.5f });
	scene.AddObject(std::move(wallRight));

	auto material2 = std::make_shared<Emissive>(glm::vec3{ 1.0f, 1.0f, 1.0f }, 5.0f);
	auto light = std::make_unique<Mesh>(material2);
	light->Load("models/cube-1.obj", glm::vec3{ 0.0f, 3.0f, 1.0f }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1.0f, 1.0f, 1.0f });
	scene.AddObject(std::move(light));

	//floor
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(plane));

	//celling
	auto celling = std::make_unique<Plane>(glm::vec3{ 0, 5, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(celling));


	auto sphere = std::make_unique<Sphere>(glm::vec3{1,1,5}, 1.0f, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(sphere));

	auto material3 = std::make_shared<Lambertian>(color3_t{ 1 });
	auto cube = std::make_unique<Mesh>(material3);
	cube->Load("models/cube-1.obj", glm::vec3{ -3.0f, 1.0f, 4.0f }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1.0f, 1.0f, 1.0f });
	scene.AddObject(std::move(cube));

}

void InitScene04(Scene& scene, const Canvas& canvas) {

	float aspectRatio = canvas.Getsize().x / canvas.Getsize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = ray::random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ ray::random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ ray::random(0.5f, 1.0f) }, ray::random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, ray::random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ ray::random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = ray::random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + ray::random(-0.5f, 0.5f), radius, z + ray::random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}
	auto material = std::make_shared<Metal>(color3_t{ ray::random(0.5f, 1.0f) }, ray::random(0, 0.5f));
	auto wallRight = std::make_unique<Mesh>(material);
	wallRight->Load("models/quad-1.obj", glm::vec3{ 4.0f, 0.0f, 0.0f }, glm::vec3{ 180, 90, 0 }, glm::vec3{ 11.99f, 12.0f, 0.5f });
	scene.AddObject(std::move(wallRight));

	auto material3 = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ ray::random(0, 360), 1.0f, 1.0f }), 5.0f);
	auto cube = std::make_unique<Mesh>(material3);
	cube->Load("models/cube-1.obj", glm::vec3{ -3.0f, 1.0f, 4.0f }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1.0f, 1.0f, 1.0f });
	scene.AddObject(std::move(cube));

	auto sphere = std::make_unique<Sphere>(glm::vec3{ 1,3,5 }, 1.0f, std::make_shared<Dielectric>(color3_t{ 1.0f }, ray::random(1.1f, 2)));
	scene.AddObject(std::move(sphere));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(plane));
}

int main(int argc, char* argv[]) {
	 std::cout << "Hello World";


	 Renderer r;
	 r.Initialize();

	 ray::seedRandom((int)time(nullptr));

	 r.CreateWindow("Ray Tracer", width, height);

	 Canvas canvas(width, height, r);

	 

	 //Scene scene(10); // sky color could be set with the top and bottom color
	 Scene scene(500, glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });

	// create material
	 auto lambertian = std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });
	 auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);




	 InitScene04(scene, canvas);
	

	 canvas.Clear({ 0, 0, 0, 1 });
	 scene.Render(canvas, samples, depth);
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