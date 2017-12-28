////////////////////////////////////////////////////////////////
// Windows Bitmap Class
//
// 4/6/17 - B.D.S.
//
// Purpose: Creates a windows bitmap image.
////////////////////////////////////////////////////////////////

#ifndef _WINDOWS_BITMAP_HPP
#define _WINDOWS_BITMAP_HPP

#include "device_independent_bitmap.hpp"
#include "binary_rw.hpp"
#include <string>

namespace read
{
	enum status { success, bad_filename, bad_header, bad_file_dimensions };
}

class windows_bitmap
{
	private:
		std::string filename;
		const static short wb_header_size = 14;
		const static halfword header = 0x4D42; //BM in the end, reversed initially for little-endian.
		word bmp_size;
		halfword reserved1;
		halfword reserved2;
		word image_data_offset;
		device_independent_bitmap* dib;
	public:
		windows_bitmap(std::string file, unsigned int width, unsigned int height);
		~windows_bitmap();
		bool save();
		read::status import(std::string file);
		device_independent_bitmap* get_dib();
};

#endif
