
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"
//------------------------------------------------------------------------------

const int buttonSize = 100;
const int dx = 100;
const int dy = 100;

Simple_window::Simple_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
    //next_button(Point(x_max()-70,0), 70, 20, "Next", cb_next),
    button_pushed(false)
{
    //attach(next_button);
    Button* next_button = new Button(Point(x_max()-70,0), 70, 20, "Next", cb_next);
    attach(*next_button);
}

void ImageButton::cb_button_move(Address, Address addr)
{
	reference_to<ImageButton>(addr).move_stuff();
}

int ImageButton::get_random_int(int low, int high)
{
	return low + rand()%(high-low);
}

void ImageButton::move_stuff()
{
	int n = get_random_int(0,4);
	Point center = Point(m_button->loc.x, m_button->loc.y);

	switch (n){
		case 0:
			m_button->move(x_max()-100-center.x, 100-center.y);
			m_image.move(x_max()-100-center.x, 100-center.y);
			break;
		case 1:
			m_button->move(x_max()-100-center.x, y_max()-100-center.y);
			m_image.move(x_max()-100-center.x, y_max()-100-center.y);
			break;
		case 2:
			m_button->move(100-center.x, y_max()-100-center.y);
			m_image.move(100-center.x, y_max()-100-center.y);
			break;
		case 3:
			m_button->move(100-center.x, 100-center.y);
			m_image.move(100-center.x, 100-center.y);
			break;
		default:
			error ("ImageButton:move_stuff()", "random numbers should be 0-4");
	}
}

ImageButton::ImageButton(Point xy, int w, int h, const string& title)
	: Main_window(xy, w, h, title),
		m_image(Point(x_max()/2, y_max()/2), "queen.jpg")
{
	m_button = new Button (Point(x_max()/2, y_max()/2), dx, dy, "", cb_button_move);
	m_image.set_mask(Point(x_max()/5, y_max()/4),dx,dy);
	attach(m_image);
	attach(*m_button);
}	

void DisplayShape::cb_button_square(Address, Address addr)
{
	reference_to<DisplayShape>(addr).press_shape(Type::square);
}

void DisplayShape::cb_button_circle(Address, Address addr)
{
	reference_to<DisplayShape>(addr).press_shape(Type::circle);
}

void DisplayShape::cb_button_hex(Address, Address addr)
{
	reference_to<DisplayShape>(addr).press_shape(Type::hex);
}

void DisplayShape::press_shape(Type type)
{
	int x = m_x.get_int();
	int y = m_y.get_int();

	switch (type){
		case circle:{
			Point c = m_circle->center();
			m_circle->move(x-c.x,y-c.y);
			attach(*m_circle);
			break;
		}
		case square:{
			Point offset = m_square->tl();
			m_square->move(x-offset.x,y-offset.y);
			attach(*m_square);
			break;
		}
		case hex:{
			//there is a bug here, offsets are wrong, hex keeps moving -to be looked at later
			Point offset = m_hex->center();
			m_hex->move(x-offset.x,y-offset.y);
			attach(*m_hex);
			break;
		}
		default:
			error("DisplayShape::press_shape", "unknown shape");
	}
	redraw();
}

void DisplayShape::next()
{
//as of now move everything -- 

	int x = m_new_x.get_int();
	int y = m_new_y.get_int();

	Point c = m_circle->center();
	m_circle->move(x-c.x,y-c.y);

	Point offset = m_square->tl();
	m_square->move(x-offset.x,y-offset.y);

	offset = m_hex->center();
	m_hex->move(x-offset.x,y-offset.y);
	
	redraw();
}

DisplayShape::DisplayShape(Point xy, int w, int h, const string& title)
	:Main_window(xy, w, h, title),
	 m_x(Point(x_max()-200,0),70,20, "x"), 
	 m_y(Point(x_max()-200,20),70,20, "y"),
	 m_new_x(Point(x_max()-300,0),70,20, "new_x"), 
	 m_new_y(Point(x_max()-300,20),70,20, "new_y"),
	 m_shape(Point(x_max()-70,100),70,20, Menu::Kind::vertical, "shape")
{
	Button* square = new Button (m_shape.location(),0,0,"square", cb_button_square);
	Button* circle = new Button (m_shape.location(),0,0,"circle", cb_button_circle);
	Button* hex = new Button (m_shape.location(),0,0,"hex", cb_button_hex);

	m_circle = new Circle(Point(0,0),m_size);
	m_square = new Rectangle(Point(0,0),m_size, m_size);
	m_hex	= new Regular_hexagon(Point(100,100),m_size);

	m_shape.attach(square);
	m_shape.attach(circle);
	m_shape.attach(hex);
	attach(m_x);
	attach(m_y);
	attach(m_new_x);
	attach(m_new_y);
	attach(m_shape);
}

void CheckerBoard::press_button(int n)
{
	switch(n){
		case 0:
		{
			if (m_pressed[0]){
				m_square0.set_visibility(Color::Transparency::invisible);
				m_pressed[0]=0;
			}else{
				m_square0.set_fill_color(Color::blue);
				m_pressed[0]=1;
			}
			break;
		}
		case 1:
		{
			if (m_pressed[1]){
				m_square1.set_visibility(Color::Transparency::invisible);
				m_pressed[1]=0;
			}else{
				m_square1.set_fill_color(Color::blue);
				m_pressed[1]=1;
			}
			break;
		}
		case 2:
		{
			if (m_pressed[2]){
				m_square2.set_visibility(Color::Transparency::invisible);
				m_pressed[2]=0;
			}else{
				m_square2.set_fill_color(Color::blue);
				m_pressed[2]=1;
			}
			break;
		}
		case 3:
		{
			if (m_pressed[3]){
				m_square3.set_visibility(Color::Transparency::invisible);
				m_pressed[3]=0;
			}else{
				m_square3.set_fill_color(Color::blue);
				m_pressed[3]=1;
			}
			break;
		}
		case 4:
		{
			if (m_pressed[4]){
				m_square4.set_visibility(Color::Transparency::invisible);
				m_pressed[4]=0;
			}else{
				m_square4.set_fill_color(Color::blue);
				m_pressed[4]=1;
			}
			break;
		}
		case 5:
		{
			if (m_pressed[5]){
				m_square5.set_visibility(Color::Transparency::invisible);
				m_pressed[5]=0;
			}else{
				m_square5.set_fill_color(Color::blue);
				m_pressed[5]=1;
			}
			break;
		}
		case 6:
		{
			if (m_pressed[6]){
				m_square6.set_visibility(Color::Transparency::invisible);
				m_pressed[6]=0;
			}else{
				m_square6.set_fill_color(Color::blue);
				m_pressed[6]=1;
			}
			break;
		}
		case 7:
		{
			if (m_pressed[7]){
				m_square7.set_visibility(Color::Transparency::invisible);
				m_pressed[7]=0;
			}else{
				m_square7.set_fill_color(Color::blue);
				m_pressed[7]=1;
			}
			break;
		}
		case 8:
		{
			if (m_pressed[8]){
				m_square8.set_visibility(Color::Transparency::invisible);
				m_pressed[8]=0;
			}else{
				m_square8.set_fill_color(Color::blue);
				m_pressed[8]=1;
			}
			break;
		}
	}
}

void CheckerBoard::cb_button_0(Address, Address addr)
{
	reference_to<CheckerBoard>(addr).press_button(0);
}
void CheckerBoard::cb_button_1(Address, Address addr)
{
	reference_to<CheckerBoard>(addr).press_button(1);
}
void CheckerBoard::cb_button_2(Address, Address addr)
{
	reference_to<CheckerBoard>(addr).press_button(2);
}
void CheckerBoard::cb_button_3(Address, Address addr)
{
	reference_to<CheckerBoard>(addr).press_button(3);
}
void CheckerBoard::cb_button_4(Address, Address addr)
{
	reference_to<CheckerBoard>(addr).press_button(4);
}
void CheckerBoard::cb_button_5(Address, Address addr)
{
	reference_to<CheckerBoard>(addr).press_button(5);
}
void CheckerBoard::cb_button_6(Address, Address addr)
{
	reference_to<CheckerBoard>(addr).press_button(6);
}
void CheckerBoard::cb_button_7(Address, Address addr)
{
	reference_to<CheckerBoard>(addr).press_button(7);
}
void CheckerBoard::cb_button_8(Address, Address addr)
{
	reference_to<CheckerBoard>(addr).press_button(8);
}

CheckerBoard::CheckerBoard(Point xy, int w, int h, const string& title)
	:Main_window(xy,w,h,title),
	 m_square0(Point(100,100),buttonSize,buttonSize),
	 m_square1(Point(100+dx,100),buttonSize,buttonSize),
	 m_square2(Point(100+2*dx,100),buttonSize,buttonSize),
	 m_square3(Point(100,100+dy),buttonSize,buttonSize),
	 m_square4(Point(100+dx,100+dy),buttonSize,buttonSize),
	 m_square5(Point(100+2*dx,100+dy),buttonSize,buttonSize),
	 m_square6(Point(100,100+2*dy),buttonSize,buttonSize),
	 m_square7(Point(100+dx,100+2*dy),buttonSize,buttonSize),
	 m_square8(Point(100+2*dx,100+2*dy),buttonSize,buttonSize),
	 m_pressed(false)
{

	int num = 0;
	for (int j=0; j<3; j++){
		for (int i=0; i<3; i++){
			num = i+j*3;
			switch(num){
				case 0:{
				Button* b = new Button(Point(100+i*dx,100+j*dy),buttonSize, buttonSize, "", cb_button_0); 
				m_buttons.push_back(b);
				break;
				}
				case 1:{
				Button* b = new Button(Point(100+i*dx,100+j*dy),buttonSize, buttonSize, "", cb_button_1); 
				m_buttons.push_back(b);
				break;
				}
				case 2:{
				Button* b = new Button(Point(100+i*dx,100+j*dy),buttonSize, buttonSize, "", cb_button_2); 
				m_buttons.push_back(b);
				break;
				}
				case 3:{
				Button* b = new Button(Point(100+i*dx,100+j*dy),buttonSize, buttonSize, "", cb_button_3); 
				m_buttons.push_back(b);
				break;
				}
				case 4:{
				Button* b = new Button(Point(100+i*dx,100+j*dy),buttonSize, buttonSize, "", cb_button_4); 
				m_buttons.push_back(b);
				break;
				}
				case 5:{
				Button* b = new Button(Point(100+i*dx,100+j*dy),buttonSize, buttonSize, "", cb_button_5); 
				m_buttons.push_back(b);
				break;
				}
				case 6:{
				Button* b = new Button(Point(100+i*dx,100+j*dy),buttonSize, buttonSize, "", cb_button_6); 
				m_buttons.push_back(b);
				break;
				}
				case 7:{
				Button* b = new Button(Point(100+i*dx,100+j*dy),buttonSize, buttonSize, "", cb_button_7); 
				m_buttons.push_back(b);
				break;
				}
				case 8:{
				Button* b = new Button(Point(100+i*dx,100+j*dy),buttonSize, buttonSize, "", cb_button_8); 
				m_buttons.push_back(b);
				break;
				}
				default:
					error ("a", "b");
			}
		}
	}

	for (int i=0; i<9; i++){
		m_pressed.push_back(0);
	}

	attach(m_square0);
	attach(m_square1);
	attach(m_square2);
	attach(m_square3);
	attach(m_square4);
	attach(m_square5);
	attach(m_square6);
	attach(m_square7);
	attach(m_square8);

	for (int i=0; i<9; i++)
		attach(m_buttons[i]);
}

