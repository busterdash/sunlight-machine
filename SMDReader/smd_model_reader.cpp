#include "smd_model_reader.h"

smd_model_reader::smd_model_reader(std::string file)
{
	std::string line;
	bool triangles = false;
	long counter = 0;
	vertex* vbuffer[3];
	short vertex_counter = 0;
	
	fi.open(file.c_str());
	
	if (fi.is_open())
	{
		while (getline(fi, line))
		{
			if (!triangles && line == "triangles")
			{
				triangles = true;
				continue;
			}
		
			if (triangles)
			{
				counter++;
				
				if (counter == 1) //Skip the first material definition.
				{
					continue;	
				}
				
				if (line.length() > 2)
				{
					if (line.substr(0,2) == "0 ")
					{
						vbuffer[vertex_counter] = parse_line(line);
						vertex_counter++;
					}
					else
					{
						triangle* tri = new triangle(vbuffer[0],vbuffer[1],vbuffer[2]);
						tri_list.push_back(tri);
						vertex_counter = 0;
					}
				}
			}
		}
	}
}

vertex* smd_model_reader::parse_line(std::string line)
{
	short data_position = 0;
	float line_data[10];
	std::string buffer = "";
	bool last_char_is_space = false; //Double spaces can't kill me.
	vertex* v;
	
	for (short i = 0; i < line.length(); i++)
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			buffer += line[i];
			last_char_is_space = false;
		}
		else
		{
			if (last_char_is_space) { continue; }
			line_data[data_position] = strtof(buffer.c_str(),0);
			data_position++;
			last_char_is_space = true;
			buffer = "";
		}
	}
	
	v = new vertex(line_data[1],line_data[2],line_data[3],line_data[4],line_data[5],line_data[6],line_data[7],line_data[8]);
	return v;
}

smd_model_reader::~smd_model_reader()
{
	fi.close();
	tri_list.clear();
}
