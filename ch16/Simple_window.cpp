
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"
//------------------------------------------------------------------------------

const int buttonSize = 40;
const int dx = 40;
const int dy = 40;

Simple_window::Simple_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
    //next_button(Point(x_max()-70,0), 70, 20, "Next", cb_next),
    button_pushed(false)
{
    //attach(next_button);
    Button* next_button = new Button(Point(x_max()-70,0), 70, 20, "Next", cb_next);
    attach(*next_button);
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


//------------------------------------------------------------------------------
/* mks commented out this function. there is alternate defintion in the header file
bool Simple_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show();
    button_pushed = false;
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return button_pushed;
}
*/
//------------------------------------------------------------------------------
/* mks commented out. see header file for the alternate defintion

void Simple_window::cb_next(Address, Address pw)
// call Simple_window::next() for the window located at pw
{  
    reference_to<Simple_window>(pw).next();    
}

//------------------------------------------------------------------------------

void Simple_window::next()
{
    button_pushed = true;
    hide();
}

//------------------------------------------------------------------------------

*/
