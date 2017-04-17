#include <iostream>
#include "raytracer.h"
#include "windows_bitmap.h"
#include <cmath>

int main(int argc, char* argv[])
{
	windows_bitmap* wb = new windows_bitmap("asdf.bmp",128,128);
	vertex* v0 = new vertex(0.0f,2.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f);
	vertex* v1 = new vertex(-3.0f,-2.0f,0.0f,0.0f,0.0f,0.0f,4.0f,4.0f);
	vertex* v2 = new vertex(3.0f,-2.0f,0.0f,0.0f,0.0f,0.0f,1.0f,4.0f);
	triangle* tri = new triangle(v0,v1,v2);
	
	vertex* sun = new vertex(0.0f,0.0f,4.0f,0.0f,0.1f,-1.0f,0.0f,0.0f);
	vertex* hit = new vertex();

	bool rayhit = raytracer::get_intersection(sun, tri, hit);
	
	if (rayhit)
	{
		std::cout << hit->x << " " << hit->y << " " << hit->z << std::endl;
	}
	else
	{
		std::cout << "NO HIT" << std::endl;
	}
	
	raytracer::transform_trace_to_uv(tri, hit);
	
	wb->get_dib()->get_image()->set_pixel((unsigned int)round(hit->u*32.0f),(unsigned int)round(hit->v*32.0f), 0x000000);
	wb->save();
	
	delete wb;
	delete sun;
	delete tri;
	delete hit;
	return 0;
}
