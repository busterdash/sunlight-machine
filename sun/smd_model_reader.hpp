/*==============================================================================================

	smd_model_reader.hpp
	Copyright 2019 Buster Schrader

	This file is part of The Sunlight Machine.

    The Sunlight Machine is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    The Sunlight Machine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Sunlight Machine.  If not, see <https://www.gnu.org/licenses/>.
	
==============================================================================================*/

#ifndef _SMD_MODEL_READER_HPP
#define _SMD_MODEL_READER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "geometry.hpp"

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
