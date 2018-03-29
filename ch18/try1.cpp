#include "../ch17/std_lib_facilities.h"

struct X{
	int val;
	void out(const string&s, int nv){
		cerr << this << "->" << s << ": " << val << "(" << nv << ")" << endl;
	}

	X(){
		val = 0;
		out("X()--default constructor", val);
	}

	X(int v){
		val = v;
		out("X(int) --regular constructor", val);
	}

	X(const X& x){
		val = x.val;
		out ("X& x --copy constructor", val);
	}

	X& operator=(const X& a){
		cout << "beginning of copy assignement" << endl;
		val = a.val;
		out("operator== copy assignment", val);
		cout << "done with copy assignement" << endl;
		return *this;
	}

	~X(){
		out("~X() -- destructor", 0);
	}
};

X copy (X a){
	cout << "in copy function" << endl;
	return a;
}

X copy2 (X a){
	cout << "beginning of copy2" << endl;
	X aa=a; 
	cout << "end of copy2" << endl;
	return aa;
}

X& ref_to(X& a){
	cout << "in ref_to function" << endl;
	return a;
}

X* make(int i){
	cout << "beginning make" << endl;
	X a(i); 
	cout << "end make" << endl;
	return new X(a);
}


struct XX {X a; X b;};

int main()
{
try{
/*
	X loc(4);
	X loc2 = loc;


	cout << "assign loc = X(5)" << endl;
	loc = X(5);
	cout << "done" << endl;


	cout << "copy" << endl;
	loc2 = copy(loc);
	cout << "done" << endl;


	cout << "copy2" << endl;
	loc2 = copy2(loc);
	cout << "done" << endl;

	X loc3(6);
	X& r = ref_to(loc);
*/

/*
  cout << "make stuff " << endl;
	X* elem = make(10);
	cout << "end make" << endl;
	delete elem;
	
	cout << "deleting make(20)" << endl;
	delete make(20);
*/

/*
	cout << "vector" << endl; 
	vector<X> v(4);
*/
/*
	cout << "XX" << endl;
	XX loc4;
	cout << "done" << endl;
*/
/*
	cout << "x on the heap " << endl;
	X* p = new X(9);
	cout << "deleting it now " << endl;
	delete p;
*/

	cout << "x[] on the heap " << endl;
	X* p = new X[10];	
	cout << "now delete" << endl;
	delete []p;


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
