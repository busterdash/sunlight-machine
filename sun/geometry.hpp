/*==============================================================================================

	geometry.hpp
	Copyright 2019 Buster Schrader

	This file is part of The Sunlight Machine.

    The Sunlight Machine is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    The Sunlight Machine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Sunlight Machine.  If not, see <https://www.gnu.org/licenses/>.
	
==============================================================================================*/

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
