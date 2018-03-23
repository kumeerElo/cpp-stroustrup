#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)
#include "Window.h" // mks
#include <vector>

using namespace Graph_lib;

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation
static int counter = 0;
struct Simple_window : Graph_lib::Window {
	Simple_window(Point xy, int w, int h, const string& title );
	/*: Window(xy,w,h,title),
	  button_pushed(false),
	  next_button(Point(x_max()-70,0), 70, 20, "Next", cb_next) { attach(next_button); }*///mks
	
	void wait_for_button()
	// modified event loop
	// handle all events (as per default), but quit when button_pushed becomes true
	// this allows graphics without control inversion
	{
		while (!button_pushed) Fl::wait();
		button_pushed = false;
		Fl::redraw();
	}

	//Button next_button;
	Button* next_button;
//private:
  protected:
	bool button_pushed;
	
	static void cb_next(Address, Address addr) // callback for next_button
	//	{ reference_to<Simple_window>(addr).next(); }
	{
		static_cast<Simple_window*>(addr)->next();
	}

	virtual void next() { button_pushed = true; }

};

class Main_window: public Simple_window
{
public:
	Button* quit_button;
	Main_window(Point xy, int w, int h, const string& title)
	:Simple_window(xy,w,h,title)
	{
		Button* quit_button = new Button(Point(x_max()-70,20),70,20,"quit",cb_quit);
		attach(*quit_button);
	}
private:
	static void cb_quit(Address, Address addr)
	{
		reference_to<Main_window>(addr).quit();
	}
	//void quit() { button_pushed = true;}
	void quit() { hide();}
	void next() {}
};


/*note to the future 

in the following example, if you make m_square a pointer in the class, the function press_button after the callback function doesn't find rectangle. An unknown rectangle is passed, and when 
we try to make any change to it, such as color or style, it gives out a segmentation fault. 
Implemenetation works if we make m_square not a regular memeber as done below - 
*/

class CheckerBoard:public Main_window
{
public:
	CheckerBoard(Point xy, int w, int h, const string& title);
private:
	Rectangle m_square0;
	Rectangle m_square1; 
	Rectangle m_square2;
	Rectangle m_square3; 
	Rectangle m_square4; 
	Rectangle m_square5; 
	Rectangle m_square6; 
	Rectangle m_square7; 
	Rectangle m_square8; 
	Vector_ref<Button> m_buttons;
	vector<int> m_pressed;

	static void cb_button_0(Address, Address addr);
	static void cb_button_1(Address, Address addr);
	static void cb_button_2(Address, Address addr);
	static void cb_button_3(Address, Address addr);
	static void cb_button_4(Address, Address addr);
	static void cb_button_5(Address, Address addr);
	static void cb_button_6(Address, Address addr);
	static void cb_button_7(Address, Address addr);
	static void cb_button_8(Address, Address addr);

	void press_button(int i);
};

class ImageButton:public Main_window
{
public:
	ImageButton(Point xy, int w, int h, const string& title);
private:
	Button* m_button;
	Image m_image;
	static void cb_button_move(Address, Address addr);
	void move_stuff();
	int get_random_int(int low, int high);
};

class DisplayShape: public Main_window
{
	enum Type {circle,square,hex};
public:
	DisplayShape(Point xy, int w, int h, const string& title);

private:
	const int m_size = 50;
	In_box m_x;
	In_box m_y;
	Menu m_shape;
	static void cb_button_square(Address, Address addr);
	static void cb_button_circle(Address, Address addr);
	static void cb_button_hex(Address, Address addr);
	void press_shape(Type type);

};
