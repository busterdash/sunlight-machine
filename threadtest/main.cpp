#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <pthread.h>
#include "raster_image.hpp"
#define NUM_THREADS 4
using namespace std;

struct worker_arguments
{
	raster_image* img;
	int x_start;
	int y_start;
	int x_end;
	int y_end;
	int color;
	
	worker_arguments(raster_image* i, int xs, int ys, int xe, int ye, int c)
	{
		img = i;
		x_start = xs;
		y_start = ys;
		x_end = xe;
		y_end = ye;
		color = c;
	}
};

void* worker(void* argument)
{
	worker_arguments* args = (worker_arguments*)argument;

	for (int y = args->y_start; y < args->y_end; y++)
	{
		for (int x = args->x_start; x < args->x_end; x++)
		{
			args->img->set_pixel(x,y,args->color);
		}
	}
}

int main(int argc, char* argv[])
{
	int image_width = 8;
	int image_height = 8;	
	raster_image* img = new raster_image(image_width,image_height);
	worker_arguments* wa[NUM_THREADS];
	pthread_t threads[NUM_THREADS];
	int t;
	
	for (t = 0; t < NUM_THREADS; t++)
	{
		wa[t] = new worker_arguments(img,0,t*image_height/NUM_THREADS,image_width,(t+1)*image_height/NUM_THREADS,0x999999 + (t*0x010000));
	}
	
	for (t = 0; t < NUM_THREADS; t++)
	{
		pthread_create(&threads[t],NULL,worker,(void*)wa[t]);
	}
	
	for (t = 0; t < NUM_THREADS; t++)
	{
		pthread_join(threads[t],NULL);
		delete wa[t];
	}
	
	color_component* result = img->get_image_red_array();
	
	for (t = 0; t < image_width * image_height; t++)
	{
		printf("%d\n",result[t]);
	}
	
	delete img;
	return 0;
}
