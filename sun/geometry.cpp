/*==============================================================================================

	geometry.cpp
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

#include "geometry.hpp"

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

triangle::triangle(vertex* v1, vertex* v2, vertex* v3)
{
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
}

triangle::~triangle()
{
	delete v[0];
	delete v[1];
	delete v[2];
}
