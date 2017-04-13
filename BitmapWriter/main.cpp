#include <iostream>
#include "windows_bitmap.h"
using namespace std;

int main(int argument_count, char* argument_value[])
{
	windows_bitmap* wb = new windows_bitmap("asdf.bmp", 16, 16);
	wb->get_dib()->get_image()->set_pixel(2,3,0x00ff00);
	wb->get_dib()->get_image()->set_pixel(2,4,0xffafaf);
	wb->save();
	delete wb;
	return 0;
}
