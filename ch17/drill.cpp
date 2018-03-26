#include "std_lib_facilities.h"

void print_array(ostream&os, vector<int>& vec)
{
	for (int i=0; i<10; i++)
		os << vec[i] << endl;
}

void print_array(ostream&os, int* ints, int n)
{
	for (int i=0; i<n; i++)
		os << ints[i] << endl;
}

void print_array(ostream&os, int* ints)
{
	for (int i=0; i<10; i++)
		os << ints[i] << endl;
}

int main(){
try{
	int i = 7;
	int* p1 = &i;
	//cout << "p1 pointer: " << p1 << endl;
	//cout << "p1 pointer contains: " << *p1 << endl;

	int* ints = new int[10];
	for (int i=0; i<10; i++)
		ints[i]=1+i*2;

	int* p2 = ints;
	//cout << "pointer p2 " << p2 << endl;
	//print_array(cout, p2, 10);


	int* p3 = p2;
	p1 = p2;
	//cout << "p1: " << p1 << endl;

	//cout << "and it contains" << endl;
	//print_array(cout, p1, 10);

	//delete p1;
	//delete []p2;
	//delete p3;

	int* p5 = ints;

	cout << "p5 contains\n";
	print_array(cout, p5, 10);

	int * ints2 = new int[10];
	for (int i=0; i<10; i++)
		ints2[i]=1+i*i;

	int* p4 = ints2;
	cout << "p4 contains\n";
	print_array(cout, p4, 10);

	for (int i = 0; i<10; i++)
		p5[i]=p4[i];
	
	cout << "after copying - p5 contains\n";
	print_array(cout, p5, 10);


/*
	int* ints = new int[10];
	for (int i=0; i<10; i++)
		ints[i]=i*i;

	cout << "print first 10" << endl;
	print_array(cout, ints);

	delete[]ints;
	//cout << "second pass" << endl; 
	//print_array(cout, ints);

	int* arr2 = new int[10];
	for (int i=0; i<10; i++)
		ints[i]=100+i;
	
	cout << "print arr2" << endl;
	print_array(cout, arr2, 10);

	delete[]arr2;

	vector<int>vec(10);
	for (int i=0; i<10; i++)
		vec[i]=100+i;

	cout << "printing vec" << endl;	
	print_array(cout, vec);
*/

	return 0;
}//try

catch (exception& e){
	cerr << "exception thrown: " << e.what() << endl;
	return 1;
}
catch (...){
	cerr << "unknown exception thrown: " << endl;
	return 2;
}


}
