#include<iostream>
using namespace std;

class Int
{
public:
	Int():m_n(0){}
	Int(int n):m_n(n){}
	int& get(){return m_n;}
	const int& get()const{return m_n;}
	friend ostream& operator<<(ostream& os, const Int& n);
	friend istream& operator>>(istream& is, Int& n);
	//Int& operator=(const Int& a); // funny enough, we don't need copy-assignemnt
	Int operator+(const Int &a); // notice return of an Int as opposed to Int&
private:
	int m_n;	
};

Int Int::operator+(const Int& a)
{
	return m_n+a.get();
}

/*
Int& Int::operator=(const Int &a)
{
	m_n=a.get();
	return *this;
}
*/

istream& operator>>(istream& is, Int& n)
{
	int i;
	is >> i;
	if (is.fail()){
		is.putback(i); // somehow this call doesn't work :( :( 
		cout << "wrong entry, please enter an int again" << endl;
		is >> i;
	}

	n.get()=i;
	return is;
}

ostream& operator<<(ostream& os, const Int& n)
{
	os << n.get();
	return os;
}


int main()
{
	Int m = 100;
	Int n = m;

	cout << "m: " << m << endl;
	cout << "n: " << n << endl;

	Int p = m+n+m+n;
	cout << "p=m+n: " << p << endl;
	
	p = m;
	cout << "p=m: " << p << endl;

	cout << "m: " << m << endl;


	/*Int q = m+10;
	cout << "p: " << p << endl;
	cout << "q: " << q << endl;
	cout << "q+10: " << q+10 << endl;
 	*/
		
/*
	cout << "enter some ints" << endl;
	Int i;

	while (cin >> i){
		cout << "i: " << i << endl;
		cout << "enter another number" << endl;	
	}
*/
}
