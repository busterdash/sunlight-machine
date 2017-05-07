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
int resolution = 512;
float spread = 1.0f;

void point_trans_rot_z(float angle, float* x, float* y, float* z);
void point_trans_rot_y(float angle, float* x, float* y, float* z);
void point_trans_rot_yz(float pitch, float yaw, float* x, float* y, float* z);
void perform_raytrace(std::string smd_in, std::string bmp_out, int tex_width, int tex_height, float sun_pitch, float sun_yaw);

int main(int argc, char** argv)
{
	std::string inpath;
	std::string outpath;
	int img_width = 512;
	int img_height = 512;
	float yaw = 15.0f;
	float pitch = 30.0f;

	for (int i = 1; i < argc; i++) //Deal with flags.
	{
		if (!strcasecmp(argv[i],"-in"))
			inpath = std::string(argv[i+1]);
		else if (!strcasecmp(argv[i],"-out"))
			outpath = std::string(argv[i+1]);
		else if (!strcasecmp(argv[i],"-width"))
			img_width = atoi(argv[i+1]);
		else if (!strcasecmp(argv[i],"-height"))
			img_height = atoi(argv[i+1]);
		else if (!strcasecmp(argv[i],"-yaw"))
			yaw = atof(argv[i+1]);
		else if (!strcasecmp(argv[i],"-pitch"))
			pitch = atof(argv[i+1]);
		else if (!strcasecmp(argv[i],"-resolution"))
			resolution = atoi(argv[i+1]);
		else if (!strcasecmp(argv[i],"-spread"))
			spread = atof(argv[i+1]);
	}
	
	perform_raytrace(inpath,outpath,img_width,img_height,pitch,yaw);
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

void perform_raytrace(std::string smd_in, std::string bmp_out, int tex_width, int tex_height, float sun_pitch, float sun_yaw)
{
	windows_bitmap* wb = new windows_bitmap(bmp_out,tex_width,tex_height);
	smd_model_reader* smr = new smd_model_reader(smd_in);
	
	const float radianizer = PI/180;
	float sun_dist = smr->get_max_coordinate() + 1.0f; //Add one so that sun rays are a little farther than geometry.
	float pitch = sun_pitch - 90.0f;
	float inv_pitch = sun_pitch + 90.0f;
	float yaw = sun_yaw + 180.0f;
	float sdx = cos(yaw*radianizer) * cos(pitch*radianizer); //Sun direction.
	float sdy = sin(yaw*radianizer) * cos(pitch*radianizer);
	float sdz = sin(pitch*radianizer);
	float spz = sin(inv_pitch*radianizer) * sun_dist;
	float spx = cos(yaw*radianizer) * cos(inv_pitch*radianizer) * sun_dist;
	float spy = sin(yaw*radianizer) * cos(inv_pitch*radianizer) * sun_dist;
	vertex* hit = new vertex();
	vertex* sun = new vertex(spx,spy,spz,sdx,sdy,sdz,0.0f,0.0f);
	float closest_tri = -1.0f;
	
	for (int py = 0; py < resolution; py++)
	{
		for (int px = 0; px < resolution; px++) //Create several rays.
		{
			float ox, oy, oz;
			ox = 0.0f; oy = (float)(px-(resolution/2))/(resolution/8)*spread; oz = (float)(py-(resolution/2))/(resolution/8)*spread;
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
				wb->get_dib()->get_image()->set_pixel((unsigned int)floor(hit->u*tex_width), (unsigned int)floor(tex_height-hit->v*tex_height), 0xffffff);
			}
			
			closest_tri = -1.0f;
		}
	}

	wb->save(); //This stays outside any raytrace operations, or else it won't write the image at all.

	delete wb;
	delete smr;
	delete sun;
	delete hit;
}

