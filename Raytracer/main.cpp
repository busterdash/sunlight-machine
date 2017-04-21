#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <sys/time.h>

#include "raytracer.hpp"
#include "windows_bitmap.hpp"
#include "smd_model_reader.hpp"

int main(int argc, char* argv[])
{
	windows_bitmap* wb = new windows_bitmap("asdf.bmp",128,128);
	smd_model_reader* smr = new smd_model_reader("cube.smd");

	std::cout << smr->get_triangle_count() << std::endl;
	
	float pitch = 30.0f - 90.0f;
	float yaw = 15.0f + 180.0f;
	float const PI = 3.141592f;
	float sx = cos(yaw*PI/180) * cos(pitch*PI/180);
	float sy = sin(yaw*PI/180) * cos(pitch*PI/180);
	float sz = sin(pitch*PI/180);
	std::cout << sx << ' ' << sy << ' ' << sz << std::endl;
	vertex* sun = new vertex(1.0f,0.0f,4.0f,sx,sy,sz,0.0f,0.0f);
	vertex* hit = new vertex();
	float closest_dist = -1.0f;

	for (unsigned int i = 0; i < smr->get_triangle_count(); i++)
	{
		float dist;
		bool rayhit = raytracer::get_intersection(sun, smr->get_triangle(i), hit, &dist);
	
		if (rayhit)
		{
			std::cout << hit->x << " " << hit->y << " " << hit->z << std::endl;
			
			if (dist < closest_dist || closest_dist < 0)
			{
				raytracer::transform_trace_to_uv(smr->get_triangle(i), hit);
				closest_dist = dist;
			}
		}
	}
	
	if (closest_dist > 0) //Evaluates to false if we didn't hit anything.
	{
		wb->get_dib()->get_image()->set_pixel((unsigned int)round(hit->u*128.0f),(unsigned int)round(128.0f-hit->v*128.0f), 0xffffff);
	}
	
	wb->save(); //This stays outside any raytrace operations, or else it won't write the image at all.

	delete wb;
	delete smr;
	delete sun;
	delete hit;
	return 0;
}
