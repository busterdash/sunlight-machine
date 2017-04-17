////////////////////////////////////////////////////////////////
// Device Independent Bitmap Class
//
// 4/6/17 - B.D.S.
//
// Purpose: Creates the image portion of the bitmap file.
////////////////////////////////////////////////////////////////

#ifndef _DEVICE_BITMAP_H
#define _DEVICE_BITMAP_H

#include "binary_writer.h"
#include "raster_image.h"
using namespace std;

class device_independent_bitmap
{
	private:
		word header_size;
		word bitmap_width;
		word bitmap_height;
		halfword color_plane_count;
		halfword bits_per_pixel;
		word compression_method;
		word bitmap_data_size;
		word hor_pixel_per_meter;
		word ver_pixel_per_meter;
		word palette_color_count;
		word important_color_count;
		raster_image* img;
	public:
		device_independent_bitmap(unsigned int width, unsigned int height);
		~device_independent_bitmap();
		void save(ofstream* f);
		raster_image* get_image();
		int get_header_size();
		int get_image_size();
};

#endif
