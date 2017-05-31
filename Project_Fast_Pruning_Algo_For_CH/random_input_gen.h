/**
 *	@file random_input_gen.h
 *  \brief this library generates random input for both convex hull algorithms and polygon triangulation 
*/
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

//! Function : random_input
/*! An Utility Function which generates random input for the convex hull algorithms
 *	\param[in] n as an int,number of random input points to be created
 *  \returns a file input.txt which consists random points
*/

void random_input(int n){
	FILE *fp;
	fp=fopen("input.txt","w+");
	
	
	int i;
	time_t t;
	fprintf(fp,"%d\n",n);
	srand((unsigned) time(&t));
	for(i=0;i<n;i++){
		fprintf(fp,"%d %d %d\n",rand()%n-rand()%n,rand()%n-rand()%n,0);
	}
	fclose(fp);
}




