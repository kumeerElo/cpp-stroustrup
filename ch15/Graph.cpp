#include "Graph.h"
#include<map>
#include <algorithm>
#include <sstream>

namespace Graph_lib {
const double edge = 20;
extern const double pi = 22.0/7;
const double arrowAngle  = 30;

double distance (Point p1, Point p2)
{
	double dx = p1.x - p2.x;
	double dy = p1.y - p2.y;
	return sqrt(dx*dx+dy*dy);
}
int power (int number, int times)
{
	int prod = 1;
	if (times==0)
		return prod;
	for (int i=0; i<times; i++){
		prod *=number;
	}
	return prod;
};

Point rotate(Point p, double theta, Point pivot)
{
/*
	rotation about a pivot consists of two things - 

							p	
						*
				  *
				*
			*
		*
	O		
 
	point o is the pivot, p is the point to be rotated.

	1. set pivot as origin - get coordinate of p wrt o.
	2. rotate p
	3. set the co-ordinate of p wrt o back.
*/	

//step 1
	double x = p.x-pivot.x;
	double y = pivot.y - p.y; // note that positive y-direction in fltk is downward

//step 2

	double rtheta = theta*pi/180; // convert the angle into radian
	double newX = x*cos(rtheta) - y*sin(rtheta);
	double newY = x*sin(rtheta) + y*cos(rtheta);

// step 3
	newX = pivot.x + newX;
	newY = pivot.y - newY;

	return Point(newX, newY);
}

Point north(Rectangle &r)
{
	return Point(r.point(0).x+r.width()/2, r.point(0).y);
}

Point south(Rectangle &r)
{
	return Point(r.point(0).x+r.width()/2, r.point(0).y+r.height());
}

Point east(Rectangle &r)
{
	return Point(r.point(0).x+r.width(), r.point(0).y+r.height()/2);
}

Point west(Rectangle &r)
{
	return Point(r.point(0).x, r.point(0).y+r.height()/2);
}

Point center(Rectangle &r)
{
	return Point(r.point(0).x+r.width()/2, r.point(0).y+r.height()/2);
}

Point northwest(Rectangle &r)
{
	return Point(r.point(0).x, r.point(0).y);
}

Point northeast(Rectangle &r)
{
	return Point(r.point(0).x+r.width(), r.point(0).y);
}

Point southeast(Rectangle &r)
{
	return Point(r.point(0).x+r.width(), r.point(0).y+r.height());
}

Point southwest(Rectangle &r)
{
	return Point(r.point(0).x, r.point(0).y+r.height());
}

void Shape::draw_lines() const
{
  if (color().visibility() && 1<points.size())  // draw sole pixel?
    for (unsigned int i=1; i<points.size(); ++i)
      fl_line(points[i-1].x,points[i-1].y,points[i].x,points[i].y);
}

void Shape::draw() const
{
  Fl_Color oldc = fl_color();
  // there is no good portable way of retrieving the current style
  fl_color(lcolor.as_int());
  fl_line_style(ls.style(),ls.width());
  draw_lines();
  fl_color(oldc); // reset color (to pevious) and style (to default)
  fl_line_style(0);
}

// does two lines (p1,p2) and (p3,p4) intersect?
// if se return the distance of the intersect point as distances from p1
inline pair<double,double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel) 
{
 	double x1 = p1.x;
  double x2 = p2.x;
  double x3 = p3.x;
  double x4 = p4.x;
  double y1 = p1.y;
  double y2 = p2.y;
  double y3 = p3.y;
  double y4 = p4.y;

  double denom = ((y4 - y3)*(x2-x1) - (x4-x3)*(y2-y1));
  if (denom == 0){
    parallel= true;
    return pair<double,double>(0,0);
  }
  parallel = false;
  return pair<double,double>( ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3))/denom,
                ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3))/denom);
}


//intersection between two line segments
//Returns true if the two segments intersect,
//in which case intersection is set to the point of intersection
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection){
   bool parallel;
   pair<double,double> u = line_intersect(p1,p2,p3,p4,parallel);
   if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
   intersection.x = p1.x + u.first*(p2.x - p1.x);
   intersection.y = p1.y + u.first*(p2.y - p1.y);
   return true;
} 

void Polygon::add(Point p)
{
  int np = number_of_points();

  if (1<np) { // check that thenew line isn't parallel to the previous one
    if (p==point(np-1)) error("polygon point equal to previous point");
    bool parallel;
    line_intersect(point(np-1),p,point(np-2),point(np-1),parallel);
    if (parallel)
      error("two polygon points lie in a straight line");
  }

  for (int i = 1; i<np-1; ++i) {  // check that new segment doesn't interset and old point
    Point ignore(0,0);
    if (line_segment_intersect(point(np-1),p,point(i-1),point(i),ignore))
      error("intersect in polygon");
  }
  

  Closed_polyline::add(p);
}


void Polygon::draw_lines() const
{
    if (number_of_points() < 3) error("less than 3 points in a Polygon");
    Closed_polyline::draw_lines();
}

void Open_polyline::draw_lines() const
{
    if (fill_color().visibility()) {
      fl_color(fill_color().as_int());
      fl_begin_complex_polygon();
      for(int i=0; i<number_of_points(); ++i){
        fl_vertex(point(i).x, point(i).y);
      }
      fl_end_complex_polygon();
      fl_color(color().as_int()); // reset color
    }
    
    if (color().visibility())
      Shape::draw_lines();
}


void Closed_polyline::draw_lines() const
{
  Open_polyline::draw_lines();
    
  if (color().visibility()) // draw closing line:
    fl_line(point(number_of_points()-1).x,point(number_of_points()-1).y,point(0).x,point(0).y);
}
void Shape::move(int dx, int dy)
{
  for (unsigned int i = 0; i<points.size(); ++i) {
    points[i].x+=dx;
    points[i].y+=dy;
  }
}

void Lines::draw_lines() const
{
//  if (number_of_points()%2==1) error("odd number of points in set of lines");

  if (color().visibility())
    for (int i=1; i<number_of_points(); i+=2)
      fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);
}

void Text::draw_lines() const
{
  int ofnt = fl_font();
  int osz = fl_size();
  fl_font(fnt.as_int(),fnt_sz);
  fl_draw(lab.c_str(), point(0).x, point(0).y);
  fl_font(ofnt,osz);
}

Function::Function(Fct f, double r1, double r2, Point xy, int count, double xscale, double yscale)
// graph f(x) for x in [r1:r2) using count line segments with (0,0) displayed at xy
// x coordinates are scaled by xscale and y coordinates scaled by yscale
{
  if (r2-r1<=0) error("bad graphing range");
  if (count<=0) error("non-positive graphing count");
  double dist = (r2-r1)/count;
  double r = r1;
  for (int i = 0; i<count; ++i) {
    add(Point(xy.x+int(r*xscale),xy.y-int(f(r)*yscale)));
    r += dist;
  }
}

void FunctionLean::create_function()
{
/*basically the same function as the constructor of the "Function", but this gets called from
	draw_lines() which means, we can modify things upto when we start to draw these lines in the window. 
	Would have been very difficult to get points in the constructor and then modify them later on. 
*/
  if (m_max-m_min<=0) error("bad graphing range");
  if (m_dataPoints<=0) error("non-positive graphing count");
  double dist = (m_max-m_min)/m_dataPoints;
  double x = m_min;
  for (int i = 0; i<m_dataPoints; ++i) {
    add(Point(m_orig.x+int(x*m_xScale),m_orig.y-int(m_fun(x)*m_yScale)));
    x += dist;
  }
}

/*void FunctionLean::draw_lines() const
{
	create_function();
	Shape::draw_lines();
}
*/

void Rectangle::draw_lines() const
{

  if (fill_color().visibility()) {  // fill
    fl_color(fill_color().as_int());
    fl_rectf(point(0).x,point(0).y,w,h);
    fl_color(color().as_int()); // reset color
  }

  if (color().visibility()) { // edge on top of fill
    fl_color(color().as_int());
    fl_rect(point(0).x,point(0).y,w,h);
  }
}


Axis::Axis(Orientation d, Point xy, int length, int n, string lab)
  :label(Point(0,0),lab)
{
  if (length<0) error("bad axis length");
  switch (d){
  case Axis::x:
    { Shape::add(xy); // axis line
      Shape::add(Point(xy.x+length,xy.y));  // axis line
      if (1<n) {
        int dist = length/n;
        int x = xy.x+dist;
        for (int i = 0; i<n; ++i) {
          notches.add(Point(x,xy.y),Point(x,xy.y-5));
        x += dist;
      }
    }
    // label under the line
    label.move(xy.x+length/3,xy.y+20);
    break;
  }
  case Axis::y:
    { Shape::add(xy); // a y-axis goes up
      Shape::add(Point(xy.x,xy.y-length));
      if (1<n) {
      int dist = length/n;
      int y = xy.y-dist;
      for (int i = 0; i<n; ++i) {
        notches.add(Point(xy.x,y),Point(xy.x+5,y));
        y -= dist;
      }
    }
    // label at top
    label.move(xy.x-10,xy.y-length-10);
    break;
  }
  case Axis::z:
    error("z axis not implemented");
  }
}

void Axis::draw_lines() const
{
  Shape::draw_lines();  // the line
  notches.draw(); // the notches may have a different color from the line
  label.draw(); // the label may have a different color from the line
}


void Axis::set_color(Color c)
{
  Shape::set_color(c);
  notches.set_color(c);
  label.set_color(c);
}

void Axis::move(int dx, int dy)
{
  Shape::move(dx,dy);
  notches.move(dx,dy);
  label.move(dx,dy);
}

void Circle::draw_lines() const
{
  if (fill_color().visibility()) {  // fill
    fl_color(fill_color().as_int());
    fl_pie(point(0).x,point(0).y,r+r-1,r+r-1,0,360);
    fl_color(color().as_int()); // reset color
  }

  if (color().visibility()) {
    fl_color(color().as_int());
    fl_arc(point(0).x,point(0).y,r+r,r+r,0,360);
  }
}


void Ellipse::draw_lines() const
{
  if (fill_color().visibility()) {  // fill
    fl_color(fill_color().as_int());
    fl_pie(point(0).x,point(0).y,w+w-1,h+h-1,0,360);
    fl_color(color().as_int()); // reset color
  }

  if (color().visibility()) {
    fl_color(color().as_int());
    fl_arc(point(0).x,point(0).y,w+w,h+h,0,360);
  }
}

void draw_mark(Point xy, char c)
{
  static const int dx = 4;
  static const int dy = 4;
  string m(1,c);
  fl_draw(m.c_str(),xy.x-dx,xy.y+dy);
}

void Marked_polyline::draw_lines() const
{
  Open_polyline::draw_lines();
  for (int i=0; i<number_of_points(); ++i) 
    draw_mark(point(i),mark[i%mark.size()]);
}
/*
void Marks::draw_lines() const
{
  for (int i=0; i<number_of_points(); ++i) 
    fl_draw(mark.c_str(),point(i).x-4,point(i).y+4);
}
*/


std::map<string,Suffix::Encoding> suffix_map;

int init_suffix_map()
{
  suffix_map["jpg"] = Suffix::jpg;
  suffix_map["JPG"] = Suffix::jpg;
  suffix_map["jpeg"] = Suffix::jpg;
  suffix_map["JPEG"] = Suffix::jpg;
  suffix_map["gif"] = Suffix::gif;
  suffix_map["GIF"] = Suffix::gif;
  suffix_map["bmp"] = Suffix::bmp;
  suffix_map["BMP"] = Suffix::bmp;
  return 0;
}

Suffix::Encoding get_encoding(const string& s)
    // try to deduce type from file name using a lookup table
{
  static int x = init_suffix_map();

  string::const_iterator p = find(s.begin(),s.end(),'.');
  if (p==s.end()) return Suffix::none;  // no suffix

  string suf(p+1,s.end());
  return suffix_map[suf];
}

/* mks
bool can_open(const string& s)
            // check if a file named s exists and can be opened for reading
{
  ifstream ff(s.c_str());
  return ff;
}
*/

// somewhat overelaborate constructor
// because errors related to image files can be such a pain to debug
Image::Image(Point xy, string s, Suffix::Encoding e)
  :w(0), h(0), fn(xy,"")
{
  add(xy);

  ifstream ff(s.c_str());
  if (!ff) {
    fn.set_label("cannot open \""+s+'\"');
    p = new Bad_image(30,20); // the "error image"
    return;
  }

  if (e == Suffix::none) e = get_encoding(s);
  
  switch(e) {
  case Suffix::jpg:
    p = new Fl_JPEG_Image(s.c_str());
    break;
  case Suffix::gif:
    p = new Fl_GIF_Image(s.c_str());
    break;
//  case Suffix::bmp:
//    p = new Fl_BMP_Image(s.c_str());
//    break;
  default:  // Unsupported image encoding
    fn.set_label("unsupported file type \""+s+'\"');
    p = new Bad_image(30,20); // the "error image"
  }
}

void Image::draw_lines() const
{
  if (fn.label()!="") fn.draw_lines();

  if (w&&h)
    p->draw(point(0).x,point(0).y,w,h,cx,cy);
  else
    p->draw(point(0).x,point(0).y);
}

Arc::Arc(Point p, double w, double h, int theta1, int theta2):
			m_w(w), m_h(h), m_theta1(theta1), m_theta2(theta2)
{
	if (m_w < 0 || m_h < 0)
		error ("Arc constructor", "unphysical values for w and h of the arc");

	if (m_theta1 < 0 || m_theta2 < 0)
		error ("Arc constructor", "unphysical values either for theta1 or theta2");

	add(Point{p.x-w, p.y-h});

}

void Arc::draw_lines() const 
{
  if (fill_color().visibility()) {  // fill
    fl_color(fill_color().as_int());
    fl_pie(point(0).x,point(0).y,2*m_w-1,2*m_h-1,m_theta1,m_theta2);
    fl_color(color().as_int()); // reset color
  }
  if (color().visibility()) {
    fl_color(color().as_int());
    fl_arc(point(0).x, point(0).y, 2*m_w, 2*m_h, m_theta1, m_theta2);
  }
}

Line_mks::Line_mks()
{
	//Point p = Point(0,0);
	m_p1 = Point(0,0);
	m_p2 = Point(0,0);
}

double Line_mks::length()const{
	double dx = m_p1.x-m_p2.x;
	double dy = m_p1.y-m_p2.y; 
	return sqrt(dx*dx+dy*dy);
}

bool Line_mks:: is_parallel_x()const
{
	if (length()>0){
		if (m_p1.y==m_p2.y)
			return true;
		return false;
	}else
		error ("Line_mks::is_parallel_x", "line has zero length");
}

bool Line_mks:: is_parallel_y()const
{
	if (length()>0){
		if (m_p1.x==m_p2.x)
			return true;
		return false;
	}else
		error ("Line_mks::is_parallel_y", "line has zero length");
}

Point Line_mks::left_corner()const
{
	if (is_parallel_x()){
		if (m_p1.x < m_p2.x)
			return m_p1;
		else 
			return m_p2;
	}	else
		error ("Line_mks::leftCorner()", "not supported for line not parallel to x-axis");
}

Point Line_mks::right_corner()const
{
	if (is_parallel_x()){
		if (m_p1.x > m_p2.x)
			return m_p1;
		else 
			return m_p2;
	}	else
		error ("Line_mks::leftCorner()", "not supported for line not parallel to x-axis");
}

Point Line_mks::top_corner()const
{
	if (is_parallel_y()){
		if (m_p1.y < m_p2.y)
			return m_p1;
		else 
			return m_p2;
	}	else
		error ("Line_mks::leftCorner()", "not supported for line not parallel to x-axis");
}

Point Line_mks::bottom_corner()const
{
	if (is_parallel_y()){
		if (m_p1.y > m_p2.y)
			return m_p1;
		else 
			return m_p2;
	}	else
		error ("Line_mks::leftCorner()", "not supported for line not parallel to x-axis");
}

bool Line_mks:: is_left(Line_mks* line) const
{
	if (line->is_parallel_y()){
		if (m_p1.x < line->p1().x)
			return 1;
		return 0;
	}else
		return 0;
}

bool Line_mks:: is_top(Line_mks* line) const
{
	if (line->is_parallel_x()){
		if (m_p1.y < line->p1().y)
			return 1;
		return 0;
	}else
		return 0;
}

double Line_mks::angle(string end)
{
	double dx=0, dy=0;

	if (end == "p1"){
		dx = p1().x - p2().x;
		dy = -(p1().y -p2().y); // see notes below -ive sign
	}else{
		dx = p2().x - p1().x;
		dy = -(p2().y -p1().y); // see notes below for the -ive sign
	}

	double theta = atan(dy/dx)*180/pi;

	// watch for the quadrant in GUI -- 
	// -ive sign was introduced in previous steps to rectify this problem.
/*					
						|
	x<0, y<0	| x>0, y<0
						|
	-----------------------						
						|
	x<0, y>0	| x>0, y>0
						|
*/

	if (dx < 0 && dy >= 0)
		theta+=180; // 2nd quadrant
	if (dx <= 0 && dy < 0){
		if (dx < 0)
  		theta+=180; // 3rd quadrant
		if (dx==0)
			theta+=360; // y axis in 3rd quadrant
	}
	if (dx > 0 && dy < 0)
		theta+=360; // 4th quadrant

	return theta;
}

Box_mks::Box_mks(Point p, int w, int h):Rectangle(p,w,h)
//Box_mks::Box_mks(Point p, int w, int h)
{

/* location of points on the rectangle 

	p1---p5--------------------------p6---p2
	|                                   	|
	p12                                  	p7	
	|                                   	|
	|                                   	|
	|                                   	|
	p11                                  	p8
 	|																			|
	p4---p10-------------------------p9---p3

	p1-p4 - are vertex for the arc
	p5-p12 -are points for straight lines   

*/

	//calculate four corners - 
	Point p1 = p;
	Point p2(p1.x+w, p1.y);
	Point p3(p1.x+w, p1.y+h);
	Point p4(p1.x, p1.y+h);

//add points as top-left corner of a  box which will contain the ellipse. Part of 
// the ellipse will represent the arc and we'll have rounded corners :)

// method 1

//	add(p1); don't add p1 - it's already added in the constructor of rectangle
	add(Point(p2.x-2*edge, p2.y));
	add(Point(p3.x-2*edge, p3.y-2*edge));
	add(Point(p4.x, p4.y-2*edge));
	
/* method 2

	m_topLeft = new Arc(Point(p1.x+edge, p1.y+edge), edge, edge, 180, 90);
	m_topRight = new Arc(Point(p2.x-edge, p2.y+edge), edge, edge, 90, 0);
	m_bottomRight = new Arc(Point(p3.x-edge, p3.y-edge), edge, edge, 360, 270);
	m_bottomLeft = new Arc(Point(p4.x+edge, p4.y-edge), edge, edge, 270, 180);
*/

// calculate points off the corner by a little distance, so an arc can be drawn 
// there
	Point p5(p1.x+edge, p1.y); 
	Point p6(p2.x-edge, p2.y);
	Point p7(p2.x, p2.y+edge);
	Point p8(p3.x, p3.y-edge);
	Point p9(p3.x-edge, p3.y);
	Point p10(p4.x+edge, p4.y);
	Point p11(p4.x, p4.y-edge);
	Point p12(p1.x, p1.y+edge);

	add(p5);
	add(p6);
	add(p7);
	add(p8);
	add(p9);
	add(p10);
	add(p11);
	add(p12);
	
}

void Box_mks::draw_lines() const
{

/* method 2
	m_topLeft->draw_lines();
	m_topRight->draw_lines();
	m_bottomRight->draw_lines();
	m_bottomLeft->draw_lines();
	
*/

	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());

		//rounded corners
   	fl_pie(point(0).x, point(0).y, 2*edge, 2*edge, 180, 90);
    fl_pie(point(1).x, point(1).y, 2*edge, 2*edge, 90, 0);
    fl_pie(point(2).x, point(2).y, 2*edge, 2*edge, 360, 270);
    fl_pie(point(3).x, point(3).y, 2*edge, 2*edge, 270, 180);

		fl_begin_complex_polygon();
		for(int i=4; i<number_of_points(); i++){
		//for(int i=0; i<number_of_points(); i++) method 2
			fl_vertex(point(i).x, point(i).y);
		}
		fl_end_complex_polygon();
		fl_color(color().as_int()); // reset color
	}
    
	if (color().visibility()){
    fl_arc(point(0).x, point(0).y, 2*edge, 2*edge, 180, 90);
    fl_arc(point(1).x, point(1).y, 2*edge, 2*edge, 90, 0);
    fl_arc(point(2).x, point(2).y, 2*edge, 2*edge, 360, 270);
    fl_arc(point(3).x, point(3).y, 2*edge, 2*edge, 270, 180);
		
    for (int i=5; i<number_of_points(); i+=2)
      fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);
	}
}

void Box::get_center(Point& center, double w, double h, string type)
{
	if (type == "tl"){
		Point corner = m_top->left_corner();	
		center.x = corner.x + w;
		center.y = corner.y + h;	
	}
	else if (type == "tr"){
		Point corner = m_top->right_corner();	
		center.x = corner.x - w;
		center.y = corner.y + h;	
	}
	else if (type == "br"){
		Point corner = m_bottom->right_corner();	
		center.x = corner.x - w;
		center.y = corner.y - h;	
	}
	else if (type == "bl"){
		Point corner = m_bottom->left_corner();	
		center.x = corner.x + w;
		center.y = corner.y - h;	
	}
	else 
		error ("Box::get_center", "undefined corner");
}

vector<Line_mks*> Box::get_lines(Point p, int w , int h)
{
	vector<Line_mks*> lines;

	Point topLeft(Point(p.x+w, p.y));
	Point bottomRight(Point(p.x+w, p.y+h));
	Point bottomLeft(Point(p.x, p.y+h));

	Line_mks* top = new Line_mks(p,topLeft);
	Line_mks* right = new Line_mks(topLeft, bottomRight);
	Line_mks* bottom = new Line_mks(bottomRight, bottomLeft);
	Line_mks* left = new Line_mks(bottomLeft, p);

	lines.push_back(top);	
	lines.push_back(right);	
	lines.push_back(bottom);	
	lines.push_back(left);	
	return lines;
}


Box::Box(Point p, int w, int h){
	m_rect = new Rectangle(p,w,h); // to be used for BoxWithText class

	vector<Line_mks*> lines = get_lines(p, w, h);

	if (lines.size() != 4)
		error ("Box constructor", "there should atleast be 4 lines");

	// only accept lines which are parallel to x or y.
	// two of them should be parallel to x and other two to the y-axis.

	short parallelX =0, parallelY=0;	
	for (int i=0; i<lines.size(); i++){
		if (!lines[i]->is_parallel_x() && !lines[i]->is_parallel_y())
			error("box constructor", "line is either not parallel to x or y axis");
		if (lines[i]->is_parallel_x())
			parallelX++;
		else 
			parallelY++;
	}

	if (parallelX !=2 || parallelY != 2)	
			error("box constructor", "doesn't have two lines parallel to either x or y axis");

	for (int i=0; i<lines.size();i++){
		if (lines[i]->is_parallel_x()){
			for (int j=0; j<lines.size(); j++){
				if (j==i) continue;
				if (lines[j]->is_parallel_x()){
						m_top = lines[i];
						m_bottom = lines[j];
						if (!m_top->is_top(m_bottom)){
							m_top = lines[j];
							m_bottom = lines[i];
						}
						break;
					}
			} //j
		}
		else{
			for (int j=0; j<lines.size(); j++){
				if (j==i) continue;
				if (lines[j]->is_parallel_y()){
					m_left= lines[i];
					m_right= lines[j];
					if (!m_left->is_left(m_right)){
						m_left= lines[j];
						m_right= lines[i];
					}
					break;
				}
			} //j	
		}//else
	}//for i

	//Now the actual constructor :)

	// first create the rectangular box - 

	Point topPoint = m_left->top_corner();
	Point bottomPoint = m_left->bottom_corner();

	add(Point(bottomPoint.x, bottomPoint.y-edge));
	add(Point(topPoint.x, topPoint.y+edge));

	Point leftPoint = m_top->left_corner();
	Point rightPoint = m_top->right_corner();

	add(Point(leftPoint.x+edge, leftPoint.y));
	add(Point(rightPoint.x-edge, rightPoint.y));

	topPoint = m_right->top_corner();
	bottomPoint = m_right->bottom_corner();

	add(Point(topPoint.x, topPoint.y+edge));
	add(Point(bottomPoint.x, bottomPoint.y-edge));

	leftPoint = m_bottom->left_corner();
	rightPoint = m_bottom->right_corner();

	add(Point(rightPoint.x-edge, rightPoint.y));
	add(Point(leftPoint.x+edge, leftPoint.y));

// now create arcs

// draw the topleft arc - 
	Point c(Point(0,0));
	get_center(c,	edge, edge, "tl" );
	m_topLeft = new Arc(c, edge, edge, 90,180);

// topright arc- 
	get_center(c, edge, edge, "tr");
	m_topRight = new Arc(c, edge, edge, 0,90);

// bottomRight arc- 
	get_center(c, edge, edge, "br");
	m_bottomRight = new Arc(c, edge, edge, 270,360);

//	bottomleft arc-
	get_center(c, edge, edge, "bl");
	m_bottomLeft = new Arc(c, edge, edge, 180,270);

}

void Box::draw_lines() const
{
	if (fill_color().visibility()) {
   	fl_color(fill_color().as_int());
    fl_begin_complex_polygon();
    for(int i=0; i<number_of_points(); ++i){
      fl_vertex(point(i).x, point(i).y);
    }
    fl_end_complex_polygon();
    fl_color(color().as_int()); // reset color
  }

	short straightSegments = 8;
	if (color().visibility()){
    for (int i=1; i<straightSegments; i+=2)
      fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);
		m_topLeft->draw_lines();
		m_topRight->draw_lines();
		m_bottomRight->draw_lines();
		m_bottomLeft->draw_lines();
	}
}

Point Arrow::rotate(Point p, double theta)
{
	double rtheta = theta*pi/180; // convert the angle into radian
	double newX = p.x*cos(rtheta) - p.y*sin(rtheta);
	double newY = p.x*sin(rtheta) + p.y*cos(rtheta);

	return Point(newX, newY);
}

void Arrow::create_arrow()
{
/*
	Base and tip of the arrow are the two ends of the line- p1 and p2. Wing tips of the arrow
	 will be found the following way - 

	1. Draw the line on x-axis (a-b in the picture below.). Get the tips c and d by adding a small 	 	 length in x and y co-ordinate of the point p2. 

					c	
     a----->b
					d

		a is the origin (point p1), b is the tip (point p2), c and d are the wings of the arrow.	

	2. Rotate c and d back to the angle of the original line.  

	3. After rotating change the origin to the point p1. Note the adjustments
	
	4. BUG - code doesn't work if we want to take p2 as origin and p1 as the head of the arrow.
*/

	double theta = m_line->angle(m_end);
	double len = m_line->length();

	Point ap1 (len-edge, edge); // starting arrow wings near x-axis
	Point ap2 (len-edge, -edge);

	Point rp1 = rotate(ap1, theta);
	Point rp2 = rotate (ap2, theta);

	// change the origin. Notice the y co-ordinate is subtracted. This is because of 
	// convention	difference in FLTK as compared to usual geometry - In FLTK, y is poisitive
  // going downwards!

	Point arrowhead1 (m_line->p1().x+rp1.x, m_line->p1().y-rp1.y);
	Point arrowhead2 (m_line->p1().x+rp2.x, m_line->p1().y-rp2.y);

	Shape::add(m_line->p1());
	Shape::add(m_line->p2());
	Shape::add(arrowhead1);	
	Shape::add(arrowhead2);	
}

Arrow::Arrow(Line_mks* line, string end)
{
	m_end = end;
	m_line = line;
	m_line->set_line_width(40);
	m_line->set_style(Line_style::solid);
	create_arrow();
}

Arrow::Arrow(Point p1, Point p2, string end)
{
	m_end = end;
	m_line = new Line_mks(p1,p2);
	m_line->set_line_width(40);
	create_arrow();
}

void Arrow::draw_lines() const
{
	if (number_of_points() != 4)
		error ("Arrow::draw_lines", "there should be only 4 points to describe an arrow");

  if (color().visibility()){
    fl_line(point(0).x,point(0).y,point(1).x,point(1).y);
		if (m_end == "p2"){
      fl_line(point(1).x,point(1).y,point(2).x,point(2).y);
      fl_line(point(1).x,point(1).y,point(3).x,point(3).y);
		}else{
      fl_line(point(0).x,point(0).y,point(2).x,point(2).y);
      fl_line(point(0).x,point(0).y,point(3).x,point(3).y);
		}
	}
}

BoxWithText::BoxWithText(Box_mks* box, const string label)
 : m_box(box)
{
	m_box->set_fill_color(Color::green);
	Point p = west(*m_box);
	m_text = new Text(Point(p.x+edge, p.y),label); // move the beginning of label a little to the right
	m_text->set_font(Font::courier_bold);
	m_text->set_font_size(16);
}


void BoxWithText::draw_lines() const
{
	m_box->draw_lines();
	m_text->draw_lines();
}

RightAngledTriag::RightAngledTriag(Point p, int w, int h)
{
/* Points in the triangle are named the following way - 

	p1************p2
	*						*
	*					*
	*				*
	*			*
	*		*
	*	*
	p3
	
*/
	m_p1=p;
 	m_p2 = Point(p.x+w, p.y);	
 	m_p3 = Point(p.x, p.y+h);	// y is positive in downward direction in fltk gui

	add(m_p1);
	add(m_p2);
	add(m_p3);
}

RightAngledTriag::RightAngledTriag(Point p1, Point p2, Point p3)
	:m_p1(p1), m_p2(p2), m_p3(p3)
{
	// p1,p2,p3 can be assigned to any vertex of the triangle
	add(m_p1);
	add(m_p2);
	add(m_p3);
}

RightAngledTriag* RightAngledTriag::rotate_p1_p2(double theta)
{
/* rotate p1 as well as p2 about p3 (for point description, see 
constructorpicture)
*/
	Point rp1 = rotate(p1(), theta, p3());
	Point rp2 = rotate(p2(), theta, p3());
	RightAngledTriag* rotatedTriag = new RightAngledTriag(rp1, rp2, p3()); 
	return rotatedTriag;
}

RightAngledTriag* RightAngledTriag::rotate_p2(double theta)
{
// rotate only p2 about p3 (for point description, see constructor picture
	Point rp2 = rotate(p2(), theta, p3());
	RightAngledTriag* rotatedTriag = new RightAngledTriag(p1(), rp2, p3()); 
	return rotatedTriag;
}

void RightAngledTriag::draw_lines()const
{
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_begin_complex_polygon();
		for(int i=0; i<number_of_points(); i++){
			fl_vertex(point(i).x, point(i).y);
		}
		fl_end_complex_polygon();
		fl_color(color().as_int()); // reset color
	}
    
	if (color().visibility()){
    for (int i=1; i<number_of_points(); i++){
      fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);
	  }
    fl_line(point(number_of_points()-1).x,point(number_of_points()-1).y,
						point(0).x,point(0).y);
	}
}

RightAngledTriag2::RightAngledTriag2(Point p, int w, int h)
{
/* Points in the triangle are named the following way - 

	p1************p2
	*						*
	*					*
	*				*
	*			*
	*		*
	*	*
	p3
	
*/
	m_p1=p;
 	m_p2 = Point(p.x+w, p.y);	
 	m_p3 = Point(p.x, p.y+h);	// y is positive in downward direction in fltk gui

	add(m_p1);
	add(m_p2);
	add(m_p3);
}

RightAngledTriag2::RightAngledTriag2(Point p1, Point p2, Point p3 )
:	m_p1(p1), m_p2(p2), m_p3(p3)
{
	add(p1);
	add(p2);
	add(p3);
}

RightAngledTriag2* RightAngledTriag2::rotate_p1_p2(double theta)
{

/* rotate p1 as well as p2 about p3 (for point description, see 
constructorpicture)
*/
	Point rp1 = rotate(p1(), theta, p3());
	Point rp2 = rotate(p2(), theta, p3());
	RightAngledTriag2* rotatedTriag = new RightAngledTriag2(rp1, rp2, p3()); 
	return rotatedTriag;
}

RightAngledTriag2* RightAngledTriag2::rotate_p2(double theta)
{
// rotate only p2 about p3 (for point description, see constructor picture
	Point rp2 = rotate(p2(), theta, p3());
	RightAngledTriag2* rotatedTriag = new RightAngledTriag2(p1(), rp2, p3()); 
	return rotatedTriag;
}

Triangle::Triangle(Point p, int w , int h):
		RightAngledTriag2(p, w, h)
{
		//int x = 2*p1.x-p2.x;
		//int y = 2*p1.y-p2.y;	
		Shape::add(Point(p.x-w, p.y));
}

Regular_hexagon::Regular_hexagon(Point center, int side)
{
	//get p1,p2,p3 for the rightangledtriangle based center and side of the hexagon

	Point p1 = Point(center.x, center.y+0.5*sqrt(3.0)*side);	

	int count = 1;
	int total = 6;

	RightAngledTriag* r = new RightAngledTriag(p1,0.5*side,0.5*sqrt(3.0)*side);
	m_triangles.push_back(r);
	RightAngledTriag* r1;
	RightAngledTriag* r2;

	while (count < total)
	{
		count++;	
		r1 = r->rotate_p2(60);
		m_triangles.push_back(r1);
		r2 = r->rotate_p1_p2(60);
		m_triangles.push_back(r2);
		r = r2;
	}	

	r1 = r->rotate_p2(60);
	m_triangles.push_back(r1);
}

void Regular_hexagon::draw_lines() const
{
	if (m_triangles.size() != 12)
		error ("Regular_hexagon::draw_lines", "there must be 12 triangles");

	for (int i=0; i<m_triangles.size(); i++){
		m_triangles[i]->draw_lines();
	}
}

Regular_hexagon2::Regular_hexagon2(Point center, int side)
	:m_center(center)
{

	Point p1 (center.x+side, center.y);
	Point p2 (center.x+0.5*side, center.y+0.5*sqrt(3.0)*side);
	Point p3 (p2.x-side, p2.y);
	Point p4 (center.x-side, center.y);
	Point p5 (center.x-0.5*side, center.y-0.5*sqrt(3.0)*side);
	Point p6 (p5.x+side, p5.y);
	
	add(p1);
	add(p2);
	add(p3);
	add(p4);
	add(p5);
	add(p6);
}

void Regular_hexagon2::draw_lines()const
{
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_begin_complex_polygon();
		for(int i=0; i<number_of_points(); ++i){
			fl_vertex(point(i).x, point(i).y);
		}
		fl_end_complex_polygon();
		fl_color(color().as_int()); // reset color
	}
    
	if (color().visibility()){
		Shape::draw_lines();
		fl_line(point(number_of_points()-1).x,point(number_of_points()-1).y,
						point(0).x,point(0).y);
	}
}

void tile_window(Regular_hexagon2* hex, int xSize, 
		vector<Regular_hexagon2*>& hexagons, char dir)
{
// hexagon vector can have some hexagons already, find out how many elements are there as this could impact the coloring part of the code.

	int numExisting = hexagons.size();

	// find out how many hexagons can fit in the window
	int a = hex->side(); 
	int space = 2*a+edge; // an edge/2 space between two hexagons
	int totHex = xSize/space;

	int count = 0;
	int x = 0, y=0;

	if (dir == 'x'){
		x = a+edge/2.0 ;
		y = hex->center_y();
	}
	else if (dir == 'y'){
		x = hex->center_x();
		y = a+edge/2.0 ;
	}

	while (count < totHex){
		Point center(x,y);
		Regular_hexagon2* newHex = new Regular_hexagon2(center,a);	
		if (dir == 'x')
			x = x+2*a+edge;
		else if (dir == 'y')
			y = y+2*a+edge;
		hexagons.push_back(newHex);
		count++;
	}

	for (int i=numExisting; i<hexagons.size(); i++){
		hexagons[i]->set_fill_color(hex->fill_color());
		hexagons[i]->set_color(hex->color());
		hexagons[i]->set_style(hex->style());
	}
}

vector<Point*> get_points()
{
	vector<Point*> points;
	Point* p1 = new Point(0,0);
	Point* p2 = new Point(10,0);
	Point* p3 = new Point(0,40);

	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	return points;
}

void Regular_Polygon::create_triangle()
{
	Point p1(m_center.x, m_center.y-m_dist);
	Point p2 (m_center.x+0.5*sqrt(3.0)*m_dist, m_center.y+0.5*m_dist);
	Point p3 (m_center.x-0.5*sqrt(3.0)*m_dist, m_center.y+0.5*m_dist);
	add(p1);
	add(p2);
	add(p3);
}

void Regular_Polygon::create_square()
{
	Point p1(m_center.x+m_dist/sqrt(2.0), m_center.y-m_dist/sqrt(2.0));	
	Point p2(m_center.x-m_dist/sqrt(2.0), m_center.y-m_dist/sqrt(2.0));	
	Point p3(m_center.x-m_dist/sqrt(2.0), m_center.y+m_dist/sqrt(2.0));	
	Point p4(m_center.x+m_dist/sqrt(2.0), m_center.y+m_dist/sqrt(2.0));	
	add(p1);
	add(p2);
	add(p3);
	add(p4);
}

Regular_Polygon::Regular_Polygon(Point center, int distance, int numSides)
	: m_center(center), m_dist(distance), m_sides(numSides)
{
	if (m_sides == 3)
		create_triangle();
	else if (m_sides == 4)
		create_square();
	else
		error ("Regular_polygon: " , "not supported for polygons with more than 4 sides");
}

Vector_ref<Rectangle> create_color_palette(const Point p)
{
	Vector_ref<Rectangle> rect;
	int side = 20;//keep the rectangles 20*20 pixels.
	for (int i=0; i<16; i++){
		for (int j=0; j<16; j++){
			rect.push_back(new Rectangle(Point(p.x+i*side,p.y+j*side),side,side));	
			rect[rect.size()-1].set_fill_color(16*i+j);
			rect[rect.size()-1].set_color(Color::invisible);
		}
	}
	return rect;
}

Octogon::Octogon(Point p, int a)
{
	// calculate p1, p2 and 3. side of octogon is a.
	// keeping the same name conventions p1,p2,p3 as of the triangle. 
/*
						p2
			 *		*
		*				*
	p1				*
		*				*
		 *			*
			*			*
				*		*			
					* *
						p3

p1p2 is half the side of the octogon (a/2)
angle p3p1p2 is 67.5 (135/2);

*/
	double theta = 67.5;		
	double rtheta = theta*pi/180; // convert the angle into radian
	int p2p3 = 0.5*a/cos(rtheta);

	Point p3 = p; // center
	Point p2 = Point(p.x,p.y - p2p3); // fltk y axis convention

// now add p1
	int dx = 0.5*a*sin(rtheta);
	int dy = 0.5*a*cos(rtheta);

	Point p1 = Point(p2.x-dx, p2.y+dy); // fltk y axis convention

	RightAngledTriag2* triag = new RightAngledTriag2(p1,p2,p3);
	m_triangles.push_back(triag);
	RightAngledTriag2 *triag2, *triag3; 

	for (int i=0; i<8; i++){
		triag2 = triag->rotate_p2(45.0);//
		m_triangles.push_back(triag2);
		triag3 = triag->rotate_p1_p2(45.0);//
		m_triangles.push_back(triag3);
		triag = triag3;
	}

// set different color for each rightangled triangle
	
	give_diff_color(); // this will be used to color the octogno
}

void Octogon::give_diff_color()
{
	int col = 1;
	for (int i = 0; i < m_triangles.size(); i++){
		m_triangles[i].set_fill_color(col);
		col++;
	}
}

void Octogon::draw_lines() const
{
	for (int i=0; i<m_triangles.size(); i++){
		m_triangles[i].draw_lines();
	}
}

void Octogon::set_fill_color(Color col)
{
	for (int i=0; i<m_triangles.size(); i++)
		m_triangles[i].set_fill_color(col);
}

//======== ch14 =============

Smiley::Smiley(Point p, int r)
	:Circle(p,r)
{
	Point c = center();
	Point leftEye(c.x-r*0.3, c.y-r*0.4);
	Point rightEye(c.x+r*0.3, c.y-r*0.4);
	m_leftEye = new Ellipse(leftEye,30,40);
	m_rightEye = new Ellipse(rightEye,30,40);
	Point smileLoc(c.x,c.y+0.2*r);
	m_smile = new Arc(smileLoc, 80, 50, 210, 330);

	Circle::set_fill_color(Color::yellow);
	m_leftEye->set_fill_color(Color::black);
	m_rightEye->set_fill_color(Color::black);
	m_smile->set_color(Color::black);
	m_smile->set_line_width(5); // doesn't work
}

Smiley::Smiley(Point p, int r, char f) // for frowny face
	:Circle(p,r)
{
	Point c = center();
	Point leftEye(c.x-r*0.3, c.y-r*0.4);
	Point rightEye(c.x+r*0.3, c.y-r*0.4);
	m_leftEye = new Ellipse(leftEye,30,40);
	m_rightEye = new Ellipse(rightEye,30,40);
	Point smileLoc(c.x,c.y+0.8*r);
	m_smile = new Arc(smileLoc, 80, 50, 150, 30); // frowny 

	Circle::set_fill_color(Color::yellow);
	m_leftEye->set_fill_color(Color::black);
	m_rightEye->set_fill_color(Color::black);
	m_smile->set_color(Color::black);
	m_smile->set_line_width(5);// this doesn't work
}

void Smiley::draw_lines()const
{
	Circle::draw_lines();
	m_leftEye->draw();
	m_rightEye->draw();
	m_smile->draw();
}

Striped_Rectangle::Striped_Rectangle(Point p, int w, int h)
	:Rectangle(p,w,h)
{
	int ySize = p.y+h;
	int spacing = 40; // spacing between lines

	int dy = 0;

	while (p.y+dy <= ySize){
		m_lines.add(Point(p.x,p.y+dy), Point(p.x+w,p.y+dy));
		m_lines.set_color(Color::red); // gives stripes red color
		m_lines.set_line_width(1); // 1 pixel width
		dy+=spacing;
	}
}

void Striped_Rectangle::draw_lines()const
{
	Rectangle::draw_lines();
	m_lines.draw();
}

//solving the smiley problem without pointer member
/*
Lessons - 

1. If you create an object in the braces, for example - 
		Ellipse m_rightEye (rightEye,30,40);
	this object gets out of scope when we reach draw_lines function
	
2. If you rather try to do it this way - 

	m_leftEye = Ellipse(leftEye,30,40);

	it doesn't work either because the Shape class doesn't have copy-constructor defined

3. Only way to get non-pointer class members work is to initialized them in the ":" right before the braces. 

*/

Smiley2::Smiley2(Point p, int r)
	:Circle(p,r),m_leftEye(Point(center().x-r*0.3,center().y-r*0.4),30,40),
	 m_rightEye(Point(center().x+r*0.3,center().y-r*0.4),30,40),
	 m_smile(Point(center().x,center().y+r*0.2),80,50,210,330)
{
	/*
	Point c = center();
	Point leftEye(c.x-r*0.3, c.y-r*0.4);
	Point rightEye(c.x+r*0.3, c.y-r*0.4);
	m_leftEye = Ellipse(leftEye,30,40);
	Ellipse m_rightEye (rightEye,30,40);
	Point smileLoc(c.x,c.y+0.2*r);
	Arc m_smile(smileLoc, 80, 50, 210, 330);
	*/
	Circle::set_fill_color(Color::yellow);
	m_leftEye.set_fill_color(Color::black);
	m_rightEye.set_fill_color(Color::black);
	m_smile.set_color(Color::black);
	m_smile.set_line_width(5); // doesn't work
}

void Smiley2::draw_lines()const
{
	Circle::draw_lines();
	m_leftEye.draw_lines();
	m_rightEye.draw_lines();
	m_smile.draw();
}

Striped_Circle::Striped_Circle(Point p, int r)
:Circle(p, r)
{
	Point c = center();
	int y = 0; // increment in y direction
	int x = 0;
	while(y<r){
		x = sqrt(r*r-y*y);
		double theta = atan(1.0*y/x);
		//upper half
		m_lines.push_back(new Line(Point(c.x+r*cos(theta),c.y-r*sin(theta)),
														 	 Point(c.x-r*cos(theta),c.y-r*sin(theta))));
		//lower half
		if (x > 0 && y >0){
			m_lines.push_back(new Line(Point(c.x+r*cos(theta),c.y+r*sin(theta)),
														 	 Point(c.x-r*cos(theta),c.y+r*sin(theta))));
		}
		y +=0.2*r;
	}

	Circle::set_fill_color(Color::yellow);
	for (int i=0; i< m_lines.size(); i++){
		m_lines[i].set_line_width(3);
		m_lines[i].set_color(Color::red);
	}
}

void Striped_Circle::draw_lines()const
{
	Circle::draw_lines();
	for (int i=0; i < m_lines.size(); i++){
		m_lines[i].draw();
	}
}

void Group::draw() const
{
	for (int i=0; i< m_shapes.size(); i++)
		m_shapes[i].draw();
}

void Group::set_fill_color(Color color)
{
	for (int i=0; i< m_shapes.size(); i++)
		m_shapes[i].set_fill_color(color);
}

void Group::set_color(Color color)
{
	for (int i=0; i< m_shapes.size(); i++)
		m_shapes[i].set_color(color);
}

void Group::move(int dx, int dy)
{
	for (int i=0; i< m_shapes.size(); i++)
		m_shapes[i].move(dx,dy);
}

Point Group::topLeft()const{
	if (m_shapes.size() < 1 )
		error ("Group::topLeft", "empty group, operation not allowed");
	return m_shapes[0].point(0);
}


void Group::color_checkerBoard(int xNum, int yNum)
{
	for (int i = 0; i < xNum; i++){
		for (int j = 0; j < yNum; j++){
			if ((i+j)%2==0)
				m_shapes[i*xNum+j].set_fill_color(Color::red);
			else
				m_shapes[i*xNum+j].set_fill_color(Color::black);
		}
	}
}

void create_checker_board(Group& checkerBoard, Point tl, int xNum, int yNum, int xSize, int ySize) 
{
	int xSide = xSize/xNum;
	int ySide = ySize/yNum;

	for (int i = 0; i < xNum; i++){
		for (int j=0; j< yNum; j++){
			Rectangle* r = new Rectangle (Point(tl.x+i*xSide, tl.y+j*ySide)
																,xSide, ySide);
			checkerBoard.add_shape(*r);
		}
	}
	checkerBoard.color_checkerBoard(xNum, yNum);
}

void add_first_piece(Group& g, int xSize, int ySize)
{
	Point tl = g.topLeft();
	int dx = xSize/8;
	int dy = ySize/8;

	int r = dy/2; // consider square checkerboard
	Circle *c = new Circle(Point(tl.x+dx/2, tl.y+dy/2),r);
	c->set_fill_color(Color::yellow);
	g.add_shape(*c);
}

void BinaryTree::add_right_dot(Point p, int level)
{
	int r = 30;
	int dx = 200-50*level;
	int dy = 150;

	Point newP(p.x+dx, p.y+dy);
	Circle* c = new Circle(newP,r);
	c->set_fill_color(Color::black);
	m_dots.push_back(c);

	Arrow* a = new Arrow(p,newP);
	m_arrows.push_back(a);
	//m_lines.add(p,newP);

	if (level == 0)	
		return;
	add_left_dot(newP,level-1);
	add_right_dot(newP,level-1);
}

void BinaryTree::add_left_dot(Point p, int level)
{
	int r = 30;
	int dx = 200-50*level;
	int dy = 150;

	Point newP(p.x-dx, p.y+dy);
	Circle* c = new Circle(newP,r);
	c->set_fill_color(Color::black);
	m_dots.push_back(c);

	Arrow* a = new Arrow(p,newP);
	m_arrows.push_back(a);
	//m_lines.add(p,newP);

	if (level ==0)
		return;
	add_left_dot(newP,level-1);
	add_right_dot(newP,level-1);
}

BinaryTree::BinaryTree(Point p, int level)
:m_root(p),m_level(level)
{
	int r = 30;
	Circle* c = new Circle(p,r);
	c->set_fill_color(Color::black);
	m_dots.push_back(c);	
	if (level == 0)
		return;
	add_left_dot(p,level-1);
	add_right_dot(p,level-1);
	//m_lines.set_color(Color::blue);
}

void BinaryTree::draw_lines()const
{
	for (int i=0; i<m_arrows.size(); i++)
		m_arrows[i].draw_lines();
	//m_lines.draw();
	for (int i=0; i<m_dots.size(); i++)
		m_dots[i].draw_lines();

}

// second implementation - this is going to be used in problem #12

void BinaryTree2::add_right_dot(Point p, int level)
{
	int dx = 200-50*level;
	int dy = 150;

	Point newP(p.x+dx, p.y+dy);
	m_points.push_back(newP);
	m_pointPairs.push_back(PointPair(p,newP));

	if (level == 0)	
		return;

	add_left_dot(newP,level-1);
	add_right_dot(newP,level-1);
}

void BinaryTree2::add_left_dot(Point p, int level)
{
	int dx = 200-50*level;
	int dy = 150;

	Point newP(p.x-dx, p.y+dy);
	m_points.push_back(newP);
	m_pointPairs.push_back(PointPair(p,newP));

	if (level ==0)
		return;

	add_left_dot(newP,level-1);
	add_right_dot(newP,level-1);
}

BinaryTree2::BinaryTree2(Point p, int level)
:m_root(p),m_level(level)
{
	m_points.push_back(p);	
	if (level == 0)
		return;
	add_left_dot(p,level-1);
	add_right_dot(p,level-1);
	//draw_nodes();
	//draw_connectors();
}

void BinaryTree2::draw_nodes()
{
	int r = 30;
	for (int i=0; i< m_points.size(); i++){
		Circle* c = new Circle(m_points[i],r);
		c->set_fill_color(Color::blue);
		m_shape.push_back(c);
	}
}

void BinaryTree2::draw_connectors()
{
	for (int i=0; i<m_pointPairs.size(); i++){
		Arrow* a = new Arrow(m_pointPairs[i].get_p1(), m_pointPairs[i].get_p2());
		a->set_color(Color::yellow);
		m_connectors.push_back(a);
	}
}

void BinaryTree2::draw_lines()const
{
	for (int i=0; i< m_connectors.size(); i++){
		m_connectors[i].draw();
	}

	for (int i=0; i< m_shape.size(); i++){
		m_shape[i].draw();
	}
}

void SquareTree::draw_nodes()
{
	int l = 50;
	for (int i=0; i< m_points.size(); i++){
		Rectangle * r = new Rectangle (m_points[i],l,l);
		r->set_fill_color(Color::red);
		m_shape.push_back(r);
	}
}

void SquareTree::draw_connectors()
{
	int l = 50; //side of the square
	for (int i=0; i<m_pointPairs.size(); i++){
		Point shiftP1(m_pointPairs[i].get_p1().x+l/2,m_pointPairs[i].get_p1().y+l/2);
		Point shiftP2(m_pointPairs[i].get_p2().x+l/2,m_pointPairs[i].get_p2().y+l/2);
		Arrow* a = new Arrow(shiftP1, shiftP2);
		a->set_color(Color::green);
		m_connectors.push_back(a);
	}
}

void print_iterator(Iterator& iter)
{
	while (1){
		double* val = iter.next();
		if (val == NULL) return;
		cout << *val << endl;	
	}
}

void Iterator::print()
{
	while (1){
		double* val = next();
		if (val == NULL) return;
		cout << *val << endl;	
	}
}

Bar_Graph::Bar_Graph(ifstream& ifs, Axis* x, Axis* y, Point orig, int yScale, int barSpacing, int barWidth)
:m_orig(orig), m_xAxis(x), m_yAxis(y)
{
	double xVal, yVal;
	char ch1, ch2, ch3;
	vector<double> xValues;
	vector<double> yValues;
	
	while (ifs >>ch1 >>xVal >> ch2 >> yVal >> ch2){
		if (!ifs.good() && !ifs.eof() )
			error ("Bar_Graph::constructor", "problem reading the datafile");
		xValues.push_back(xVal);
		yValues.push_back(yVal);
	}

	if (xValues.size() ==0)
		error ("Bar_Graph constructor", "enter at least one value");

	int xcoord = m_orig.x+barSpacing; 
	int ycoord= m_orig.y;

	for (int i=0; i<xValues.size(); i++){
		if (i>0)
			xcoord = xcoord+ barSpacing+barWidth; 
		ycoord = orig.y-yScale*yValues[i];
		if (ycoord < 0)
			error ("Bar_graph constructor", "negative y coord, adjust the scaling for the data values");
		Rectangle* bar = new Rectangle(Point(xcoord,ycoord),barWidth,orig.y-ycoord);
		m_bars.push_back(bar);
	}

	set_bar_labels(xValues, yValues);
}

void Bar_Graph::set_bar_labels(vector<double> &xvals, vector<double> &yvals)
{
	for (int i=0; i<m_bars.size(); i++){
		Point locX(m_bars[i].tl().x,m_bars[i].tl().y+m_bars[i].height()+20);
		Point locY(m_bars[i].tl().x,m_bars[i].tl().y-20);
		ostringstream os1;
		os1 << xvals[i];
		Text* txtX = new Text(locX,os1.str());
		m_bar_labels.push_back(txtX);
		ostringstream os2;
		os2 << yvals[i]; 
		Text* txtY = new Text(locY, os2.str());
		m_bar_labels.push_back(txtY);
	}
}


void Bar_Graph::set_bar_labels(vector<string> &labels)
{
	if (labels.size() != m_bars.size())
		error ("Bar_Graph:: set_bar_labels", " not enough labels");	

	for (int i=0; i<m_bars.size(); i++){
		Point locX(m_bars[i].tl().x,m_bars[i].tl().y+m_bars[i].height()+20);
		Point locY(m_bars[i].tl().x,m_bars[i].tl().y-20);
		Text* txtX = new Text(locX,labels[i]);
		m_bar_labels.push_back(txtX);
		ostringstream os;
		os <<  m_bars[i].height();
		Text* txtY = new Text(locY, os.str());
		m_bar_labels.push_back(txtY);
	}
}

void Bar_Graph::move_bars(int dx)
{
	for(int i=0; i<m_bars.size(); i++)
		m_bars[i].move(dx,0);
}

void Bar_Graph::move_y_labels_top(int dx)
{
	for (int i=1; i<m_bar_labels.size(); i+=2)
		m_bar_labels[i].move(dx,0);
}


void Bar_Graph::draw_lines()const
{
	m_xAxis->draw();
	m_yAxis->draw();
	for(int i=0; i< m_bars.size(); i++)
		m_bars[i].draw();

	for(int i=0; i< m_bar_labels.size(); i++)
		m_bar_labels[i].draw();
}

} // Graph
