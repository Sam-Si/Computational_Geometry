/** 
 *	@file Quickhull.cpp
 *	@brief A cpp program to find the convex-hull of the given points in a plane.
 *  The approach to this algorithm is similar to that of "quick-sort", hence the name : "quickHull"
 *  A beautiful divide-and-conquer idea is implemented using standard Cpp STL's
 *  The average running time Complexity of the algorithm is O(n*log(n)). 
 *	\sa https://www.cise.ufl.edu/~ungor/courses/fall06/papers/QuickHull.pdf
*/


#include <iostream>
#include <algorithm>
#include <set>
#include <ctime>
#include <bits/stdc++.h>
/**
 *	\header random_input_gen.h "random_input_gen.h"
*/
#include "random_input_gen.h"
/**
 *	\header utility_functions.h "utility_functions.h"
*/
#include "utility_functions.h"

using namespace std;
ofstream outfile("result.ch");		///< @brief the points in the convex hull are 

set <point> hull;				///< @brief the points present on the convex hull 

//long long frequency;        ///< @brief ticks per second
//long long t1,t2;			///< @brief ticks
//double elapsedTime;				///< @brief physical CPU time elapsed to finish the algorithm

vector <point> convex_hull;		///< @brief The final Points of hull in anti-clockwise direction
vector <point> clockwise;		///< @brief Intermediate set of points that are clockwise w.r.t the start and end points on hull
vector <point> anti;			///< @brief Intermediate set of points that are anti-clockwise w.r.t the start and end points on hull

int n;							///< @brief Total number of points in the cartesian plane

point* a = new point[1500000];	///<@brief Instantiate the array of point structure to be passed as input to each algorithm
point* original = new point[1500000]; ///<@brief Instantiate the array of point structure which stores the input 
 
//! Function : Direction
/*! Funtion to find the relative direction for given 3 points in order
 *	\param[in] a as a point structure
 *	\param[in] b as a point structure
 *	\param[in] c as a point structure
 *	\returns  if the point 'c' lies above the line joining 'a' and 'b', return value is 1
 *	\returns  if the points are co-linear, then return value is 0
 *	\returns  if the points are counter-clockwise aligned, then return value is -1
*/

int Direction(point a, point b, point c)
{
    double val = (c.y - a.y)*(b.x - a.x) - (b.y - a.y)*(c.x - a.x); 
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}
 
//! Function : Dist_frm_line
/*! Funtion to find the distance of point 'p' from the line joining points 'p1' and 'p2'
 *	\param[in] p1 as a point structure
 *	\param[in] p2 as a point structure
 *	\param[in] p as a point structure
 *	\returns  the absolute distance between the line and the given point
*/

double Dist_frm_line(point p1, point p2, point p){
    return abs ((p.y - p1.y) * (p2.x - p1.x) -(p2.y - p1.y) * (p.x - p1.x));
}

//! Function : Quick_Hull
/*! \brief this function recursively eliminates the internal points in a triangle formed by the line and a point farthest from the line. And recursively finds the convex vertices from remaining area.
 *  \param[in] a as an array of points
 *  \param[in] n as the total number of points
 *	\param[in] p1 as a point structure
 *	\param[in] p2 as a point structure
 *	\param[in] side as an int, direction in which quickhull should be recursed
*/

void Quick_Hull(point a[],int n, point p1, point p2, int side){
    int index = -1;
	double max_distance = 0; 
    for (int i=0; i<n; i++){
        double temp = Dist_frm_line(p1, p2, a[i]);
        if (Direction(p1, p2, a[i]) == side && temp > max_distance){
            index = i;
            max_distance = temp;
        }
    }
    //At base condition (where all points lie on one side) then the two points are inserted into set where duplicate points are removed.
    if (index == -1){
        hull.insert(p1);
        hull.insert(p2);
        return;
    }
    //finds the convexhull by eliminating triangle area formed by p1,p2,a[index],and recursively calling quickhull on other sides of lines joining p1,a[index] and p2,a[index 
    Quick_Hull(a, n, a[index], p1, -Direction(a[index], p1, p2));
    Quick_Hull(a, n, a[index], p2, -Direction(a[index], p2, p1));
    
}

//! Function : get_proper_ids
/*! \brief This function takes a 'set' of points and prepares a 'vector' which contains them points in anti-clockwise order.
 *  \param[in] hull as a set of points
 *	\returns A vector of points in which the points are in anti-clockwise order.
*/

vector < point > get_proper_ids(set<point> hull) {
	set < point >::iterator it=hull.begin(),bt,end=hull.end();
	it = hull.begin();
	point initial_point = *it;
	end--;
	int i;
	vector<point> temp;
	temp.push_back(initial_point);
	for(it++;it!=end;it++){
		point a = *hull.begin();
		point b = *it;
		bt = hull.end();
		bt--;
		point c = *bt;
		if(Direction(a,b,c)==1){
			clockwise.push_back(b);
		}else if(Direction(a,b,c)==-1){
			anti.push_back(b);
		}
	}
	
	for(i=0;i<clockwise.size();i++){
		temp.push_back(clockwise[i]);
	}
	
	temp.push_back(*it);
	
	for(i=anti.size()-1;i>=0;i--){
		temp.push_back(anti[i]);
	}
	return temp;
}
//! Function : main
/*! Driver Function to execute quickhull algorithm with the data set of points from an input file */
int main()
{
	//random_input(500);
	int i;
	string line;
	ifstream infile("input.txt");		///< @brief the input points are taken from the text file input.txt
	
	getline(infile,line);					// Reading the first line of the input file and read it as the number of input points+	
	istringstream iss(line);				// Parsing the line(string) into an input string stream so as to get the 
	
	iss>>n;
	
	
	int m=0;

	
	while(getline(infile,line)){
	
		istringstream iss (line);
		iss>>a[m].x>>a[m].y;			
		a[m].id = m;						/* reading the file line-by-line and storing the input points into array(a) and array(original)	*/
		original[m].x = a[m].x;
		original[m].y = a[m].y;
		original[m].id = a[m].id;
		m++;
	}
    if (n < 3){
        cout << "Convex hull not possible\n";
        return 0;
    }    
    int min_x = 0, max_x = 0;
    for (i=1; i<n; i++){
        if (a[i].x < a[min_x].x)
            min_x = i;
        if (a[i].x > a[max_x].x)
            max_x = i;
    }
    
//    QueryPerformanceFrequency(&frequency);
//    QueryPerformanceCounter(&t1);
    
    Quick_Hull(a, n, a[min_x], a[max_x], 1);
    Quick_Hull(a, n, a[min_x], a[max_x], -1);
    
//    QueryPerformanceCounter(&t2);
    
//    elapsedTime = (double)((t2.LowPart - t1.LowPart)) / frequency.LowPart;
//	cout<<"time taken by QuickHull is: "<<elapsedTime<<endl;
 
    //cout << "The Convex Hull points are:\n";
    outfile<<"CH"<<endl;
    outfile<<n<<" "<<hull.size()<<endl;
    
    for(i=0;i<n;i++){
    	outfile<<original[i].x<<" "<<original[i].y<<" "<<0<<endl;
	}	
	
	convex_hull = get_proper_ids(hull);
	
	for(i=0;i<convex_hull.size();i++){
		outfile<<convex_hull[i].id<<" ";
	}
    cout<<"open result.ch file in visualization software for solution. Cheers!"<<endl;
    return 0;
}
