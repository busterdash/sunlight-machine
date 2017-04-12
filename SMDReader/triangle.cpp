#include "triangle.h"

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
