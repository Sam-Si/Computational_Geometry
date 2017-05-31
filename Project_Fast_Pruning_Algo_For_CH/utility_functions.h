/**
 *	@file utility_functions.h
 *  \brief this library contains the utility functions for different types of convex hull algorithms  
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

/*! Structure point :
  *  User defined structure to represent integer cartesian point for the given input points	  
*/

typedef struct point{				
	double x;		/**<abscissa of the integer cartesian point	 */	
	double y;		/**< ordinate of the integer cartesian points */
	int id;		/**< Index of point in original input array */					
}point;

point int_point;		///<interior point in the hull

//! Function : find_rotation
/*! Funtion to find the relative rotation for given 3 points in order
 *	\param[in] a as a point structure
 *	\param[in] b as a point structure
 *	\param[in] c as a point structure
 *	\returns  if the points are collinear, then return value is 0
 *	\returns  if the points are clockwise aligned, then return value is 1
 *	\returns  if the points are counter-clockwise aligned, then return value is -1 
*/
int find_rotation(point a,point b,point c){		
								
	double x = (b.y - a.y)*(c.x - b.x) - (b.x - a.x)*(c.y - b.y); 
	if(x==0){
		return 0;											
	}else if(x>0) return 1;									
	else return -1;											
}

//! Function : dist
/*! Function to formulate the square of distance between two given points as input 
 *	\param[in] a as a point structure
 *	\param[in] b as a point structure
 *  \returns square of distance between points a and b
*/
double dist(point a,point b){
	return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);	
}

//! Function : operator<
/*! Overriding an inbuilt function to replicate the functionality of a sweep line. 
 *	\param[in] a as a point structure
 *	\param[in] b as a point structure
 *  \returns true if point 'a' lies to the left of point 'b' on x-axis
 *	\returns false, otherwise.
*/
bool operator<(const point& a, const point& b)
{
	if(a.x!=b.x)
      return a.x < b.x;
    else
      return a.y<b.y;
}

//! Function : foo
/*! Function as an utility for the comparisions when performing sort upon the points in Graham's Scan
 *	\param[in]	a as a constant void, furthur typecasted into point structure
 *	\param[in]  b as a constant void, furthur typecasted into point structure
 *  \returns If a is to be placed before b, return 1
 *  \returns -1, Otherwise
*/
int foo(const void *a,const void *b){
	point *p1 = (point *)a;
	point *p2 = (point *)b;
	int x = find_rotation(int_point,*p1,*p2);
	if(x==0){
		if(dist(int_point,*p2)>dist(int_point,*p1)){
			return -1;
		}else{
			return 1;
		}
	}else{
		if(x==-1) return -1;
		else return 1; 
	}
}


//! Function : comp
/*! Function as an utility for the comparisions when performing sort upon the points in Andrews Approach
 *	\param[in]	p1 as a constant void, furthur typecasted into point structure
 *	\param[in]  p2 as a constant void, furthur typecasted into point structure
 *  \returns If p1 is to be placed before p2, return 1
 *  \returns -1, Otherwise
*/
int comp(const void *p1,const void *p2){
	point *a = (point *)p1;
	point *b = (point *)p2;
	if((a->x<b->x) || (a->x==b->x && a->y<b->y)) return 1;
	return -1;
}

//! Function : print_stack
/*! An Utility Function to print all the elements of the stack given as input
 *	\param[in] temp as a stack of point structure
 *  \returns -none-
*/
void print_stack(stack <point> temp){					
	while(!temp.empty()){
		cout<<temp.top().x<<" "<<temp.top().y<<endl;
		temp.pop();
	}
}
