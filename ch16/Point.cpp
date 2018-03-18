#include <iostream>
using namespace std;
#include "Point.h"

namespace Graph_lib {
/*
ostream& Point::operator<<(ostream &os)
{
		return os << "x: " << x << " y: " << y;
}*/
 
ostream& operator<<(ostream &os, const Point& p)
{
		return os << "x: " << p.x << " y: " << p.y;
}

}//Graph_lib namespace
