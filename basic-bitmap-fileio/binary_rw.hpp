////////////////////////////////////////////////////////////////
// Binary Reader/Writer Struct
//
// 4/6/17 - B.D.S.
//
// Purpose: Provides an interface to R&W binary data easier.
////////////////////////////////////////////////////////////////

#ifndef _BINARY_RW_HPP
#define _BINARY_RW_HPP

#include <fstream>
typedef unsigned short int halfword;
typedef unsigned long int word;

struct binary_rw
{
	static int bytes_written;
	static void write(std::ofstream* f, halfword hw);
	static void write(std::ofstream* f, word w);
	static word read_word(std::ifstream* f);
	static halfword read_halfword(std::ifstream* f);
	static void skip_words(std::ifstream* f, int words);
	static void skip_halfwords(std::ifstream* f, int halfwords);
};

#endif
