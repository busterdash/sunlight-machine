#include "windows_bitmap.hpp"
#include <iostream>

windows_bitmap::windows_bitmap(std::string file, unsigned int width, unsigned int height)
{
	filename = file;
	reserved1 = 0;
	reserved2 = 0;
	dib = new device_independent_bitmap(width,height);
	image_data_offset = dib->get_header_size() + 14; //bytes.
	bmp_size = image_data_offset + dib->get_image_size();
}

windows_bitmap::~windows_bitmap()
{
	delete dib;
}

read::status windows_bitmap::import(std::string file)
{
	std::ifstream fi;
	read::status errorcode = read::success;
	fi.open(file.c_str(), std::ios::in | std::ios::binary);
	
	if (fi.is_open())
	{
		halfword signature = binary_rw::read_halfword(&fi);
		
		if (signature == header)
		{
			binary_rw::skip_words(&fi,2);
			word offset_to_array = binary_rw::read_word(&fi);
			
			if ((int)offset_to_array == dib->get_header_size() + wb_header_size)
			{
				binary_rw::skip_words(&fi,1);
				word w = binary_rw::read_word(&fi);
				word h = binary_rw::read_word(&fi);
				
				if (w == dib->get_image_width() && h == dib->get_image_height())
				{
					fi.seekg(offset_to_array,std::ios_base::beg); //We've had enough with headers, lets get our image.
					unsigned int pad_amount = dib->get_image_width() % 4; //Amount of padding at the end of the rows.
					
					for (unsigned int y = 0; y < dib->get_image_height(); y++)
					{
						for (unsigned int x = 0; x < dib->get_image_width(); x++)
						{
							//Compose a color from three bytes we read in.
							char c;
							color pix = 0;
							fi.get(c);
							pix = pix | (unsigned char)c;
							fi.get(c);
							pix = pix | ((unsigned char)c << 8);
							fi.get(c);
							pix = pix | ((unsigned char)c << 16);
							
							dib->get_image()->set_pixel(x,dib->get_image_height()-y-1,pix);
						}
						
						fi.seekg(pad_amount,std::ios_base::cur); //Skip the padding at the end of the rows.
					}
				}
				else
				{
					errorcode = read::bad_file_dimensions;
				}
			}
			else
			{
				errorcode = read::bad_header;
			}
		}
		else
		{
			errorcode = read::bad_header;
		}
	}
	else
	{
		errorcode = read::bad_filename;
	}
	
	fi.close();
	return errorcode;
}

bool windows_bitmap::save()
{
	bool out = false;
	std::ofstream fi;
	fi.open(filename.c_str(), std::ios::out | std::ios::binary);
	
	if (fi.is_open())
	{
		binary_rw::write(&fi, header);
		binary_rw::write(&fi, bmp_size);
		binary_rw::write(&fi, reserved1);
		binary_rw::write(&fi, reserved2);
		binary_rw::write(&fi, image_data_offset);
		dib->save(&fi);
		out = true;
	}
	
	fi.close();
	return out;
}

device_independent_bitmap* windows_bitmap::get_dib()
{
	return dib;
}
