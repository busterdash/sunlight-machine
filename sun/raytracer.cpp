/*==============================================================================================

	raytracer.cpp
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

#include "raytracer.hpp"
#include <cmath>

void raytracer::vec(float* a, float* b, float* c)
{
	a[0] = b[0] - c[0];
	a[1] = b[1] - c[1];
	a[2] = b[2] - c[2];
}

void raytracer::cross_product(float* a, float* b, float* c)
{
	a[0] = b[1] * c[2] - c[1] * b[2];
	a[1] = b[2] * c[0] - c[2] * b[0];
	a[2] = b[0] * c[1] - c[0] * b[1];
}

float raytracer::dot_product(float* a, float* b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float raytracer::distance_formula_3d(float x1, float y1, float z1, float x2, float y2, float z2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
}

void raytracer::alpha_beta_to_cartesian(float x1, float y1, float x2, float y2, float percent, float* outx, float* outy)
{
	float dist = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	float dist_seg = dist * percent;
	*outx = (x2 - x1) * dist_seg / dist + x1;
	*outy = (y2 - y1) * dist_seg / dist + y1;
}

void raytracer::transform_trace_to_uv(triangle* t, vertex* hit)
{	
	//Naming: s->side, i->inner, a|b|c->vertex
	float sa, sb, sc, ia, ib, aa, ab, ad, sad, ida, ie, alpha, beta;
	const float PI = 3.1415926f;
	
	//Calculate distances between triangle sides and hit positions. This flattens the triangle to 2D space.
	sa = distance_formula_3d(t->v[1]->x, t->v[1]->y, t->v[1]->z, t->v[2]->x, t->v[2]->y, t->v[2]->z);
	sb = distance_formula_3d(t->v[0]->x, t->v[0]->y, t->v[0]->z, t->v[2]->x, t->v[2]->y, t->v[2]->z);
	sc = distance_formula_3d(t->v[0]->x, t->v[0]->y, t->v[0]->z, t->v[1]->x, t->v[1]->y, t->v[1]->z);
	ia = distance_formula_3d(t->v[0]->x, t->v[0]->y, t->v[0]->z, hit->x, hit->y, hit->z);
	ib = distance_formula_3d(t->v[1]->x, t->v[1]->y, t->v[1]->z, hit->x, hit->y, hit->z);

	//Calculate alpha and beta.
	aa = acos(((sc*sc)+(ia*ia)-(ib*ib))/(2.0f*sc*ia))/PI*180.0f;
	ab = acos(((sa*sa)+(sc*sc)-(sb*sb))/(2.0f*sa*sc))/PI*180.0f;
	ad = 180.0f-aa-ab;
	sad = sin(ad*PI/180.0f);
	ida = (sc*sin(ab*PI/180.0f))/sad;
	ie = (sc*sin(aa*PI/180.0f))/sad;
	alpha = ia/ida;
	beta = ie/sa;
	
	//Convert alpha and beta to UV coordinates.
	alpha_beta_to_cartesian(t->v[1]->u, t->v[1]->v, t->v[2]->u, t->v[2]->v, beta, &hit->u, &hit->v);
	alpha_beta_to_cartesian(t->v[0]->u, t->v[0]->v, hit->u, hit->v, alpha, &hit->u, &hit->v);
}

//Source of this function only: http://www.lighthouse3d.com/tutorials/maths/ray-triangle-intersection/
bool raytracer::process_intersection(float* p, float* d, float* v0, float* v1, float* v2, float* t)
{
	float e1[3], e2[3], h[3], s[3], q[3];
	float a, f, u, v;
	vec(e1,v1,v0);
	vec(e2,v2,v0);
	
	cross_product(h,d,e2);
	a = dot_product(e1,h);
	
	if (a > -0.00001 && a < 0.00001)
	{
		return false;	
	}
	
	f = 1 / a;
	vec(s,p,v0);
	u = f * (dot_product(s,h));
	
	if (u < 0.0 || u > 1.0)
	{
		return false;	
	}
	
	cross_product(q,s,e1);
	v = f * dot_product(d,q);
	
	if (v < 0.0 || u + v > 1.0)
	{
		return false;
	}
	
	//At this stage, we compute t to find out where intersection point is on line.
	*t = f * dot_product(e2,q);
	
	if (*t > 0.00001) //Ray intersection.
	{
		return true;
	}
	else //Line intersection, but not ray intersection.
	{
		return false;
	}
}

bool raytracer::get_intersection(vertex* ray, triangle* tri, vertex* intersect, float* t)
{
	float p[3], d[3], v0[3], v1[3], v2[3];
	p[0] = ray->x; p[1] = ray->y; p[2] = ray->z;
	d[0] = ray->nx; d[1] = ray->ny; d[2] = ray->nz;
	v0[0] = tri->v[0]->x; v0[1] = tri->v[0]->y; v0[2] = tri->v[0]->z;
	v1[0] = tri->v[1]->x; v1[1] = tri->v[1]->y; v1[2] = tri->v[1]->z;
	v2[0] = tri->v[2]->x; v2[1] = tri->v[2]->y; v2[2] = tri->v[2]->z;
	
	if (!process_intersection(p, d, v0, v1, v2, t)) //If ray doesn't hit this triangle...
	{
		return false;
	}
	
	(*intersect).x = (p[0] + d[0] * (*t));
	(*intersect).y = (p[1] + d[1] * (*t));
	(*intersect).z = (p[2] + d[2] * (*t));
	return true;
}
