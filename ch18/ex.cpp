//#include "../ch17/std_lib_facilities.h"
#include <iostream>
using namespace std;
#include <string.h>
#include <sstream>

const int k = 1000;

int length(const char* str){
	int sz=0;	
	while(str[sz]){
		sz++;
	}
	return sz;
}

bool is_lower(char c){
	string chars = "abcdefghijklmnopqrstuvwxyz";

	for (int i=0; i<chars.size(); i++){
		if (c == chars[i])
			return true;
	}
	return false;
}

char to_lower(char c){
	if (is_lower(c))
		return c;
	int offset = 'a'-'A';
	return char(c+offset);
}

char* strdup(const char* str){
	int size = length(str);
	char* p = new char[size];
	for (int i=0; i<size; i++)
		*(p+i)=str[i];
	return p;
}

bool findx (const char* s, const char* x){
	if (length(x) > length(s))
		return false;

	for (int i=0; i<length(s);i++){
		if (*(s+i)==*x){
			bool isFound = 1;
			for (int j=0; j<length(x); j++){
				if (i+j >length(s)-1)
					return false;
				if (*(s+i+j)!=*(x+j)){
					isFound = 0;
					break;
				}
			}
			if (isFound)
				return true;
		}
	}
		return false;
}

int stringcmp(const char* s1, const char* s2){
	const char* tmp = s1;
	if (length(s1) > length(s2)){
		s1 = s2;
		s2 = tmp;
	}

	for (int i=0; i< length(s1); i++){
		if (to_lower(s1[i])>to_lower(s2[i])) return 1;
		if (to_lower(s1[i])<to_lower(s2[i])) return -1;
	}

	if (length(s1)!=length(s2))
		return -1;
	return 0;
}

//string cat_dog(const string& s1, const string& s2, const string& sep)
char* cat_dog(const string& s1, const string& s2, const string& sep)
{
/*
	string s = s1;
	s+=sep;
	s+=s2;
	return s;
*/	

	const char* cs1 = s1.c_str();
	const char* cs2 = s2.c_str();
	const char* csep = sep.c_str();
	int size = length(cs1)+length(cs2)+length(csep)+1; // 1 for 0 terminate c-string.	
	char* p = new char[size]; 

	int i=0;

	for (; i< length(cs1); i++)
		p[i]=cs1[i];	

	int k=0;
	for (; k<length(csep);k++)
		p[i+k]=csep[k];

	int j=0;

	for (; j< length(cs2); j++)
		p[i+k+j]=cs2[j];	

	p[i+j+k] = '\0';

	return p;
}

bool is_palindrome(const char* s){
	char* s2 = new char[length(s)]; //

	for (int i=0; i<length(s);i++)
		s2[i]=s[length(s)-1-i];

	for (int i=0; i<length(s);i++){
		if (s[i]!=s2[i]){
			delete[]s2;
			return false;
		}
	}
	delete[]s2;
	return true;
};

void stack2(){
	int a = 7;
	double b = 10.0;
	char name[1000];
	cout << "stack22 a: " << &a << endl;
	cout << "stack2: b: " << &b << endl;
}

void stack1(){
	int a = 7;
	double b = 10.0;
	cout << "stack1: a: " << &a << endl;
	cout << "stack1: b: " << &b << endl;

	int vec1[10];
	cout << "stack1: vec[0] " << &vec1[0] << endl;
	cout << "stack1: vec[1] " << &vec1[1] << endl;
	cout << "stack1: vec[2] " << &vec1[2] << endl;
	cout << "stack1:  vec[9]" << &vec1[9] << endl;
	cout << "calling  stack2 from stack1" << endl;
	//stack2();
}

void hex_to_double(){
	cout << "from hex to dec" << endl;
	long num;
	while (cin >> hex >> num){
		cout << dec << num << endl;
	}
}

void dyn2(){
	int* num2 = new int[100];
	cout << "num2[0]" << &num2[0] << endl;
	cout << "num2[99]" << &num2[99] << endl;
}

void dyn1(){
	int x = 10;
	double y = 10.0;
	cout << "x: " << &x << endl;
	cout << "y: " << &y << endl;

	int* a = new int(5);
	double* b = new double(10.0); 
	cout << "dyn1 a:"  << a << endl;
	cout << "dyn1 b:"  << b << endl;
  
	int *nums = new int[1000];
	cout << "nums[0]: "  << &nums[0] << endl;
	cout << "nums[1]: "  << &nums[1] << endl;


	double* ds = new double[100];

	cout << "ds[0]: "  << &ds[0] << endl;
	cout << "ds[99]: "  << &ds[99] << endl;


	dyn2();
}

void fun1(){
	int a = 10;
	cout << "fun1: a "  << &a << endl;
}

int main()
{
try{

/*  ex -9 - heap and stack
	A couple of observations - 
1. Address of stack is lower to what the address of variables in the main are (code). 
2. Total memory of stack is allocated in a variable way. If you define more variables, the address of stack is going to be that much lower fromt the main. For example, if you have only two variables, say both ints, in a function, the function's address is going to be about 12 bytes + 20 bytes. The last addition is what I found in many of my experiments, it seems that every new stack is off by about 16-25 bytes, may be to write some other info about the stack.
3. In anothe example, if you have an array of 100 ints, say int[100], the stack is going to be about 424 bytes below that of the main.
4. Within the stack, the address of varibles grows up. Notice, how useful the varibale becomes as you will cross the boundary otherwise. 
5. Heap allocation is far simpler. Heap's address is way below the stack address on my computer, see book, and all heap allocations occupy the space defined by the type, 4 for int, 8 for double, etc, and some extra storage. Extra storage is similar to what was described in stack, about 220-24 bytes.
6. Heap calls from different function go to the same heap address and memory is assigned based on the order of function calls. Variables of a function which is called after anther function will have later heap address compared to the former.
7.  



	long a = 7;
	double b = 10.0;
	cout << "main: a: " << &a << endl;
	cout << "main: b: " << &b << endl;
	//cout << "global: k: " << &k << endl;

	int* n = new int(10);
	cout << "main: n: " << n << endl;
	

	//stack1();
	dyn1();
	
	hex_to_double();
*/

/*ex-8

	string s;
	while (cin>>s){
		cout << "palindrome: " << is_palindrome(s.c_str()) << endl;
	}
*/

/* ex-5,6 == two implementations - one using string and another char*. And to the beauty of
	stroustrup, char* is exercise 7 :) 
 
	string name = cat_dog("manoj", "kumar", ".and.");
	char* name = cat_dog("manoj", "kumar", "and");
	cout << name<< endl;
	delete []name;
*/

/*ex4

	char str[15];
	for (int i=0; i<15; i++){
		str[i]='a'+i;
	}

	char*p = strdup(str);

	cout << p << endl;
*/

/*ex3

	cout << "enter strings - s1 && s2" << endl;
	string s1;
	string s2;

	while (cin >> s1 >> s2){
		int result = stringcmp(s1.c_str(), s2.c_str());
		if (result ==1)
			cout << s1 << " > " << s2 << endl;
		else if (result ==-1)
			cout << s1 << " < " << s2 << endl;
		else 
			cout << s1 << " = " << s2 << endl;
		cout << "enter strings - s1 && s2" << endl;
	}
*/

/*ex2

	cout << "enter the main string followed by the one that you want to search" << endl;
	string mainStr;
	string searchStr;

	while (cin >> mainStr >> searchStr){
		cout << "found: " << findx(mainStr.c_str(), searchStr.c_str())<<endl;
	}
*/	

/* ex1
	string s;
	char* s2;
	while (cin >> s){
		cout << "before strdup, string is: " << s << endl;
		s2 = strdup(s.c_str());
		cout << "after strdup, string is: " << s2 << endl;
		delete []s2;
	}
*/

/* test for length function
	string s;
	while (cin >> s){
		cout << "size of " << s << " is: " << length(s.c_str()) << endl;
	}
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
