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
	int xWin = 1400;
	int yWin = 800;
	Color_lines_window win (Point(400,100),xWin,yWin,"Function Graphs");
	return gui_main();
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
