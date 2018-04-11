#include "../ch17/std_lib_facilities.h"

template<class T> class S {
    T val;
public:
    S () {}
    S (const T & arg) : val(arg) {}
    T & get ();
    const T & get () const;
    void set (const T & arg);
    S & operator= (const T & arg) {val = arg; return *this;}
};

template<class T> T & S<T>::get () {return val;}
template<class T> const T & S<T>::get () const {return val;}
template<class T> void S<T>::set (const T & arg) {val = arg;}

// These are horrible, but need namespace fiddling to do it better,
// as far as I can see.

ostream & operator<< (ostream & arg1, const vector<int> & arg2) {
    for (int i = 0; i < int(arg2.size()); ++i)
        arg1 << (i > 0 ? " " : "") << arg2[i];
    return arg1;
}

istream & operator>> (istream & arg1, vector<int> & arg2) {
// This reads to EOF - we could equally well just read the number of
// elements in arg2 on entry.
    int n;
    arg2.resize(0);
    while (arg1) {
        arg1 >> n;
        if (arg1) arg2.push_back(n);
    }
    return arg1;
}

template<class T> void read_val (S<T> & arg) {
    T n;
    cin >> n;
    arg = n;
}

int main () {
    S<int> a(123);
    S<char> b('Z');
    S<double> c(4.56);
    S<string> d;
    d = "PDQ";
    S<vector<int> > e(vector<int>(5,789));
    //cout << a.get() << " " << b.get() << " " << c.get() << " " <<
    //   d.get() << " " << e.get() << endl;
   
		cout << e.get() << endl;
/* 
    read_val(a);
    read_val(b);
    read_val(c);
    read_val(d);
    read_val(e);
    cout << a.get() << " " << b.get() << " " << c.get() << " " <<
        d.get() << " " << e.get() << endl;
*/
}
