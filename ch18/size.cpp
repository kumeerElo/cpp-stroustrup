#include "../ch17/std_lib_facilities.h"

struct ss{
	ss(int ii, double dd, char cc):i(ii), d(dd), c(cc){}
	int i;
	double d;
	char c;
};

int main()
{
try{

	const char* str = "manoj";

	const char* str2 = "kumar";
	
	str2 = str;
	cout << str2 << endl;
/*
	int x = 7;
	int *p = &x;
	cout << "size of int " << sizeof(x) << endl;
	cout << "size of int* " << sizeof(p) << endl;

	char c = 'c';
	char* pc = &c;

	cout << "size of char" << sizeof(c) << endl;
	cout << "size of char* " << sizeof(pc) << endl;

	double d = 10.5;
	double* pd = &d;

	cout << "size of double " << sizeof(d) << endl;
	cout << "size of double* " << sizeof(pd) << endl;

	ss s(10,20.0,'d');

	ss* ps = &s;

	cout << "size of struct " << sizeof(s) << endl;
	cout << "size of struct* " << sizeof(ps) << endl;
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
