#include <iostream>
using namespace std;

void vec(float* a, float* b, float* c)
{
	a[0] = b[0] - c[0];
	a[1] = b[1] - c[1];
	a[2] = b[2] - c[2];
}

void cross_product(float* a, float* b, float* c)
{
	a[0] = b[1] * c[2] - c[1] * b[2];
	a[1] = b[2] * c[0] - c[2] * b[0];
	a[2] = b[0] * c[1] - c[0] * b[1];
}

float dot_product(float* a, float* b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

//Source: http://www.lighthouse3d.com/tutorials/maths/ray-triangle-intersection/
bool ray_intersects_triangle(float* p, float* d, float* v0, float* v1, float* v2, float* t)
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

int main(int argc, char* argv[])
{
	float v1[3] = { 0.0, 2.0, 0.0 };
	float v2[3] = { -3.0, -2.0, 0.0 };
	float v3[3] = { 3.0, -2.0, 0.0 };
	float p[3] = { 0.0, 0.0, 4.0 };
	float d[3] = { 0.0, 0.0, -1.0 };
	float i = 0.0;
	float c[3] = { 0.0, 0.0, 0.0 };
	
	if (ray_intersects_triangle(p,d,v1,v2,v3,&i))
	{
		cout << "INTERSECTION\n";
		
		c[0] = p[0] + d[0] * i;
		c[1] = p[1] + d[1] * i;
		c[2] = p[2] + d[2] * i;
		
		cout << "AT: " << c[0] << ", " << c[1] << ", " << c[2] << "\n";
	}
	else
	{
		cout << "NO INTERSECTION\n";
	}
}
