#include "../ch17/std_lib_facilities.h"


bool is_palindrome(const char str[], int len)
{
	int begin = 0;
	int end = len-1;

	while (begin < end){
		if (str[begin] != str[end])
			return false;
		begin++;
		end--;
	}
	return true;
}

istream& read_word(istream& is, char* buffer, int max)
{
	is.width(max);
	is >> buffer;
	return is;
}


int len(const char str[]){
	if (str == NULL)
		return 0;

	int count = 0;
	while(str[count]!=0){
		count++;
	}
	return count;
}

int main()
{
try{
	char str[10];
	char c; 
	int ind = 0;

	cout << "enter a word" << endl;
	while (read_word(cin, str,10)){
		cout << "word is " << str << "and it's length is " << len(str) << endl;
		cout << "enter a word" << endl;
	}
	
	while (cin >> c){
		if ( ind==10){
			cout << "we have " << 10 << "chars in the str" << endl;
			break;
		}
		if (!cin || c == '!'){
			cout << "reading done" << endl;
			break;
		}
		str[ind] = c;
		ind++;
	}


	/*cout << "we read " << endl;

	for (int i=0; i<ind; i++){	
		cout << str[i];
	}
	cout << endl;

	cout << "is_palindrome: " << 	is_palindrome(str,ind) << endl;
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
