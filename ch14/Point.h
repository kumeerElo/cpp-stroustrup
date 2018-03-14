#ifndef POINT_GUARD
#define POINT_GUARD
#include <iostream>
using namespace std;

//typedef void (*Callback)(void*,void*);

namespace Graph_lib {

struct Point {
	int x,y;
	Point(int xx, int yy) : x(xx), y(yy) { }
	Point() :x(0), y(0) { }

	Point& operator+=(Point d) { x+=d.x; y+=d.y; return *this; }
	Point& operator-=(double edge) { x-=edge; y-=edge; return *this; }
	//ostream& operator<<(ostream &os);

};

inline bool operator==(Point a, Point b) { return a.x==b.x && a.y==b.y; }
inline bool operator!=(Point a, Point b) { return !(a==b); }
ostream& operator<<(ostream& os, const Point& p);

class PointPair
{
public:
	PointPair(Point p1, Point p2): m_p1(p1), m_p2(p2){};	
	Point get_p1()const {return m_p1;}
	Point get_p2()const {return m_p2;}
private:
	Point m_p1;
	Point m_p2;
};

}


#endif
