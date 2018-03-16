#include "fltk.h" 
#include "Simple_window.h"
#include "Point.h"
#include "std_lib_facilities.h"
#include <vector>
#include <time.h>
#include <cmath>

using namespace::Graph_lib;
using Graph_lib::Font;

/*
double one(double x){return 1;}
double slope(double x){return x/2;}
double square(double x){return x*x;}
double sloping_cos(double x){return cos(x)+slope(x);}

struct Person
{
	string m_name;
	int m_age;
};

istream& operator>>(istream& is , Person& person)
{
	string name;
	int age;
	cout << "enter person's name" << endl;
	is >>name;
	cout << "enter person's age" << endl;
	is >>age;
	person.m_name = name;
	person.m_age = age;
	return is;
}

ostream& operator<<(ostream& os , Person& person)
{
	return os << person.m_name  << " , " << person.m_age;
}

const char fixChars[]{';',':', '"','[', ']', '*', '&', '^', '%', '$', '#', '@', '!'};
vector<char> punct(fixChars, fixChars+sizeof(fixChars)/sizeof(fixChars[0]));

class Person_Class
{
public:
	Person_Class():m_name(""), m_age(0){}
	Person_Class(string name, int age):m_name(name), m_age(age)
	{
		if (m_age < 0 || m_age > 150)
			error ("Person_Class constructor"," unreasonable age");
		
		for (int i=0; i<m_name.size();i++){
			char letter = m_name[i];
			for (int j=0; j<punct.size(); j++){
				if (letter == punct[j])
					error ("Person_Class constructor"," punctuation letter in name");
			}
		}
	}

	string name()const{return m_name;}
	int age()const{return m_age;}
	void set_name(string name){m_name = name;}
	void set_age(int age){m_age= age;}
private:
	string m_name;
	int m_age;
};

istream& operator>>(istream& is, Person_Class& person)
{
	cout << "in Person_Class >>" << endl;
	string name;
	int age;
	cout << "enter person's name" << endl;
	is >>name;
	cout << "enter person's age" << endl;
	is >>age;
	Person_Class person2(name,age);
	person = person2;
	//person.set_name(name);
	//person.set_age(age);
	return is;
}

ostream& operator<<(ostream& os , Person_Class& person)
{
	cout << "in Person_Class << " << endl;
	return os << person.name()<< " , " << person.age();
}
*/

int main()
{
try
{
//drill - class definition

/*person based on class person
	
	Person_Class person;
	vector<Person_Class> persons;

	while(cin>>person){
		if (person.name() == "na")
			break;
		persons.push_back(person);	
	}

	for (int i=0; i< persons.size(); i++)
		cout << persons[i].name() << "\t" << persons[i].age() << endl;

*/

/*person based on struct person

	Person person1, person2;
	cin >> person1 >> person2;	
	cout << "person's info" << endl;
	cout << person1 << endl << person2 << endl;
*/



/*drill - function graphing

	int xWin = 600;
	int yWin = 600;
	Simple_window win (Point(400,100),xWin,yWin,"Function Graphs");
	Point origin(xWin/2,yWin/2);
	int length = 400;
	int ticSpacing = 20;
	int numNotch = length/ticSpacing;
	Axis xAxis(Axis::x, origin, length, numNotch, "1 == 20 pixels");
	Axis yAxis(Axis::y, origin, length, numNotch, "1 == 20 pixels");
	xAxis.set_color(Color::red);
	yAxis.set_color(Color::red);
	win.attach(xAxis);
	win.attach(yAxis);

	int negXrange = -10;
	int posXrange = 11;
	int numPoints = 400;
	int xScale = 20;
	int yScale = 20;

	Function f1 (one, negXrange, posXrange, origin, numPoints, xScale, yScale);
	f1.set_color(Color::yellow);
	win.attach(f1);

	Function f2 (slope, negXrange, posXrange, origin, numPoints, xScale, yScale);
	f2.set_color(Color::blue);
	win.attach(f2);

	Text labelF2 (Point(origin.x+negXrange*xScale, origin.y+120),"x/2");
	win.attach(labelF2);
	labelF2.set_color(Color::blue);

	Function f3 (square, negXrange, posXrange, origin, numPoints, xScale, yScale);
	f3.set_color(Color::cyan);
	win.attach(f3);

	Function f4 (cos, negXrange, posXrange, origin, numPoints, xScale, yScale);
	f4.set_color(Color::magenta);
	win.attach(f4);

	Function f5 (sloping_cos, negXrange, posXrange, origin, numPoints, xScale, yScale);
	f5.set_color(Color::green);
	win.attach(f5);
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
