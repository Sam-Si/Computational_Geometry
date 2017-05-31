#include "FileReader.h"
#include <fstream>
using namespace std;

FileReader::FileReader(){
}

vector<Point> FileReader::read(string filename){
	vector<Point> points;
	ifstream infile(filename.c_str());
	double x, y;
	while(infile>>x>>y){
		Point temp;
		temp.x=x;
		temp.y=y;
		points.push_back(temp);
		//cout<<x<<" "<<y<<"\n";
	}
	return points;

}
FileReader::~FileReader(){
}