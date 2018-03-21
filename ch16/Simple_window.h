#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)
#include "Window.h" // mks

using namespace Graph_lib;

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

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
	void quit() { button_pushed = true;}
	void next() {};
};

