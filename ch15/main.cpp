#include "fltk.h" 
#include "Simple_window.h"
#include "Point.h"
#include "std_lib_facilities.h"
#include <vector>
#include <time.h>
#include <cmath>

using namespace::Graph_lib;
using Graph_lib::Font;

int numTerms=0;//for leibniz
double one(double x){return 1;}
double slope(double x){return x/2;}
double square(double x){return x*x;}
double sloping_cos(double x){return cos(x)+slope(x);}

double leibniz(double x){
	//double x is the trick to plot the results in the window - return a constant number for every x
	numTerms++;
	double result = 0;
	for (int i=0; i<numTerms; i++)
		result += pow(-1,i)/(2*i+1);

	return result;
}

int main()
{
try
{
	int xWin = 600;
	int yWin = 600;
	Simple_window win (Point(400,100),xWin,yWin,"Function Graphs");
	Point origin(xWin/2,yWin/2);
	int length = 800;
	int ticSpacing = 20;
	int numNotch = length/ticSpacing;
	Axis xAxis(Axis::x, origin, length/2, numNotch, "1 == 20 pixels");
	Axis yAxis(Axis::y, origin, length, numNotch, "1 == 20 pixels");
	xAxis.set_color(Color::red);
	yAxis.set_color(Color::red);
	win.attach(xAxis);
	win.attach(yAxis);
	win.wait_for_button();

	for (int i=0; i<100; i++){
		//cout << "i: " << i << ":" << leibniz(1.0) << endl;
		Function* f = new Function(leibniz, -10, 10, origin, 100,25,100);
		f->set_color(i);
		win.attach(*f);
		win.wait_for_button();
	}

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
