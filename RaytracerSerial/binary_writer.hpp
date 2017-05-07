////////////////////////////////////////////////////////////////
// Binary Writer Class
//
// 4/6/17 - B.D.S.
//
// Purpose: Provides an interface to write binary data easier.
////////////////////////////////////////////////////////////////

#ifndef _BINARY_WRITER_HPP
#define _BINARY_WRITER_HPP

#include <fstream>
using namespace std;
typedef unsigned short int halfword;
typedef unsigned long int word;

struct binary_writer
{
	static int bytes_written;
	static void write(ofstream* f, halfword hw);
	static void write(ofstream* f, word w);
};

#endif
