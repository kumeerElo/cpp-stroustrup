#include "GUI.h"
#include "std_lib_facilities.h"
#include <sstream>

//using namespace Graph_lib;

namespace Graph_lib{
void Button::attach(Window& win)
  {
    pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
    pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
    own = &win;
  }

int In_box::get_int()
{
  Fl_Input& pi = reference_to<Fl_Input>(pw);
//  return atoi(pi.value());
  const char* p = pi.value();
  if (!isdigit(p[0])) return -999999;
  return atoi(p);
}

string In_box::get_string()
{
  Fl_Input& pi = reference_to<Fl_Input>(pw);
  return string(pi.value());
}

void In_box::attach(Window& win)
{
  pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
  own = &win;
}

void Out_box::put(int i)
{
  Fl_Output& po = reference_to<Fl_Output>(pw);
  std::stringstream ss;
  ss << i;
  po.value(ss.str().c_str());
}

void Out_box::put(const string& s)
{
  reference_to<Fl_Output>(pw).value(s.c_str());
}

void Out_box::attach(Window& win)
{
  pw = new Fl_Output(loc.x, loc.y, width, height, label.c_str());
  own = &win;
}

/*
Menu::Menu(Point xy, int w, int h, Kind kk, const string& s)
:Widget(xy,w,h,s,0), k(kk), offset(0)
{
}
*/
int Menu::attach(Button& b)
{
  b.width = width;
  b.height = height;

  switch(k) {
  case horizontal:
    //b.loc = Point(loc.x+offset,loc.y);
    b.loc = Point(loc.x+offset,loc.y+b.height);
    offset+=b.width;
    break;
  case vertical:
    //b.loc = Point(loc.x,loc.y+offset);
		//this way the buttons of the menu will open to the left
    b.loc = Point(loc.x-b.width,loc.y+offset);  
    offset+=b.height;
    break;
  }
  selection.push_back(&b);
  return int(selection.size()-1);
}

int Menu::attach(Button* p)
{
//  owned.push_back(p);
  return attach(*p);
}

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window(xy,w,h,title),
	 next_button(Point(x_max()-150,0),70,20,"Next point", cb_next),
	 quit_button(Point(x_max()-70,0),70,20,"Quit", cb_quit),
	 next_x(Point(x_max()-310,0),50,20,"next x:"),
	 next_y(Point(x_max()-210,0),50,20,"next y:"),
	 xy_out(Point(100,0),100,20,"current(x,y):")
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	attach(lines);
}

void Lines_window::cb_quit(Address, Address pw)
{
	reference_to<Lines_window>(pw).quit();
}

void Lines_window::quit()
{
	hide();
}

void Lines_window::cb_next(Address, Address pw)
{
	reference_to<Lines_window>(pw).next();
}

void Lines_window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();

	lines.add(Point(x,y));

	ostringstream os;
	os << '(' << x << ',' << y << ')';
	xy_out.put(os.str());

	redraw();
}

void Color_lines_window::cb_quit(Address, Address pw)
{
	reference_to<Color_lines_window>(pw).quit();
}

void Color_lines_window::quit()
{
	hide();
}

void Color_lines_window::cb_next(Address, Address pw)
{
	reference_to<Color_lines_window>(pw).next();
}

void Color_lines_window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();

	lines.add(Point(x,y));

	ostringstream os;
	os << '(' << x << ',' << y << ')';
	xy_out.put(os.str());

	redraw();
}

void Color_lines_window::cb_color_red(Address, Address pw)
{
	reference_to<Color_lines_window>(pw).change_color_red();
}

void Color_lines_window::change_color_red()
{
	lines.set_color(Color::red);
	redraw();
}

void Color_lines_window::cb_color_blue(Address, Address pw)
{
	reference_to<Color_lines_window>(pw).change_color_blue();
}

void Color_lines_window::change_color_blue()
{
	lines.set_color(Color::blue);
	redraw();
}

void Color_lines_window::cb_color_green(Address, Address pw)
{
	reference_to<Color_lines_window>(pw).change_color_green();
}

void Color_lines_window::change_color_green()
{
	lines.set_color(Color::green);
	redraw();
}

void Color_lines_window::cb_color_button(Address, Address pw)
{
	reference_to<Color_lines_window>(pw).press_color_button();
}

void Color_lines_window::press_color_button()
{
	if (is_color_pressed){
		color_button.show();	
		color_menu.hide();
		is_color_pressed = false;
	}else{
		color_menu.show();
		is_color_pressed = true;
	}
}

void Color_lines_window::cb_ls_dot(Address, Address pw)
{
	reference_to<Color_lines_window>(pw).change_ls_dot();
}

void Color_lines_window::change_ls_dot()
{
	lines.set_style(Line_style::dot);
	redraw();
}

void Color_lines_window::cb_ls_dash(Address, Address pw)
{
	reference_to<Color_lines_window>(pw).change_ls_dash();
}

void Color_lines_window::change_ls_dash()
{
	lines.set_style(Line_style::dash);
	redraw();
}

void Color_lines_window::cb_ls_solid(Address, Address pw)
{
	reference_to<Color_lines_window>(pw).change_ls_solid();
}

void Color_lines_window::change_ls_solid()
{
	lines.set_style(Line_style::solid);
	redraw();
}

void Color_lines_window::cb_ls_button(Address, Address pw)
{
	reference_to<Color_lines_window>(pw).press_ls_button();
}

void Color_lines_window::press_ls_button()
{
	if (is_ls_pressed){
		ls_button.show();	
		ls_menu.hide();
		is_ls_pressed = false;
	}else{
		ls_menu.show();
		is_ls_pressed = true;
	}
}

Color_lines_window::Color_lines_window(Point xy, int w, int h, const string& title)
	:Window(xy,w,h,title),
	 next_button(Point(x_max()-150,0),70,20,"Next point", cb_next),
	 quit_button(Point(x_max()-70,0),70,20,"Quit", cb_quit),
	 color_button(Point(x_max()-70,50),70,20,"Color", cb_color_button),
	 ls_button(Point(0,20),70,20,"lineStyle",cb_ls_button),
	 next_x(Point(x_max()-310,0),50,20,"next x:"),
	 next_y(Point(x_max()-210,0),50,20,"next y:"),
	 xy_out(Point(100,0),100,20,"current(x,y):"),
	 color_menu(Point(x_max()-100,50),100,20, Menu::Kind::vertical, "color_menu"),
	 ls_menu(Point(0,20),70,20, Menu::Kind::horizontal, "lineStyle_menu"),
	 is_color_pressed(false),
	 is_ls_pressed(false)
{
	Button* red_button = new Button(Point(0,0),0,0, "red", cb_color_red);
	Button* blue_button = new Button(Point(0,0),0,0, "blue", cb_color_blue);
	Button* green_button = new Button(Point(0,0),0,0, "green", cb_color_green);
	color_menu.attach(red_button);
	color_menu.attach(blue_button);
	color_menu.attach(green_button);

	Button* dot_button = new Button(Point(0,0),0,0, "dot", cb_ls_dot);
	Button* dash_button = new Button(Point(0,0),0,0, "dash", cb_ls_dash);
	Button* solid_button = new Button(Point(0,0),0,0, "solid", cb_ls_solid);

	ls_menu.attach(dot_button);
	ls_menu.attach(dash_button);
	ls_menu.attach(solid_button);

	attach(next_button);
	attach(quit_button);
	attach(ls_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	attach(color_menu);
	color_menu.hide();
	attach(color_button);
	attach(ls_menu);
	ls_menu.hide();
	attach(lines);
}

}//Graph_lib

