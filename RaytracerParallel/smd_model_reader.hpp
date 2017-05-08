#ifndef _SMD_MODEL_READER_HPP
#define _SMD_MODEL_READER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "geometry.cuh"

class smd_model_reader
{
	private:
		std::ifstream fi;
		std::vector<triangle*> tri_list;
		vertex* parse_line(std::string line);
	public:
		smd_model_reader(std::string file);
		~smd_model_reader();
		triangle* get_triangle(unsigned int index);
		float get_max_coordinate();
		unsigned int get_triangle_count();
};

#endif
