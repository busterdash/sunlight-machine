#ifndef _SMD_MODEL_READER_H
#define _SMD_MODEL_READER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "geometry.h"

class smd_model_reader
{
	private:
		std::ifstream fi;
		std::vector<triangle*> tri_list;
		vertex* parse_line(std::string line);
	public:
		smd_model_reader(std::string file);
		~smd_model_reader();
};

#endif
