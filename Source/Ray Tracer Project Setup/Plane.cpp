#include "Plane.h"
#include "MathUtls.h"


bool Plane::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit)
{
    // check dot product of ray direction and plane normal, if result is 0 then ray direction if parallel to plane
    // the dot product is 0 if the two vectors are perpendicular (90 degrees)
    float denominator = dot(ray.m_direction, m_normal);
    //if (<check if denominator is approximately() zero>)
    if (ray::approximately(denominator,0.0f))
    {
        return false; // ray direction and plane parallel, no intersection
    }

    // get t (distance) along ray direction to hit point
    float t = glm::dot(m_center - ray.m_origin, m_normal) / denominator;
    if (t < 0)
    {
        return false; // plane behind ray's origin, no intersection
    }

    // check if t is outside min and max distance
    //if (<check if t is outside the min and max distance <= || >= >)
    if (t <= minDistance || t >= maxDistance )
    {
        return false;
    }

    // set raycast hit 
    raycastHit.distance = t;
    raycastHit.point = ray.GetPoint(t);
    raycastHit.normal = m_normal;
    raycastHit.material = GetMaterial();

    return true;
}
