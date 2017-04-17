#include <iostream>
#include "raytracer.h"
#include "windows_bitmap.h"
#include "smd_model_reader.h"
#include <cmath>

int main(int argc, char* argv[])
{
	windows_bitmap* wb = new windows_bitmap("asdf.bmp",128,128);
	smd_model_reader* smr = new smd_model_reader("cube.smd");

	std::cout << smr->get_triangle_count() << std::endl;
	
	vertex* sun = new vertex(2.5f,2.0f,2.5f,-1.0f,-0.6f,-1.0f,0.0f,0.0f);
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
