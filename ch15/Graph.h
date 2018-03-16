//#ifndef GRAPH_GUARD
//#define GRAPH_GUARD 1

#include "Point.h"
//#include<vector>
//#include<string>
//#include<cmath>
#include "fltk.h"
#include "std_lib_facilities.h"
#include <vector>

namespace Graph_lib {
// defense against ill-behaved Linux macros:
#undef major
#undef minor

struct Color {
  enum Color_type {
    red=FL_RED, blue=FL_BLUE, green=FL_GREEN,
    yellow=FL_YELLOW, white=FL_WHITE, black=FL_BLACK,
    magenta=FL_MAGENTA, cyan=FL_CYAN, dark_red=FL_DARK_RED,
    dark_green=FL_DARK_GREEN, dark_yellow=FL_DARK_YELLOW, dark_blue=FL_DARK_BLUE,
    dark_magenta=FL_DARK_MAGENTA, dark_cyan=FL_DARK_CYAN
  };
  enum Transparency { invisible = 0, visible=255 };

  Color(Color_type cc) :c(Fl_Color(cc)), v(visible) { }
  Color(Color_type cc, Transparency vv) :c(Fl_Color(cc)), v(vv) { }
  Color(int cc) :c(Fl_Color(cc)), v(visible) { }
  Color(Transparency vv) :c(Fl_Color()), v(vv) { }

  int as_int() const { return c; }
  char visibility() const { return v; }
  void set_visibility(Transparency vv) { v=vv; }
private:
  unsigned char v;  // 0 or 1 for now
  Fl_Color c;
};

struct Line_style {
  enum Line_style_type {
    solid=FL_SOLID,       // -------
    dash=FL_DASH,       // - - - -
    dot=FL_DOT,         // ....... 
    dashdot=FL_DASHDOT,     // - . - . 
    dashdotdot=FL_DASHDOTDOT, // -..-..
  };
  Line_style(Line_style_type ss) :s(ss), w(0) { }
  Line_style(Line_style_type lst, int ww) :s(lst), w(ww) { }
  Line_style(int ss) :s(ss), w(0) { }
	void set_width (int width){
		w+=width;
	}
  int width() const { return w; }
  int style() const { return s; }
private:
  int s;
  int w;
};

class Font {
public:
  enum Font_type {
    helvetica=FL_HELVETICA,
    helvetica_bold=FL_HELVETICA_BOLD,
    helvetica_italic=FL_HELVETICA_ITALIC,
    helvetica_bold_italic=FL_HELVETICA_BOLD_ITALIC,
    courier=FL_COURIER,
    courier_bold=FL_COURIER_BOLD,
    courier_italic=FL_COURIER_ITALIC,
    courier_bold_italic=FL_COURIER_BOLD_ITALIC,
    times=FL_TIMES,
    times_bold=FL_TIMES_BOLD,
    times_italic=FL_TIMES_ITALIC,
    times_bold_italic=FL_TIMES_BOLD_ITALIC,
    symbol=FL_SYMBOL,
    screen=FL_SCREEN,
    screen_bold=FL_SCREEN_BOLD,
    zapf_dingbats=FL_ZAPF_DINGBATS
  };

  Font(Font_type ff) :f(ff) { }
  Font(int ff) :f(ff) { }

  int as_int() const { return f; }
private:
  int f;
};

template<class T> class Vector_ref {
  vector<T*> v;
  vector<T*> owned;
public:
  Vector_ref() {}

  Vector_ref(T* a, T* b=0, T* c=0, T* d=0)
  {
      if (a) push_back(a);
      if (b) push_back(b);
      if (c) push_back(c);
      if (d) push_back(d);
  }

  ~Vector_ref() { for (int i=0; i<owned.size(); ++i) delete owned[i]; }

  void push_back(T& s) { v.push_back(&s); }
  void push_back(T* p) { v.push_back(p); owned.push_back(p); }

  // ???void erase(???)

  T& operator[](int i) { return *v[i]; }
  const T& operator[](int i) const { return *v[i]; }
  int size() const { return v.size(); }
};

typedef double Fct(double);

class Shape  {  // deals with color and style, and holds sequence of lines
protected:
  Shape() { }
  Shape(initializer_list<Point> lst);  // add() the Points to this Shape
  void add(Point p){ points.push_back(p); }
  void set_point(int i, Point p) { points[i] = p; }
  virtual void draw_lines() const;  // simply draw the appropriate lines

public:
  virtual void draw() const;          // deal with color and draw_lines
  virtual void move(int dx, int dy);  // move the shape +=dx and +=dy

  void set_color(Color col) { lcolor = col; }
  Color color() const { return lcolor; }

  void set_style(Line_style sty) { ls = sty; }
  Line_style style() const { return ls; }

/*
  void set_line_width(int w) { this->get_ls().set_width(w); } // mks 
	Line_style get_ls() {return ls;}	
*/
 
	void set_line_width(int w){ls.set_width(w);} 

  void set_fill_color(Color col) { fcolor=col;}
  Color fill_color() const { return fcolor; }

  Point point(int i) const { return points[i]; }
  int number_of_points() const { return int(points.size()); }

  virtual ~Shape() { }
  Shape(const Shape&) = delete;
  Shape& operator=(const Shape&) = delete;

private:
  vector<Point> points; // not used by all shapes
  Color lcolor {fl_color()};
  Line_style ls {0};
  Color fcolor {Color::invisible};
};

struct Function : Shape {
  // the function parameters are not stored
  Function(Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
  //Function(Point orig, Fct f, double r1, double r2, int count, double xscale = 1, double yscale = 1); 
};

struct Fill {
  Fill() :no_fill(true), fcolor(0) { }
  Fill(Color c) :no_fill(false), fcolor(c) { }

  void set_fill_color(Color col) { fcolor = col; }
  Color fill_color() { return fcolor; }
protected:
  bool no_fill;
  Color fcolor;
};

struct Line : Shape {
  Line(Point p1, Point p2) { add(p1); add(p2); }
};

struct Rectangle : Shape {

  Rectangle(Point xy, int ww, int hh) :w{ ww }, h{ hh }
  {
    if (h<=0 || w<=0) error("Bad rectangle: non-positive side");
    add(xy);
  }
  Rectangle(Point x, Point y) :w{ y.x - x.x }, h{ y.y - x.y }
  {
    if (h<=0 || w<=0) error("Bad rectangle: first point is not top left");
    add(x);
  }
  void draw_lines() const;

//  void set_fill_color(Color col) { fcolor = col; }
//  Color fill_color() { return fcolor; }

  int height() const { return h; }
  int width() const { return w; }
private:
  int h;      // height
  int w;      // width
//  Color fcolor; // fill color; 0 means "no fill"
};

bool intersect(Point p1, Point p2, Point p3, Point p4);


struct Open_polyline : Shape {  // open sequence of lines
  using Shape::Shape;
  void add(Point p) { Shape::add(p); } 
  void draw_lines() const;
};

struct Closed_polyline : Open_polyline {  // closed sequence of lines
  using Open_polyline::Open_polyline;
  void draw_lines() const;
  
//  void add(Point p) { Shape::add(p); }
};


struct Polygon : Closed_polyline {  // closed sequence of non-intersecting lines
  using Closed_polyline::Closed_polyline;
  void add(Point p);
  void draw_lines() const;
};

struct Lines : Shape {  // indepentdent lines
  Lines() {}
  Lines(initializer_list<Point> lst) : Shape{lst} { if (lst.size() % 2) error("odd number of points for Lines"); }
  void draw_lines() const;
  void add(Point p1, Point p2) { Shape::add(p1); Shape::add(p2); }
};

struct Text : Shape {
  // the point is the bottom left of the first letter
  Text(Point x, const string& s) : lab{ s } { add(x); }

  void draw_lines() const;

  void set_label(const string& s) { lab = s; }
  string label() const { return lab; }

  void set_font(Font f) { fnt = f; }
  Font font() const { return Font(fnt); }

  void set_font_size(int s) { fnt_sz = s; }
  int font_size() const { return fnt_sz; }
private:
  string lab; // label
  Font fnt{ fl_font() };
  int fnt_sz{ (14<fl_size()) ? fl_size() : 14 };  // at least 14 point
};


struct Axis : Shape {
  // representation left public
  enum Orientation { x, y, z };
  Axis(Orientation d, Point xy, int length, int nummber_of_notches=0, string label = "");

  void draw_lines() const;
  void move(int dx, int dy);

  void set_color(Color c);

  Text label;
  Lines notches;
//  Orientation orin;
//  int notches;
};

struct Circle : Shape {
  Circle(Point p, int rr) // center and radius
  :r{ rr } {
    add(Point{ p.x - r, p.y - r });
  }

  void draw_lines() const;

  Point center() const { return { point(0).x + r, point(0).y + r }; }

  void set_radius(int rr) { r=rr; }
  int radius() const { return r; }
	//void move(int dx, int dy){Shape::move(0,0);}//make the circle unmovable
	void move(int dx, int dy){Shape::move(dx,dy);}//make the circle unmovable
private:
  int r;
};


struct Ellipse : Shape {
	Ellipse():w(0),h(0){};
  Ellipse(Point p, int ww, int hh)  // center, min, and max distance from center
  :w{ ww }, h{ hh } {
    add(Point{ p.x - ww, p.y - hh });
  }

  void draw_lines() const;

  Point center() const { return{ point(0).x + w, point(0).y + h }; }
  Point focus1() const { return{ center().x + int(sqrt(double(w*w - h*h))), center().y }; }
  Point focus2() const { return{ center().x - int(sqrt(double(w*w - h*h))), center().y }; }
  
  void set_major(int ww) { w=ww; }
  int major() const { return w; }
  void set_minor(int hh) { h=hh; }
  int minor() const { return h; }
private:
  int w;
  int h;
};
/*
struct Mark : Text {
  static const int dw = 4;
  static const int dh = 4;
  Mark(Point xy, char c) : Text(Point(xy.x-dw, xy.y+dh),string(1,c)) {}
};
*/

struct Marked_polyline : Open_polyline {
  //Marked_polyline(const string& m) :mark(m) { }
  Marked_polyline(const string& m) :mark(m) {if (m=="") mark = "*";}
  void draw_lines() const;
private:
  string mark;
};

struct Marks : Marked_polyline {
  Marks(const string& m) :Marked_polyline(m)
  { set_color(Color(Color::invisible)); }
};

struct Mark : Marks {
  Mark(Point xy, char c) : Marks(string(1,c)) {add(xy); }
};

/*

struct Marks : Shape {
  Marks(char m) : mark(string(1,m)) { }
  void add(Point p) { Shape::add(p); }
  void draw_lines() const;
private:
  string mark;
};
*/

struct Bad_image : Fl_Image {
  Bad_image(int h, int w) : Fl_Image(h,w,0) { }
  void draw(int x,int y, int, int, int, int) { draw_empty(x,y); }
};

struct Suffix {
  enum Encoding { none, jpg, gif, bmp };
};

Suffix::Encoding get_encoding(const string& s);

struct Image : Shape {
  Image(Point xy, string s, Suffix::Encoding e = Suffix::none);
  ~Image() { delete p; }
  void draw_lines() const;
  void set_mask(Point xy, int ww, int hh) { w=ww; h=hh; cx=xy.x; cy=xy.y; }
  void move(int dx,int dy) { 
		Shape::move(dx,dy); 
		p->draw(point(0).x,point(0).y); 
  }
private:
  int w,h,cx,cy; // define "masking box" within image relative to position (cx,cy)
  Fl_Image* p;
  Text fn;
};

Point north(Rectangle &r);
Point south(Rectangle &r);
Point east(Rectangle &r);
Point west(Rectangle &r);
Point center(Rectangle &r);
Point northwest(Rectangle &r);
Point northeast(Rectangle &r);
Point southeast(Rectangle &r);
Point southwest(Rectangle &r);
double distance (Point p1, Point p2);
Point rotate();

struct Arc: Shape{
public:
	Arc():m_w(0), m_h(0), m_theta1(0), m_theta2(0){} 
  Arc(Point p, double w, double h, int theta1, int theta2);
  void draw_lines() const;
private:
	double m_w;
	double m_h;
	int m_theta1; // arc will be drawn from theta1 to theta2
	int m_theta2; 
};

struct Line_mks : Shape {
  Line_mks(Point p1, Point p2):m_p1(p1), m_p2(p2) { Shape::add(p1); Shape::add(p2); }
	Line_mks();
	double length() const;
	bool is_parallel_x() const;
	bool is_parallel_y() const;
	Point left_corner() const; // only possible for lines parallel to x or y
	Point right_corner() const; // only possible for lines parallel to x or y
	Point top_corner() const;	// only possible for lines parallel to x or y
	Point bottom_corner() const;	// only possible for lines parallel to x or y
	bool is_left(Line_mks* line) const;
	bool is_top(Line_mks* line) const;
	Point p1() {return m_p1;}
	Point p2() {return m_p2;}
	double angle(string end = "p2"); // by default the arrow-head is on p2
  //void add_arrow_head(string end = "p2");
private:
	Point m_p1;
	Point m_p2;
};

struct Box: Shape
{
	Box(Point p, int w, int h);
	void draw_lines() const;
	void get_center(Point& center, double w, double h, string type);
	vector<Line_mks*> get_lines(Point p, int w, int h);
	Rectangle* rectangle(){return m_rect;};
private:
	Rectangle* m_rect;
	Line_mks* m_left;
	Line_mks* m_top;
	Line_mks* m_right;
	Line_mks* m_bottom;
	Arc* m_topLeft;
	Arc* m_topRight;
	Arc* m_bottomRight;
	Arc* m_bottomLeft;
};


struct Box_mks: Rectangle 
//struct Box_mks:Shape
{
	Box_mks(Point p, int w, int h);
	void draw_lines()const;
};


/* method 2 - implementation of box_mks
 this implementation is buggy - you can't change color of arcs from the object 
 of Box_mks. Only color inside the rectangle change. Surprisingly, you can change 
 line style of the whole box. So, part of inheritance is not working or some other implementation is wrong. 
 
struct Box_mks: Arc
{
	Box_mks(Point p, int w, int h);
	void draw_lines()const;
	private:
		Arc* m_topLeft;
		Arc* m_topRight;
		Arc* m_bottomRight;
		Arc* m_bottomLeft;
};
*/

struct Arrow: Shape
{
	Arrow(Line_mks* line, string end = "p2"); // by default the arrow will be put on the second point 

	Arrow(Point p1, Point p2, string end = "p2"); // by default the arrow will be put on the second point 
	void create_arrow();
	void draw_lines() const;
	Point rotate(Point p, double theta);
	private:
		string m_end;
		Line_mks* m_line;
};

struct BoxWithText: Shape
{
	BoxWithText(Box_mks* box, const string text);
	void draw_lines()const;
private:
	Box_mks* m_box;
	Text* m_text;	
};

struct RightAngledTriag: Shape
{
	RightAngledTriag(Point p, int w, int h);
	RightAngledTriag(Point p1, Point p2, Point p3);
	
	void draw_lines ()const;
	RightAngledTriag* flip_horizontal();
	RightAngledTriag* rotate_p1_p2(double theta);
	RightAngledTriag* rotate_p2(double theta);
	
	Point p1() const {return m_p1;}
	Point p2() const {return m_p2;}
	Point p3() const {return m_p3;}
	int width() const {return distance(m_p1, m_p2);}
	int height() const{return distance(m_p1, m_p3);}
private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
};

struct RightAngledTriag2: Polygon 
{
	RightAngledTriag2(Point p, int w, int h);
	RightAngledTriag2(Point p1, Point p2, Point p3);
	RightAngledTriag2* rotate_p1_p2(double theta);
	RightAngledTriag2* rotate_p2(double theta);

	Point p1() const {return m_p1;}
	Point p2() const {return m_p2;}
	Point p3() const {return m_p3;}
private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
};

/* I love this class :) - beautiful depiction of inheritance
1. Three points get added just by calling constructor of the base class, in this case, RightAngledTriag2. 
2. No need to call other functions such as draw_lines(), set_color, set_fill_color, etc as they get called automatically as part of the inheritance. 
*/

struct Triangle: RightAngledTriag2
{
	Triangle(Point p, int w, int h);
};


struct Octogon: Shape
{
	Octogon(Point p, int side);
	void draw_lines() const;
  void set_fill_color(Color col);
	void give_diff_color();
private:
	Vector_ref<RightAngledTriag2> m_triangles;
};


struct Regular_hexagon:Shape
{
	Regular_hexagon(Point center, int side);
	void draw_lines()const;
  void set_fill_color(Color col) { 
		for (int i=0; i<m_triangles.size(); i++){
			m_triangles[i]->set_fill_color(col); 
		}
	}
private:
	vector<RightAngledTriag*> m_triangles;
};

struct Regular_hexagon2: Shape
{
	Regular_hexagon2(Point center, int side);
	void draw_lines() const;
	int side(){return distance(point(0),point(1));}
	int center_x(){return m_center.x;}
	int center_y(){return m_center.y;}
private:
	Point m_center;
};

void tile_window(Regular_hexagon2* hex, int xSize, vector<Regular_hexagon2*>& hexagon, char dir = 'x');

vector<Point*> get_points();

struct Regular_Polygon: Polygon
{
	Regular_Polygon(Point center, int distance, int numSides);
	void create_triangle();
	void create_square();
private:
	Point m_center;
	int m_dist;
	int m_sides;
};

Vector_ref<Rectangle> create_color_palette(const Point p);

// ====== ch14 ===============

class Smiley: public Circle
{
public:
	Smiley(Point p, int r);
	Smiley(Point p, int r, char c);
	void draw_lines() const;
private:
	Ellipse* m_leftEye;
	Ellipse* m_rightEye;
	Arc* m_smile;
};

class Smiley2: public Circle
{
public:
	Smiley2(Point p, int r);
	void draw_lines() const;
private:
	Ellipse m_leftEye;
	Ellipse m_rightEye;
	Arc m_smile;
};

class Frowny: public Smiley
{
public:
	Frowny(Point p, int r):Smiley(p , r, 'f'){};
};

class Striped_Rectangle: public Rectangle
{
public:
  Striped_Rectangle(Point p, int w, int h);
	void draw_lines()const;
private:	
	Lines m_lines;
};

class Striped_Circle: public Circle
{
public:
  Striped_Circle(Point p, int r);
	void draw_lines()const;
private:	
	Vector_ref<Line> m_lines;
};


class Group: public Shape
{
public:
	void add_shape(Shape& s){m_shapes.push_back(s);}
	void draw() const;
	void move(int dx, int dy);
	void set_fill_color(Color color);	
	void set_color(Color color);	
	void color_checkerBoard(int xNum, int yNum);
	Point topLeft()const;
private:
	Vector_ref<Shape> m_shapes;
};

void create_checker_board(Group &g, Point tl, int xNum, int yNum, int xSize, 
													int ySize );

void add_first_piece(Group& g, int xSize, int ySize);

class BinaryTree: public Shape
{
public:
	BinaryTree(Point p, int level);
	void add_left_dot (Point p, int level);
	void add_right_dot (Point p, int level);
	void draw_lines()const;
private:
	Point m_root;
	int m_level;
	Vector_ref<Circle> m_dots;
	Vector_ref<Arrow> m_arrows;
	//Lines m_lines;
};

class BinaryTree2: public Shape
{
public:
	BinaryTree2(Point p, int level);
	void add_left_dot (Point p, int level);
	void add_right_dot (Point p, int level);
	virtual void draw_nodes();
	virtual void draw_connectors();
	void draw_lines()const;
protected:
	Vector_ref<Shape> m_shape;
	Vector_ref<Arrow> m_connectors;
	vector<Point> m_points;
	vector<PointPair> m_pointPairs;
private:
	Point m_root;
	int m_level;
};

class SquareTree: public BinaryTree2
{
public:
	SquareTree(Point p, int level):BinaryTree2(p,level){};
	void draw_nodes();
	void draw_connectors();
};

class Iterator
{
public:
	virtual double* next()=0;
	void print();
};

class Vector_Iterator: public Iterator
{
public:
	Vector_Iterator(int size):m_size(size),m_index(0){
		if (size==0)
			error ("Vector_Iteration", "enter at least 1 member");
		for (int i=0; i< size; i++)
			m_vec.push_back(i*i);
	}
	double* next(){
		if (m_index > m_size-1)
			return NULL;
		double* tmp = &m_vec[m_index];
		m_index++;
		return tmp;
	}
private:
	int m_index;
	int m_size;
	vector<double> m_vec;
};

class List_Iterator: public Iterator
{
public:
	List_Iterator(int size):m_size(size),m_counter(0){
		if (size==0)
			error ("List Iterator", "enter at least 1 member");
		for (int i=0; i< size; i++)
			m_list.push_back(i*i);
		m_iter = m_list.begin();
	}

	double* next(){
		if (m_counter == m_size)
			return NULL;
		double* tmp= new double;
		*tmp = *m_iter;
		m_iter++;
		m_counter++;
		return tmp;
	}
private:
	list<double>::iterator m_iter;
	int m_size;
	int m_counter;
	list<double> m_list;
};

void print_iterator(Iterator& iter);

class Controller
{
public:
	Controller(int level):m_level(level){}
	virtual bool on(){
		if (m_level !=0)
			return true;
	}
	virtual bool off(){return !on();}
	virtual void set_level(int level){m_level=level;}
	virtual void show(){
		if (on())
			cout << "It's on!" << endl; 
		else
			cout << "It's off!" << endl;
		cout << "current level: " << m_level << endl;
	}
protected:
	int m_level;
};


class Color_Controller: public Controller
{
public:
	Color_Controller(int color):Controller(color),m_init(color){}
	bool on(){
		if (m_level == m_init)
			return 1;
		return 0;
	}
private:
	int m_init;
};

//============= ch15 ===================

class FunctionLean: public Shape
{
public:
	FunctionLean(Fct* fun, double min, double max, Point orig, int numPoints=100, 
						int xScale=20, int yScale=20):m_fun(fun), m_min(min), m_max(max), m_orig(orig), 
						m_dataPoints(numPoints),m_xScale(xScale), m_yScale(yScale){}
	void set_function(Fct* fun){m_fun=fun;}
	void set_min_range(int min){m_min=min;}
	void set_max_range(int max){m_max=max;}
	void set_origin(Point point){m_orig=point;}
	void set_data_points(int num){m_dataPoints=num;}
	void set_xScale(int xScale){m_xScale=xScale;}
	void set_yScale(int yScale){m_yScale=yScale;}
	void create_function(); // must call this function, otherwise you won't have anything drawn !!
private:
	Fct* m_fun;
	double m_min;
	double m_max;
	Point m_orig;
	int m_dataPoints;
	int m_xScale;
	int m_yScale;
};

} //namespace Graph_lib
//#endif
