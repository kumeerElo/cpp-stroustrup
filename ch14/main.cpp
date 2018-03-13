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
	//a comment for git 

	Simple_window win (Point(400,100),1000,800,"main");
	Point tl(500,100);

	BinaryTree tree(tl,3);
	win.attach(tree);
	win.wait_for_button();

/* problem #9 - group different objects into one.
	Group shapes;
	Circle c(tl,100);
	Ellipse e (Point(tl.x+200,tl.y), 200,100);
	Rectangle r (Point(100,100), 200,100);

	shapes.add_shape(c);
	shapes.add_shape(e);
	shapes.add_shape(r);
	shapes.set_fill_color(Color::blue);
	shapes.set_color(Color::red);
	
	win.attach(shapes);
	win.wait_for_button();

	shapes.move(100,400);
	win.wait_for_button();
 

	Point p(100,100);

	Group checkerBoard;
	create_checker_board(checkerBoard, p, 8, 8, 600, 600);
	add_first_piece(checkerBoard, 600,600);
	win.attach(checkerBoard);
	win.wait_for_button();
*/		

/* problem # 6	
	Striped_Circle sc(tl,200);
	win.attach(sc);
	win.wait_for_button();
*/

/*
	int x_size = win.x_max();
	int y_size = win.y_max();
	int y_grid = 50;
	Lines grid;
	for (int y=y_grid; y<y_size; y+=y_grid)
		grid.add(Point(0,y),Point(x_size,y));
	grid.set_color(Color::red);

	win.attach(grid);
	win.wait_for_button();
*/

/* problem #5 - striped rectangle

	Striped_Rectangle sr(tl,600,400);
	sr.set_color(Color::yellow);
	sr.set_fill_color(Color::yellow);
	win.attach(sr);
	win.wait_for_button();
*/

/* problem #4
	Circle c(tl,200);
	c.set_color(Color::blue);
	win.attach(c);	
	win.wait_for_button();

	Circle c1(tl,200);
	c1.move(400,0);
	c1.set_color(Color::red);
	win.attach(c1);

	win.wait_for_button();
*/

/* problem 1

	Smiley2 aSmile(tl,150);	
	win.attach(aSmile);

	Point tl2(700,300);
	Frowny aFrown (tl2,150);	
	win.attach(aFrown);
	win.wait_for_button();
*/
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
