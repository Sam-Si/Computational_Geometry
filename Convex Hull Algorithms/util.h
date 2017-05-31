#ifndef UTIL_H
#define UTIL_H

#include <bits/stdc++.h>
using namespace std;

struct Point{
	double x;
	double y;
};

bool turnsLeft(Point a, Point b, Point c);
double vectorArea(Point a, Point b, Point c);
bool isCollinear(Point a, Point b, Point c);

#endif
