#include "FileReader.h"

bool byX(const Point& a,const Point& b){
	if(a.x!=b.x){
		return a.x<b.x;
	}else 
		return a.y<b.y;
}

vector<Point> run(vector<Point> points){
	sort(points.begin() , points.end(),byX);
	vector<Point> result,U,L;
	if(points.size()<3){
		cout<<"Not Possible";
		exit(0);
	}
	L.push_back(points[0]);
	L.push_back(points[1]);
	int n=points.size();
	for(int i=2; i<n; i++){
		while(L.size()>1 && !turnsLeft(L[L.size()-2],L[L.size()-1], points[i]))
			L.pop_back();
		L.push_back(points[i]);
	}
	

	U.push_back(points[n-1]);
	U.push_back(points[n-2]);

	for(int i=n-3; i>=0; i--){
		while(U.size()>1 && !turnsLeft(U[U.size()-2],U[U.size()-1], points[i]))
			U.pop_back();
		U.push_back(points[i]);
	}
	
	U.pop_back();
	L.pop_back();
	while(U.size()>0){
		result.push_back(U[U.size()-1]);
		U.pop_back();
	}
	while(L.size()>0){
		result.push_back(L[L.size()-1]);
		L.pop_back();
	}
	return result;


}



int main(){
	FileReader file;
	vector<Point> points;
	points= file.read("in1");
	ofstream fileOut("out1"); 
	fileOut<<"CH\n";

	vector<Point> result=run(points);
	fileOut<<points.size()<<" "<<result.size()<<"\n";
	for(vector<Point>::iterator i=result.begin(); i!=result.end(); i++){
		Point p=*i;
		fileOut<<p.x<<" "<<p.y<<"\n";
		cout<<p.x<<" "<<p.y<<"\n";
	}
	
	
}