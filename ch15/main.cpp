#include "fltk.h" 
#include "Simple_window.h"
#include "Point.h"
#include "std_lib_facilities.h"
#include <vector>
#include <time.h>

using namespace::Graph_lib;
using Graph_lib::Font;

int main()
{
try
{
	Simple_window win (Point(400,100),1000,800,"main");
	Point tl(500,100);
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
