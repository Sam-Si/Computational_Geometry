
#include "bits/stdc++.h"

using namespace std;

int no_of_points;

std::vector<long long> answer;
// Algorithm for a really fast CONVEX HULL
typedef long double coord_t;         // coordinate type 

struct Point {
    coord_t x, y;

    Point() : x(0.0), y(0.0){

    }

    bool operator <(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

void print_point(Point a){
    cout << a.x << " " << a.y << endl;
}

struct quadrilateral
{
    Point a; // Right bottom most
    Point b; // Right top most
    Point c; // Left top most
    Point d; // Left bottom most
};

void rand_run(){

    quadrilateral diamond;

    std::vector<Point> input_points;

    srand (time(NULL));    

    // important points
    coord_t xur1, xur2;
    coord_t yur1, yur2;

    int update_counter = 0;
    for (int i = 0; i < no_of_points; ++i){
        Point temp;
        double tat;
        temp.x = (double)((rand()%200000)-99999);
        temp.y = (double)((rand()%200000)-99999);
        bool update = false;

        input_points.push_back(temp);

        // Initialising the Diamond
        if(i == 0){
            diamond.a = temp;
            diamond.b = temp;
            diamond.c = temp;
            diamond.d = temp;
        }

        // diamond a
        if((diamond.a.x - diamond.a.y) < (temp.x - temp.y)){
            diamond.a = temp;
            update = true;
        }
        // diamond b
        if((diamond.b.x + diamond.b.y) < (temp.x + temp.y)){
            diamond.b = temp;
            update = true;
        }
        // diamond c
        if((diamond.c.x - diamond.c.y) > (temp.x - temp.y)){
            diamond.c = temp;
            update = true;
        }
        // diamond d
        if((diamond.d.x + diamond.d.y) > (temp.x + temp.y)){
            diamond.d = temp;
            update = true;
        }

        if(update){
            update_counter++;
            xur1 = max(diamond.c.x, diamond.d.x);
            xur2 = min(diamond.a.x, diamond.b.x);
            yur1 = max(diamond.a.y, diamond.d.y);
            yur2 = min(diamond.b.y, diamond.c.y);
        }

    }


    std::vector<Point> modified_input_points;

    for(int i = 0;i < input_points.size();i++){
        // Pruning part
        Point temp;
        temp = input_points[i];

        bool x_prune = false;
        bool y_prune = false;

        if(((temp.x) > (xur1)) && ((temp.x) < (xur2))){
            x_prune = true;
        }
        if(((temp.y) > (yur1)) && ((temp.y) < (yur2))){
            y_prune = true;
        }

        if(!(x_prune && y_prune)){
            modified_input_points.push_back(temp);
        }
    }

    long long mo = modified_input_points.size();

    answer.push_back(mo);

}

int main(){

	srand (time(NULL)); 

    int test = (rand()%100000);
    no_of_points = (rand()%100);

    int temp = test;
    while(temp--){
        rand_run();
    }

    long long sum = 0;

    for(int i = 0;i < answer.size();i++){
        sum += answer[i];
    }
    cout << "Average percent prune: " << ((double)sum/(double)(test*no_of_points))*100 << endl;

    return 0;
}

