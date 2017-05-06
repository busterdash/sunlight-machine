#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <sys/time.h>

#include "raytracer.hpp"
#include "windows_bitmap.hpp"
#include "smd_model_reader.hpp"

float const PI = 3.141593f;
void point_trans_rot_z(float angle, float* x, float* y, float* z);
void point_trans_rot_y(float angle, float* x, float* y, float* z);
void point_trans_rot_yz(float pitch, float yaw, float* x, float* y, float* z);
void perform_raytrace(std::string smd_in, std::string bmp_out, int tex_width, int tex_height, float sun_pitch, float sun_yaw, int resolution);

int main(int argc, char** argv)
{
	std::string inpath;
	std::string outpath;
	int img_width = 512;
	int img_height = 512;
	int resolution = 512;
	float yaw = 15.0f;
	float pitch = 30.0f;

	for (int i = 1; i < argc; i++) //Deal with flags.
	{
		if (!stricmp(argv[i],"-in"))
			inpath = std::string(argv[i+1]);
		else if (!stricmp(argv[i],"-out"))
			outpath = std::string(argv[i+1]);
		else if (!stricmp(argv[i],"-width"))
			img_width = atoi(argv[i+1]);
		else if (!stricmp(argv[i],"-height"))
			img_height = atoi(argv[i+1]);
		else if (!stricmp(argv[i],"-resolution"))
			resolution = atoi(argv[i+1]);
		else if (!stricmp(argv[i],"-yaw"))
			yaw = atof(argv[i+1]);
		else if (!stricmp(argv[i],"-pitch"))
			pitch = atof(argv[i+1]);
	}
	
	perform_raytrace(inpath,outpath,img_width,img_height,pitch,yaw,resolution);
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

void perform_raytrace(std::string smd_in, std::string bmp_out, int tex_width, int tex_height, float sun_pitch, float sun_yaw, int resolution)
{
	windows_bitmap* wb = new windows_bitmap(bmp_out,tex_width,tex_height);
	smd_model_reader* smr = new smd_model_reader(smd_in);
	
	float pitch = sun_pitch - 90.0f;
	float inv_pitch = sun_pitch + 90.0f;
	float yaw = sun_yaw + 180.0f;
	float sdx = cos(yaw*PI/180) * cos(pitch*PI/180); //Sun direction.
	float sdy = sin(yaw*PI/180) * cos(pitch*PI/180);
	float sdz = sin(pitch*PI/180);
	float spz = sin(inv_pitch*PI/180) * 6.0f;
	float spx = cos(yaw*PI/180) * cos(inv_pitch*PI/180) * 6.0f;
	float spy = sin(yaw*PI/180) * cos(inv_pitch*PI/180) * 6.0f;
	vertex* hit = new vertex();
	vertex* sun = new vertex(spx,spy,spz,sdx,sdy,sdz,0.0f,0.0f);
	float closest_tri = -1.0f;
	
	for (int py = 0; py < resolution; py++)
	{
		for (int px = 0; px < resolution; px++) //Create several rays.
		{
			float ox, oy, oz;
			ox = 0.0f; oy = (float)(px-(resolution/2))/(resolution/8); oz = (float)(py-(resolution/2))/(resolution/8);
			point_trans_rot_y(-pitch,&ox,&oy,&oz);
			point_trans_rot_z(yaw,&ox,&oy,&oz);
			(*sun).x = spx + ox;
			(*sun).y = spy + oy;
			(*sun).z = spz + oz;
			
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
				wb->get_dib()->get_image()->set_pixel((unsigned int)round(hit->u*tex_width),(unsigned int)round(tex_height-hit->v*tex_height), 0xffffff);
			}
			
			closest_tri = -1.0f;
		}
	}

	wb->save(); //This stays outside any raytrace operations, or else it won't write the image at all.s

	delete wb;
	delete smr;
	delete sun;
	delete hit;
}

