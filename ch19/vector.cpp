#include "../ch17/std_lib_facilities.h"

class Vector_mks{
public:
	Vector_mks();
	Vector_mks(int size);
	Vector_mks(const Vector_mks& ref);
	void push_back(int n);
	int size() const{return m_size;}
	void print();
	int space()const{return m_space;}
	void reserve(int n);
	void resize(int n);
	Vector_mks& operator=(const Vector_mks& arg);
	int& operator[](int n) {return m_elem[n];}
	int& operator[](int n) const {return m_elem[n];}
private:
	int* m_elem;
	int m_size;
	int m_space;
};

Vector_mks::Vector_mks()
	:m_size(0),m_space(0)
{
	m_elem = NULL;	
}

Vector_mks::Vector_mks(int size)
	:m_size(size),m_space(size)
{
	int* p = new int[m_size];
	m_elem = p;
	for (int i=0; i<m_size;i++)
		m_elem[i]=0;
}

Vector_mks::Vector_mks(const Vector_mks& ref)
{
	int* p = new int[ref.size()];

	for (int i=0; i<ref.size(); i++)
		p[i]=ref[i];

	m_elem = p;
	m_size = ref.size();
	m_space = ref.space();

}

Vector_mks& Vector_mks::operator=(const Vector_mks& arg)
{
	int* p = new int[arg.m_size];
	for (int i=0; i< arg.size(); i++)
		p[i]=arg[i];

	delete []m_elem;
	m_elem = p;
	m_space = arg.space();
	m_size = arg.size();

	return *this;
}


void Vector_mks::resize(int newSize)
{
	reserve(newSize);
	for (int i=m_size; i<newSize; i++)
		m_elem[i]=0;	

	m_size =newSize;
}

void Vector_mks::reserve(int n){
	
	if (n < m_space) return;

	int* p = new int[n];
	for (int i=0; i<m_size; i++)
		p[i] = m_elem[i];

	delete []m_elem;
	m_elem = p;
	m_space=n;
}

void Vector_mks::push_back(int n)
{
	const int fixedSpace = 10;

	if (m_size==0)
		reserve(fixedSpace);
	else if (m_size == m_space)
		reserve(2*m_space);

	m_elem[m_size]= n;
	m_size++;
	
/* manoj's initial implementation, very basic but correct :)
	if (m_elem ==NULL){
		m_elem = new int(n);
		m_size = 1;
	}else{
		int* new_elem = new int[m_size+1];
		for (int i=0; i<m_size; i++)
			new_elem[i]=m_elem[i];
		new_elem[m_size]=n; //add the new element

		delete[]m_elem;
		m_elem = new_elem;
		m_size++;
		m_space++;
	}
*/
}

void Vector_mks::print()
{
	for (int i=0; i<m_size; i++)
		cout << m_elem[i] << " ";
	cout << endl;
}

int main()
{
try{

	Vector_mks v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(50);
	
	Vector_mks v2 = v;
	cout << "v2: " << endl;
	v2.print();

	Vector_mks v3(v);
	cout << "v3: " << endl;
	v3.print();
/*
	cout << "original " << endl;
	v.print();	
	cout << "resize to 20 " << endl;
	v.resize(20);
	v.print();

	cout << "resize to 2 " << endl;
	v.resize(2);
	v.print();

	cout << "resize to 5 " << endl;
	v.resize(5);
	v.print();
	
	cout << "resize to 0 " << endl;
	v.resize(0);
	v.print();

	cout << "resize to 10 " << endl;
	v.resize(10);
	v.print();

	cout << "resize to -17 " << endl;
	v.resize(-17);
	v.print();

	cout << "resize to 100 " << endl;
	v.resize(100);
	v.print();
*/

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
