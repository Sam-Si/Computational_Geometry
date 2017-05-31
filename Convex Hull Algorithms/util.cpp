#include "util.h"

bool turnsLeft(Point a, Point b, Point c){
	 if(vectorArea(a, b, c)<0)
        return true;
     else
        return false;

}
bool isCollinear(Point a, Point b, Point c){
	if(vectorArea(a, b, c)==0)
        return true;
     else
        return false;
}
double vectorArea(Point p, Point q, Point r){
	return (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
}
