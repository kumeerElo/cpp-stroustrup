#include "fltk.h" 
#include "Simple_window.h"
#include "Point.h"
#include "std_lib_facilities.h"
#include <vector>
#include <time.h>
#include <cmath>
#include <fstream>

using namespace::Graph_lib;
using Graph_lib::Font;

int main()
{
try
{
	// class Bar-Graph - prob 8, 11
	int xWin = 1400;
	int yWin = 800;
	Simple_window win (Point(400,100),xWin,yWin,"Function Graphs");
	Point origin(100,yWin/2+300);
	int length = 1200;
	int ticSpacing = 20;
	int numNotch = length/ticSpacing;
	Axis xAxis(Axis::x, origin, length-70, numNotch, "x-axis");
	Axis yAxis(Axis::y, origin, length/2, numNotch, "y-axis");
	win.attach(xAxis);
	win.attach(yAxis);



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
