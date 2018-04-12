#include<iostream>
using namespace std;

template <class T>
class Number
{
public:
	Number():m_val(0){};
	Number(T v):m_val(v){};
	T& get(){return m_val;}
	T get()const{return m_val;}
	template <class M>
	friend ostream& operator<<(ostream& os, const Number<M>& num);
	template <class M>
	friend istream& operator>>(istream& is, Number<M>& num);
	Number<T> operator+(const Number<T>& n);
	Number<T> operator*(const Number<T>& n);
	Number<T> operator/(const Number<T>& n);
	Number<T> operator%(const Number<T>& n);
private:
	T m_val;
};	

template <class T>
istream& operator>>(istream& is, Number<T>& num)
{
	T val;
	is >> val;
	num.get() = val;
	return is;
}

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
Number<T> Number<T>::operator*(const Number<T>& n)
{
	T v = m_val*n.get();
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
