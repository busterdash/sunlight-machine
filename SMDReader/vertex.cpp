#include "vertex.h"

vertex::vertex(float pos_x, float pos_y, float pos_z, float normal_x, float normal_y, float normal_z, float tex_x, float tex_y)
{
	x = pos_x;
	y = pos_y;
	z = pos_z;
	nx = normal_x;
	ny = normal_y;
	nz = normal_z;
	u = tex_x;
	v = tex_y;
}

vertex::vertex(float pos_x, float pos_y, float pos_z)
{
	x = pos_x;
	y = pos_y;
	z = pos_z;
	nx = 0.0f;
	ny = 0.0f;
	nz = 0.0f;
	u = 0.0f;
	v = 0.0f;
}

vertex::vertex()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	nx = 0.0f;
	ny = 0.0f;
	nz = 0.0f;
	u = 0.0f;
	v = 0.0f;
}

vertex::~vertex()
{
}
