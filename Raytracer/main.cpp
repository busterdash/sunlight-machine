#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <sys/time.h>

#include "raytracer.hpp"
#include "windows_bitmap.hpp"
#include "smd_model_reader.hpp"

float const PI = 3.141593f;
void point_trans_rot_z(float angle, float* x, float* y, float* z);
void point_trans_rot_y(float angle, float* x, float* y, float* z);

int main(int argc, char* argv[])
{
	windows_bitmap* wb = new windows_bitmap("asdf.bmp",512,512);
	smd_model_reader* smr = new smd_model_reader("new.smd");
	
	float pitch = 30.0f - 90.0f;
	float yaw = 15.0f + 180.0f;
	float sdx = cos(yaw*PI/180) * cos(pitch*PI/180); //Sun direction
	float sdy = sin(yaw*PI/180) * cos(pitch*PI/180);
	float sdz = sin(pitch*PI/180);
	vertex* hit = new vertex();
	vertex* sun = new vertex(2.0f,1.0f,4.0f,sdx,sdy,sdz,0.0f,0.0f);
	float closest_tri = -1.0f;
	
	for (unsigned int py = 0; py < 512; py++)
	{
		for (unsigned int px = 0; px < 512; px++) //Create several rays.
		{
			float ox, oy, oz;
			ox = 0.0f; oy = (float)(px - 128.0f) / 64.0f; oz = (float)(py - 128.0f) / 64.0f;
			point_trans_rot_y(-33.0f,&ox,&oy,&oz);
			point_trans_rot_z(30.0f,&ox,&oy,&oz);
			(*sun).x = 2.0f + ox;
			(*sun).y = 1.0f + oy;
			(*sun).z = 4.0f + oz;
			
			if (px == 128 && py == 128)
			{
				std::cout << sun->x << ' ' << sun->y << ' ' << sun->z << std::endl;
			}
			
			for (unsigned int i = 0; i < smr->get_triangle_count(); i++) //Check each triangle against ray.
			{
				float dist;
				bool rayhit = raytracer::get_intersection(sun, smr->get_triangle(i), hit, &dist);
			
				if (rayhit)
				{
					if (dist < closest_tri || closest_tri < 0)
					{
						raytracer::transform_trace_to_uv(smr->get_triangle(i), hit);
						closest_tri = dist;
					}
				}
			}
			
			if (closest_tri > 0) //Evaluates to false if we didn't hit anything.
			{
				wb->get_dib()->get_image()->set_pixel((unsigned int)round(hit->u*512.0f),(unsigned int)round(512.0f-hit->v*512.0f), 0xffffff);
			}
			
			closest_tri = -1.0f;
		}
	}

	wb->save(); //This stays outside any raytrace operations, or else it won't write the image at all.

	delete wb;
	delete smr;
	delete sun;
	delete hit;
	return 0;
}

void point_trans_rot_z(float angle, float* x, float* y, float* z)
{
	float ox, oy, oz, pc, ps;
	ox = *x;
	oy = *y;
	oz = *z;
	pc = cos(angle*PI/180);
	ps = sin(angle*PI/180);
	*x = (ox * pc) + (oy * -ps);
	*y = (ox * ps) + (oy * pc);
	*z = oz;
}

void point_trans_rot_y(float angle, float* x, float* y, float* z)
{
	float ox, oy, oz, pc, ps;
	ox = *x;
	oy = *y;
	oz = *z;
	pc = cos(angle*PI/180);
	ps = sin(angle*PI/180);
	*x = (ox * pc) + (oz * ps);
	*y = oy;
	*z = (ox * -ps) + (oz * pc);
}

