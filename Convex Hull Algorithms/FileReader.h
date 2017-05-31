#ifndef FILEREADER_H
#define FILEREADER_H
#include "util.h"

using namespace std;



class FileReader
{
	
public:
	FileReader();
	~FileReader();
	vector<Point> read(string filename);
};

#endif
