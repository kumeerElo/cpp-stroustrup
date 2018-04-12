#include<iostream>
using namespace std;
#include <vector>
#include "number.h"

template<class T> 
void print(const vector<T>& v)
{
	for (int i =0; i< v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
}

template<class T>
vector<T> add(vector<T>& v1, vector<T>& v2)
{
	if (v1.size() !=v2.size()){
		cout << "diff size vectors, adding default elements to the smaller vector " << endl;
	}

	if (v1.size() < v2.size()){
		for (int i = v1.size(); i<v2.size(); i++)
			v1[i]=T();
	}
	if (v2.size() < v1.size()){
		for (int i = v2.size(); i<v1.size(); i++)
			v2[i]=T();
	}

	vector<T>v;
	for (int i=0; i<v1.size(); i++){
		v.push_back(v1[i]+v2[i]);
	}
	return v;
}

template<class T>
vector<T> multiply(vector<T>& v1, vector<T>& v2)
{
	if (v1.size() !=v2.size()){
		cout << "diff size vectors, adding default elements to the smaller vector " << endl;
	}

	if (v1.size() < v2.size()){
		for (int i = v1.size(); i<v2.size(); i++)
			v1[i]=1;
	}
	if (v2.size() < v1.size()){
		for (int i = v2.size(); i<v1.size(); i++)
			v2[i]=1;
	}

	vector<T>v;
	for (int i=0; i<v1.size(); i++){
		v.push_back(v1[i]*v2[i]);
	}
	return v;
}


template<class T>
void test(vector<T>& v1, vector<T>& v2)
{
	T n;
	int tot=0;
	cout << "create your v1 vector" << endl;
	cout << "enter the size of v1" << endl;
	cin >> tot;
	int count = 0;
	while (count < tot){
		cin >> n;
		v1.push_back(n);
		count++;
	}
	cout << "v1: " << endl;
	print(v1);

	cout << "create your v2 vector" << endl;
	cout << "enter the size of v2" << endl;
	cin >> tot;
	count = 0;
	while (count < tot){
		cin >> n;
		v2.push_back(n);
		count++;
	}

	cout << "v2: " << endl;
	print(v2);
	
	//vector<T> v = add(v1, v2);
	vector<T> v = multiply(v1, v2);
	
	cout << "vectors after addition" << endl;
	print(v);
}

int main()
{
 /* check int
	vector<int> v1;
	vector<int> v2;
	create_vectors(v1, v2);	
*/
	//check double

/*
	vector<double> v1;
	vector<double> v2;
	test(v1, v2);	
*/

	vector<Number<double>> v1; // great usaage of Number<double> class :)
	vector<Number<double>> v2;
	test(v1, v2);	
}
