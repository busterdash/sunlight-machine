#include "binary_writer.hpp"

int binary_writer::bytes_written = 0;

void binary_writer::write(ofstream* f, halfword hw)
{
	char byte1 = (char)(hw >> 8);
	char byte2 = (char)(hw & 255);
	f->put(byte2); //Reverse these for big-endian.
	f->put(byte1);
	bytes_written += 2;
}

void binary_writer::write(ofstream* f, word w)
{
	char byte1 = (char)(w >> 24);
	char byte2 = (char)((w >> 16) & 255);
	char byte3 = (char)((w >> 8) & 255);
	char byte4 = (char)(w & 255);
	f->put(byte4); //Reverse these for big-endian.
	f->put(byte3);
	f->put(byte2);
	f->put(byte1);
	bytes_written += 4;
}
