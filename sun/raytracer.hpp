/*==============================================================================================

	raytracer.hpp
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

#ifndef _RAYTRACER_HPP
#define _RAYTRACER_HPP

#include "geometry.hpp"

class raytracer
{
	private:
		static void vec(float* a, float* b, float* c);
		static void cross_product(float* a, float* b, float* c);
		static float dot_product(float* a, float* b);
		static float distance_formula_3d(float x1, float y1, float z1, float x2, float y2, float z2);
		static void alpha_beta_to_cartesian(float x1, float y1, float x2, float y2, float percent, float* outx, float* outy);
		static bool process_intersection(float* p, float* d, float* v0, float* v1, float* v2, float* t);
	public:
		static bool get_intersection(vertex* ray, triangle* tri, vertex* intersect, float* dist);
		static void transform_trace_to_uv(triangle* t, vertex* hit);
};

#endif
