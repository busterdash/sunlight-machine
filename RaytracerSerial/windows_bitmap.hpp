////////////////////////////////////////////////////////////////
// Windows Bitmap Class
//
// 4/6/17 - B.D.S.
//
// Purpose: Creates a windows bitmap image.
////////////////////////////////////////////////////////////////

#ifndef _WINDOWS_BITMAP_HPP
#define _WINDOWS_BITMAP_HPP

#include <string>
#include "device_independent_bitmap.hpp"
using namespace std;

class windows_bitmap
{
	private:
		ofstream fi;
		const static halfword header = 0x4D42; //BM in the end, reversed initially for little-endian.
		word bmp_size;
		halfword reserved1;
		halfword reserved2;
		word image_data_offset;
		device_independent_bitmap* dib;
	public:
		windows_bitmap(string filename, unsigned int width, unsigned int height);
		~windows_bitmap();
		void save();
		device_independent_bitmap* get_dib();
};

#endif
