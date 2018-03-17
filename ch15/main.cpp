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


	string fileName = "rain-2015-16.dat";
	ifstream ifs (fileName.c_str());
	if (!ifs)
		error("can't open file", fileName);	

	Bar_Graph graph(ifs, &xAxis, &yAxis, origin,50, 60,30);
	graph.set_graphX_label("Month of the year(2016,2017)");
	graph.set_graphY_label("total rain (inch)");
	graph.set_axes_color(Color::blue);
	
	/*string tmp[]={"x", "175", "180", "185", "190", "195"};
	int n = sizeof(tmp)/sizeof(tmp[0]);
	vector<string> labels(tmp,tmp+n);	
	graph.set_bar_labels(labels);
	*/
	graph.set_bar_label_color(Color::red);
	graph.set_bar_color(Color::red);

	fileName = "rain-2016-17.dat";
	ifstream ifs2(fileName.c_str());
	if (!ifs2)
		error("can't open file", fileName);	

	Bar_Graph graph2(ifs2, &xAxis, &yAxis, origin,50,60,30);

	graph2.move_bars(30);
	graph2.move_y_labels_top(30);
	graph2.set_bar_label_color(Color::cyan);
	graph2.set_bar_color(Color::cyan);

	win.attach(graph2);
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
