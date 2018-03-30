#include "../ch17/std_lib_facilities.h"

class Vec
{
public:
	Vec(){m_elem = NULL, m_size=0;}
	Vec(int num);
	Vec(const Vec& aVec);
	~Vec(){
		if (m_elem)
			delete []m_elem;
	}
	int get(int ind);
	int get_const(int ind)const;
	void set(int ind, int num);
	int size()const{return m_size;}
	int* elem()const{return m_elem;}
	void print();
	Vec& operator=(const Vec& vec);
	int& operator[](int n){return m_elem[n];}
	int operator[](int n)const {return m_elem[n];}
private:
	int* m_elem;
	int m_size;
};

Vec::Vec(int num)
	:m_size(num)
{
	int* ints = new int[num];	
	m_elem = ints;
}

Vec::Vec(const Vec& aVec){
	m_size = aVec.size();
	m_elem = new int[m_size];
	for (int i=0; i< m_size; i++){
		set(i,aVec.get_const(i));
	}
}

Vec& Vec::operator=(const Vec& vec){
	int* tmp = m_elem;
	m_elem = vec.elem();
	m_size = vec.size();
	for (int i =0; i<vec.size(); i++)
		set(i,vec.get_const(i));
	delete []tmp;
	return *this;
}

int	Vec::get(int ind){
	if (ind > m_size -1 )
		error ("get: ", "unacceptable index");
	return m_elem[ind];
}

int	Vec::get_const(int ind)const{
	if (ind > m_size -1 )
		error ("get: ", "unacceptable index");
	return m_elem[ind];
}

void Vec::set(int ind, int num){
	if (ind > m_size -1 )
		error ("set: ", "unacceptable index");
	m_elem[ind]=num;
}

void Vec::print(){
	for (int i=0; i<m_size; i++)
		cout << get(i) << " ";
	cout << endl;
}

int main()
{
try{

	Vec vec(10);
	for (int i = 0; i< 10; i++)
		vec.set(i,i*i+1);

	cout << "vector" << endl;
	vec.print();
	
	cout << "7th elememnt: " << vec[6] << endl;
	vec[6]=10;
	
	cout << "vector after modification" << endl;
	vec.print();

/*
	Vec vec(10);
	for (int i = 0; i< 10; i++)
		vec.set(i,i*i+1);

	cout << "vector" << endl;
	vec.print();
	
	cout << "vector2 -- copy constructor" << endl;
	Vec vec2 = vec;
	vec2.print();

	Vec vec3(20);
	for (int i=0; i< 20; i++)
		vec3.set(i,i-10);
	cout << "vector3- orig" << endl;
	vec3.print();	

	vec3 = vec2;
	cout << "vector3- copy assignment" << endl;
	vec3.print();	
*/
	return 0;
}//try

catch(exception &e){
	cerr << "exception happened: " << e.what() << endl;
	return 1;
}
catch(...){
	cerr << "unknown exception happened" << endl;
	return 2;
}

}//main
