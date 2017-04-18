////////////////////////////////////////////////////////////////
// Raster image class
//
// 4/6/17 - B.D.S.
//
// Purpose: An uncompressed 24-bit bitmap image in memory.
////////////////////////////////////////////////////////////////

#ifndef _RASTER_IMAGE_HPP
#define _RASTER_IMAGE_HPP

typedef unsigned char color_component;
typedef unsigned int color;

class raster_image
{
	private:
		unsigned int image_width;
		unsigned int image_height;
		color_component* image_red_array;
		color_component* image_green_array;
		color_component* image_blue_array;
	public:
		raster_image(unsigned int width, unsigned int height);
		~raster_image();
		color_component* get_image_red_array();
		color_component* get_image_green_array();
		color_component* get_image_blue_array();
		void set_pixel(unsigned int x, unsigned int y, color c);
};

#endif
