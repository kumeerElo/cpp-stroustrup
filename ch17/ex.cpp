#include "std_lib_facilities.h"

void size_of_types()
{
	char c = 'A';
	int i = 10;
	double d = 10.0;
	bool b = true;

	cout << "size of char: " << sizeof(c) << endl;
	cout << "size of int: " << sizeof(i) << endl;
	cout << "size of double: " << sizeof(d) << endl;
	cout << "size of bool: " << sizeof(b) << endl;
}

int get_size(const char* s)
{
	int size = 0;
	while (*s !='\0'){
		size++;
		s++;
	}
	return size;
}

char* to_lower(const char* s){
	int len = get_size(s);
	char* newS = new char[len];

	while (*s !='\0'){
		*newS = *s;
		if (!islower(*newS))
			*newS = tolower(*newS);
		s++;
		newS++;
	}

	newS = newS-len; //move back the pointer;
	return newS;
}

bool findx (const char* s, const char* x)
{
	int sSize = get_size(s);
	int xSize = get_size(x);

	if (xSize > sSize ) return 0;
	bool isCharSame = 0;

	for (int i=0; i<sSize; i++){
		if (s[i]==x[0]){
			isCharSame = 1;
			for (int j=1; j< xSize; j++){
				if (i+j > sSize) return 0;
				if (x[j]!=s[i+j])
					isCharSame = 0;
			}
		}
		if (isCharSame) return 1;
	}
	return 0;
}

void allocate_memory()
{

	int counter = 0;
	int largeNum = pow(2,20);
	while(1){
		double *d = new double[largeNum];
		counter++;
		cout << "counter: " << counter << endl;
		cout << "allocated memory: " << counter*8 << "mb" << endl;
	}
}

char* read_char()
{
	char c;
	int initSize = 5;
	int count = 0;
	
	char *storage = new char[initSize+1]; // last 1 for '\0'

	while (cin){
		c = cin.get();
		if (c == '!'){
			cout << "reading is done\n"; 
			break;
		}
		if (count < initSize)
			storage[count] = c;
		else{
				initSize *=2;
				storage = static_cast<char*>(realloc(storage,initSize+1));
				storage[count] = c;
		}
		count++;
	}
	storage[count] = '\0';
	return storage;
}

string read_char_string()
{
	string str;
	char c;
	int count=0;

	while (cin){
		c = cin.get();
		if (!cin || c == '!'){
			cout << "reading is done\n";
			break;
		}
		str += c;
	}
	return str;
}

void free_store_memory_alloc()
{
	int* ints = new int[10];

	for (int i=0; i< 10; i++)
		cout << "address for " << i << " is " << dec << ints+i << endl;
}
 
int main(){
try{

//ex9
	free_store_memory_alloc();

	/*ex 7 - a good program for reallocation
	char* storage = read_char();
	cout << "we read\n" << storage << endl;
	delete[] storage;
	*/

	/* ex8 - read chars using string 

	string storage = read_char_string();
	cout << "we read\n" << storage << endl;
  */

	/* ex2 
	size_of_types();
	*/
	
	/* ex3/4 - for ex4 - don't do the toLower part otherwise it's identical implementation.

	const char* name = "Hello, World!";
	cout << "before: " << name << endl;
	char* lowerName = to_lower(name);
	cout << "after: " << lowerName << endl;
	delete[]lowerName;
	*/

/* ex5
	string source; 
	string search;

	cout << "enter the source string" << endl;

	while (getline(cin, source)){
		cout << "enter the search string" << endl;
		getline(cin, search);
		const char* s = source.c_str(); 
		const char* x = search.c_str(); 
		bool isFound = findx(s, x);
		cout << "isFound: " << isFound << endl;	
		cout << "enter the source string" << endl;
	}
*/

	/* ex 6
	allocate_memory();
	*/

}//try

catch(exception& e){
	cerr << "exception occured for " << e.what() << endl;
	return 1;
}
catch(...){
	cerr << "unknown exception occured!" <<endl;
	return 2;
}
}//main
