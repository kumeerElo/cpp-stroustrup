#include "../ch17/std_lib_facilities.h"

int fac(int n){
	if (n ==0)
		return 1;
	return n*fac(n-1);
}

/* array implementation 

int ga[]={1,2,4,8,16,32,64,128,256,512};
void print(const int arr[],int size){
	for (int i=0; i<size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void f(const int arg[]){
	int size=10; 
	int la[size];
	
	for (int i=0; i<size; i++)
		la[i]=ga[i];

	cout << "la contains" << endl;
	print(la,size);

	int* p = new int[size];
	
	for (int i=0; i<size; i++)
		p[i]=arg[i];

	cout << "p contains" << endl;
	print(p,size);
	
	delete[]p;
}
*/

// vector implementation 
vector<int> gv; // a global vector

void print(const vector<int>& v){
	for (int i=0; i<v.size();i++)
		cout << v[i] << " ";
	cout << endl;
}

void f(const vector<int>& arg){
	vector<int>lv(arg.size());
	for(int i=0;i<lv.size();i++)
		lv[i]=gv[i];

	cout << "lv contains" << endl;
	print(lv);

	vector<int>lv2(arg.size());

	for(int i=0;i<lv2.size();i++)
		lv2[i]=arg[i];

	cout << "lv22 contains" << endl;
	print(lv2);
}

int main()
{
try{

// array implementation
//initialize the global vector

	for(int i=0; i<10; i++)
		gv.push_back(pow(2,i));

	f(gv);

	vector<int>vv;
	for (int i=0; i<10;i++)
		vv.push_back(fac(i));		

	f(vv);

/* array testing
	//f(ga);	

	int aa[10];

	for (int i=0; i<10;i++)
		aa[i]=fac(i);		

	f(aa);
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
