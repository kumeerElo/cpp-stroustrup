#include<iostream>
using namespace std;

template <class T>
class Number
{
public:
	Number():T(){};
	Number(T v):m_val(v){};
	T get()const{return m_val;}
	template <class M>
	friend ostream& operator<<(ostream& os, const Number<M>& num);
	Number<T> operator+(const Number<T>& n);
	Number<T> operator/(const Number<T>& n);
	Number<T> operator%(const Number<T>& n);
private:
	T m_val;
};	

template <class T>
ostream& operator<<(ostream& os, const Number<T>& num)
{
	return os << num.get();
}

template <class T>
Number<T> Number<T>::operator%(const Number<T>& n)
{
	T v = m_val%n.get();
	return Number<T>(v);
}

template <class T>
Number<T> Number<T>::operator/(const Number<T>& n)
{
	T v = m_val/n.get();
	return Number<T>(v);
}

template <class T>
Number<T> Number<T>::operator+(const Number<T>& n)
{
	T v = m_val+n.get();
	return Number<T>(v);
}

int main()
{

	Number<int> i(10);
	Number<double> d(2.4);

	cout << "i: " << i << endl;
	cout << "d: " << d << endl;

	Number<int> i2 = i%3;
	cout << "i2: " << i2 << endl;

// % operator for doubles is not defined. so if we uncomment the following lines
// code would not compile :)

	//Number<double> d2 = d%1.1; 
	//cout << "d2: " << d2 << endl;

/*
	Number<double> d2 (1.1);
	Number<double> d3 =  d2/d;
	cout << "d3: " << d3 << endl;

	Number<double> d4 =  d2/2.2;
	cout << "d4: " << d4 << endl;
*/
/*
	Number<int> i1(4);
	Number<int> i2 = i/i1;
	cout << "i2: " << i2 << endl;
	//Number<int> i2 = i/3;
	//cout << "i2: " << i2 << endl;
*/


/*
	Number<int> i2 = 5; // no need to define copy assignment and = operator
	cout << "i2: " << i2 << endl;

	Number<double> d2(12.5); // no need for copy initialization
	cout << "d2: " << d2 << endl;

	Number<double> d3 = d + d2;
	cout << "d3: " << d3 << endl;

	Number<int> i5 = i+100;
	cout << "i5: " << i5 << endl;
*/


}
