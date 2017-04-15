#ifndef _VERTEX_H
#define _VERTEX_H

#include <string>

struct vertex
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
	float u;
	float v;
	vertex(float pos_x, float pos_y, float pos_z, float normal_x, float normal_y, float normal_z, float tex_x, float tex_y);
	vertex(float pos_x, float pos_y, float pos_z);
	vertex();
	~vertex();
};

#endif
