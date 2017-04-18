#include "windows_bitmap.hpp"

windows_bitmap::windows_bitmap(string filename, unsigned int width, unsigned int height)
{
	fi.open(filename.c_str(), ios::out | ios::binary);
	
	reserved1 = 0;
	reserved2 = 0;
	dib = new device_independent_bitmap(width,height);
	image_data_offset = dib->get_header_size() + 14; //bytes.
	bmp_size = image_data_offset + dib->get_image_size();
}

windows_bitmap::~windows_bitmap()
{
	fi.close();
	delete dib;
}

void windows_bitmap::save()
{
	binary_writer::write(&fi, header);
	binary_writer::write(&fi, bmp_size);
	binary_writer::write(&fi, reserved1);
	binary_writer::write(&fi, reserved2);
	binary_writer::write(&fi, image_data_offset);
	dib->save(&fi);
}

device_independent_bitmap* windows_bitmap::get_dib()
{
	return dib;
}
