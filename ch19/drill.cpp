#include<iostream>
using namespace std;
#include <vector>

void error (const string& s1, const string& s2)
{
	throw s1+s2; 
}

template<class T> struct S
{
	S():val(T()){};
	S(T v):val(v){}
	T& get();
	T get()const;
	void set(T v);
	void operator=(const T& arg);
	template <class M>	
	friend ostream& operator<<(ostream& os, const S<M>& s);
	template<class V>
	friend istream& operator>>(istream& is, S<V>& v);
	void read_val(T& v);
private:
	T val;
};

template<class T> T& S<T>::get(){return val;}
template<class T> T S<T>::get()const{return val;}
template<class T> void S<T>::set(T v){val=v;}
template<class T> void S<T>::operator=(const T& t) {val =t;}

template<class T> void S<T>::read_val(T& t)
{
	cout << "enter a value " << endl;
	cin>>t;
	val =t;
}

template<class T>
istream & operator>> (istream& is, vector<T>& arg) 
{
	cout << "enter numbers follwing {v1 v2 v3} format, note beginning and ending braces"<< endl;
	char cb = '{';
	char ce = '}'; 
	char c;	
	T t;

	is >> c;

	if (c != cb)
		error ("operator>> vector<T>", "needs beginning {");

	while (1){
		is >> t;
		if (is.fail()){
			is.putback(t);
			char c;
			is >> c;
			if (c ==ce){
				cout << "successful reading! " << endl;
				break;
			}else{
				error ("operator>> vector<T>", "uknown end to reading values, so erroring out");
			}
		}
		arg.push_back(t);
	}


/*
	while (is>>t){
 		if (t == ce) break;
		arg.push_back(t);
	}

	if (is.fail()){
		is.putback(t);
		char c;
		is >> c;
		if (c ==ce){
			cout << "successful reading! " << endl;
		}else{
			error ("operator>> vector<T>", "uknown end to reading values, so erroring out");
		}
	}
*/
}

/*
template<class T>
istream& operator>>(istream& is, T& tv)
{
	is>>tv;
	return is;
}
*/

template<class T>
ostream & operator<< (ostream & arg1, const vector<T> & arg2) 
{
    for (int i = 0; i < int(arg2.size()); ++i)
        arg1 << (i > 0 ? " " : "") << arg2[i];
    return arg1;
}

template <class T>
ostream& operator<<(ostream& os, const S<T>& s)
{
	T v = s.get();		
	os << v;
	return os;
}

template<class T>
istream& operator>>(istream& is, S<T>& t)
{
	is >> t.get();
	return is;
}

int main()
{
try{
	S<vector<int>> v2;
	cout << "enter a vector of int " << endl;
	cin >>v2;
	cout << "you entered: " << v2 << endl;

	S<int> i2;
	cout << "enter an int" << endl;
	cin >>i2;
	cout << "you entered: " << i2 << endl;

	S<string> s2;
	cout << "enter a string" << endl;
	cin >>s2;
	cout << "you entered: " << s2 << endl;


/*
	S<int> i(5);
	S<char> c('A');
	S<double> d (1.0);
	S<string> s("manoj");
	vector<int>v(10,20);
	S<vector<int>> vs(v);
	vector<char> cs(20,'B');
	S<vector<char>> vc(cs);

	cout << "==orig-intial ==" << endl;

	cout << i << endl;
	cout << c << endl;
	cout << d << endl;	
	cout << s << endl;
	cout << vs << endl;
	cout << vc << endl;
*/
/* test for read_val

	int t;
	cout << "read an int" << endl;
	i.read_val(t);
	cout << "new value is: " << i << endl;

	string ts;
	cout << "read a string" << endl;
	s.read_val(ts);
	cout << "new value is: " << s << endl;

	
	vector<char> tmp;

	cout << "read an char vector " << endl;
	vc.read_val(tmp);
	cout << "vector: " << vc << endl;


	vector<int> vi;
	cout << "read an int vector " << endl;
	vs.read_val(vi);
	cout << "vector: " << vs << endl;
*/	

/*
	//reassign them using copy operator;

	i = 10;
	c = 't';
	d = 20.0;
	s = "kumar";
	vector<int>v1(5,-1);
	vs = v1;
	vector<char>c1(30,'h');
	vc = c1;

	cout << "after copy assignment" << endl;

	cout << i << endl;
	cout << c << endl;
	cout << d << endl;	
	cout << s << endl;
	cout << vs << endl;
	cout << vc << endl;


	// reassign above by using set --

	i.set(50);
	c.set('z');
	d.set(-2.0);
	s = "srivastae";
	vector<int> v2 (5,2);
	vs.set(v2);	
	vector<char> c2 (10,'p');
	vc.set(c2);	

	cout << "after copy initialization" << endl;

	cout << i << endl;
	cout << c << endl;
	cout << d << endl;	
	cout << s << endl;
	cout << vs << endl;
	cout << vc << endl;
*/
	
	/*cout << i << endl;
	cout << c << endl;
	cout << d << endl;
	cout << s << endl;*/
	//cout << vs << endl;

	/*default
	S<int> i;
	S<char> c;
	S<double> d;
	cout << i << endl;
	cout << c << endl;
	cout << d << endl;
	*/
}
catch(exception& e){
	cerr << "exception occured " << e.what() << endl;
	return 1;
}
catch(...){
	cerr << "unknown exception occured " << endl;
	return 2;
}
}
