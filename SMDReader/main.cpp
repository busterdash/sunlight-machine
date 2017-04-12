#include <iostream>
#include "smd_model_reader.h"
using namespace std;

int main(int argc, char* argv[])
{
	smd_model_reader* smr = new smd_model_reader("C:\\users\\buster\\desktop\\smdreader\\cube.smd");
	
	delete smr;
	return 0;	
}
