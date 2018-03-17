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
	// class Bar-Graph - prob 6 and 7
	int xWin = 1000;
	int yWin = 600;
	Simple_window win (Point(400,100),xWin,yWin,"Function Graphs");
	Point origin(xWin/2-200,yWin/2+200);
	int length = 800;
	int ticSpacing = 20;
	int numNotch = length/ticSpacing;
	Axis xAxis(Axis::x, origin, length/2, numNotch, "x-axis");
	Axis yAxis(Axis::y, origin, length/2, numNotch, "y-axis");

	string fileName = "bar.dat";
	ifstream ifs (fileName.c_str());
	if (!ifs)
		error("can't open file", fileName);	

	Bar_Graph graph(ifs, &xAxis, &yAxis, origin,10);
	graph.set_graphX_label("year");
	graph.set_graphY_label("\%increase in produce");
	graph.set_axes_color(Color::blue);
	
	string tmp[]={"1980", "1990", "2000", "2010"};
	int n = sizeof(tmp)/sizeof(tmp[0]);
	vector<string> labels(tmp,tmp+n);	
	graph.set_bar_labels(labels);
	graph.set_bar_label_color(Color::red);
	graph.set_bar_color(Color::yellow);

	win.attach(graph);
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
