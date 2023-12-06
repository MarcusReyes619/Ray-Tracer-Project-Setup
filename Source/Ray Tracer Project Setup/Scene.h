#pragma once

#include "Color.h"
#include "Camera.h"
#include <memory>
#include "Object.h"
#include <vector>
class Scene
{
public:
	Scene() = default;
	Scene(const color3_t& topColor, const color3_t& bottomColor) :
		m_topColor{ topColor },
		m_bottomColor{ bottomColor }
	{}
	Scene(int depth = 5) : m_depth{ depth } {}
	Scene(int depth, const color3_t& topColor, const color3_t& bottomColor) :
		m_depth{ depth },
		m_topColor{ topColor },
		m_bottomColor{ bottomColor }
	{}

	void Render(class Canvas& canvas, int numSamples);
	color3_t Trace(const ray_t& ray);
	color3_t Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit);
	color3_t Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth);

	void AddObject(std::unique_ptr<Object> object) { m_objects.push_back(std::move(object)); }

	void SetCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }

private:
	//<shared pointer of Camera> m_camera;
	std::shared_ptr<Camera> m_camera;

	color3_t m_topColor{ 0 };
	color3_t m_bottomColor{ 1 };

	std::vector<std::unique_ptr<Object>> m_objects;
	int m_depth{ 5 };

};
