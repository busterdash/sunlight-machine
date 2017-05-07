#ifndef _GEOMETRY_HPP
#define _GEOMETRY_HPP

struct vertex
{
	float x; //World position.
	float y;
	float z;
	float nx; //Surface normal.
	float ny;
	float nz;
	float u; //Texture coordinates.
	float v;
	vertex(float pos_x, float pos_y, float pos_z, float normal_x, float normal_y, float normal_z, float tex_x, float tex_y);
	vertex(float pos_x, float pos_y, float pos_z);
	vertex();
	~vertex();
};

struct triangle
{
	vertex* v[3];
	triangle(vertex* v1, vertex* v2, vertex* v3);
	~triangle();
};

#endif
