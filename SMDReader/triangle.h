#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "vertex.h"

struct triangle
{
	vertex* v[3];
	triangle(vertex* v1, vertex* v2, vertex* v3);
	~triangle();
};

#endif
