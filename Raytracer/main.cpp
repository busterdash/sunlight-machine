#include <iostream>
#include "raytracer.hpp"
#include "windows_bitmap.hpp"
#include "smd_model_reader.hpp"
#include <cmath>

int main(int argc, char* argv[])
{
	windows_bitmap* wb = new windows_bitmap("asdf.bmp",128,128);
	smd_model_reader* smr = new smd_model_reader("cube.smd");

	std::cout << smr->get_triangle_count() << std::endl;
	
	float pitch = 48.8f - 90.0f;
	float yaw = 40.0f + 180.0f;
	float const PI = 3.141592f;
	float sx = cos(yaw*PI/180) * cos(pitch*PI/180);
	float sy = sin(yaw*PI/180) * cos(pitch*PI/180);
	float sz = sin(pitch*PI/180);
	std::cout << sx << ' ' << sy << ' ' << sz << std::endl;
	vertex* sun = new vertex(1.5f,0.5f,2.5f,sx,sy,sz,0.0f,0.0f);
	vertex* hit = new vertex();
	
	for (unsigned int i = 0; i < smr->get_triangle_count(); i++)
	{
		bool rayhit = raytracer::get_intersection(sun, smr->get_triangle(i), hit);
	
		if (rayhit)
		{
			std::cout << hit->x << " " << hit->y << " " << hit->z << std::endl;
		}
		else
		{
			continue;
		}
		
		raytracer::transform_trace_to_uv(smr->get_triangle(i), hit);
		
		wb->get_dib()->get_image()->set_pixel((unsigned int)round(hit->u*128.0f),(unsigned int)round(128.0f-hit->v*128.0f), 0x000000);
	}

	wb->save();
	
	delete wb;
	delete smr;
	delete sun;
	delete hit;
	return 0;
}
