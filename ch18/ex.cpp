//#include "../ch17/std_lib_facilities.h"
#include <iostream>
using namespace std;
#include <string.h>

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

int main()
{
try{

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
