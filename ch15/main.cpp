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
//drill - function graphing

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

	int negXrange = -10;
	int posXrange = 11;
	int numPoints = 400;
	int xScale = 20;
	int yScale = 20;

	Function f1 (one, negXrange, posXrange, origin, numPoints, xScale, yScale);
	f1.set_color(Color::yellow);
	win.attach(f1);

	Function f2 (slope, negXrange, posXrange, origin, numPoints, xScale, yScale);
	f2.set_color(Color::blue);
	win.attach(f2);

	Text labelF2 (Point(origin.x+negXrange*xScale, origin.y+120),"x/2");
	win.attach(labelF2);
	labelF2.set_color(Color::blue);

	Function f3 (square, negXrange, posXrange, origin, numPoints, xScale, yScale);
	f3.set_color(Color::cyan);
	win.attach(f3);

	Function f4 (cos, negXrange, posXrange, origin, numPoints, xScale, yScale);
	f4.set_color(Color::magenta);
	win.attach(f4);

	Function f5 (sloping_cos, negXrange, posXrange, origin, numPoints, xScale, yScale);
	f5.set_color(Color::green);
	win.attach(f5);
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
