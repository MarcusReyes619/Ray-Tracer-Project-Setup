#pragma once
#include <stdlib.h> 
#include  <cstdlib>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>


namespace ray{

inline void seedRandom(unsigned int seed)
{

	srand(seed);
}

inline float random01()
{
		return (float)rand() / (float)RAND_MAX;
}

inline float random(float min, float max)
{


	if (min > max) std::swap(min, max);
	return min + (random01() * (max - min));


}


inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max) {

	float x, y, z;

	x = random(min.x, max.x);
	y = random(min.y, max.y);
	z = random(min.z, max.z);

	return glm::vec3(x, y, z);



}

inline glm::vec3 randomInUnitSphere()
{
	glm::vec3 v;
	// generate random vectors between -1 <-> +1, return vector if length is less than 1
	do
	{
		//v = get random vector between(-1, -1, -1) and (1, 1, 1)
		glm::vec3 neg = glm::vec3(-1, -1, -1);
		glm::vec3 pos = glm::vec3(1, 1, 1);
		v = random(neg, pos);
	} while (glm::length2(v) >= 1.0f);

		return v;
}

}