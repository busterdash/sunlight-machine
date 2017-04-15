#include <iostream>
#include <iomanip>
#include <cmath>
#include "triangle.h"

float distance_formula_3d(float x1, float y1, float z1, float x2, float y2, float z2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
}

void alpha_beta_to_cartesian(float x1, float y1, float x2, float y2, float percent, float* outx, float* outy)
{
	float dist = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	float dist_seg = dist * percent;
	*outx = (x2 - x1) * dist_seg / dist + x1;
	*outy = (y2 - y1) * dist_seg / dist + y1;
}

//Take a triangle and a hit position on that triangle, and give back a point on the UV map.
vertex* transform_trace_to_uv(triangle* t, vertex* hit)
{
	vertex* out = new vertex();
	
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
	alpha_beta_to_cartesian(t->v[1]->u, t->v[1]->v, t->v[2]->u, t->v[2]->v, beta, &out->u, &out->v);
	alpha_beta_to_cartesian(t->v[0]->u, t->v[0]->v, out->u, out->v, alpha, &out->u, &out->v);
	
	return out;
}

int main(int argc, char* argv[])
{	
	vertex* v1 = new vertex(1.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 4.0f);
	vertex* v2 = new vertex(4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 4.0f, 1.0f);
	vertex* v3 = new vertex(1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	vertex* h = new vertex(1.1f, 1.1f, 0.0f);
	vertex* uv;
	
	triangle* t = new triangle(v1,v2,v3);
	uv = transform_trace_to_uv(t, h);
	
	std::cout << std::fixed << std::setprecision(6) << "(" << uv->u << ", " << uv->v << ")\n";
	
	delete t; //v1-v3 will get deleted when the triangle is deleted.
	delete h;
	delete uv;
	
	return 0;	
}
