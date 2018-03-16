#include "fltk.h" 
#include "Simple_window.h"
#include "Point.h"
#include "std_lib_facilities.h"
#include <vector>
#include <time.h>
#include <cmath>

using namespace::Graph_lib;
using Graph_lib::Font;


double one(double x){return 1;}
double slope(double x){return x/2;}
double square(double x){return x*x;}
double sloping_cos(double x){return cos(x)+slope(x);}

int main()
{
try
{
	int xWin = 600;
	int yWin = 600;
	Simple_window win (Point(400,100),xWin,yWin,"Function Graphs");
	Point origin(xWin/2,yWin/2);
	int length = 400;
	int ticSpacing = 20;
	int numNotch = length/ticSpacing;
	Axis xAxis(Axis::x, origin, length, numNotch, "1 == 20 pixels");
	Axis yAxis(Axis::y, origin, length, numNotch, "1 == 20 pixels");
	xAxis.set_color(Color::red);
	yAxis.set_color(Color::red);
	win.attach(xAxis);
	win.attach(yAxis);

	FunctionLean fun1(one,-10,10,origin);
	fun1.set_function(square);
	fun1.set_max_range(5);
	fun1.set_origin(Point(origin.x+100,origin.y));
	fun1.create_function();
	fun1.set_color(Color::blue);
	win.attach(fun1);
	win.wait_for_button();

  return 0;
}

catch(exception& e){
	cerr << "exception thrown: " << e.what() << endl;
	return 1;
}
catch(...){
	cerr << "unknown exception happened: "<< endl;
	return 2;
}

}//main
