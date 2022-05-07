#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
struct S {
    public: S(T item = 0) : val{item} {}
    S &operator=(const T &);
    T &get();

private:
    T val;
};

template<typename T>
T &S<T>::get() {
    return val;
}

template<typename T>
S<T> &S<T>::operator=(const T &s) {
    val = s;
    return *this;
}

template<typename T>
ostream &operator<<(ostream &os, vector<T> &v) {
    os << "( ";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << (i < v.size() - 1 ? "- " : " ");
    }
    os << ")\n";

    return os;
}

template<typename T>
istream &operator>>(istream &is, vector<T> &v) {
    char ch = 0;
    is >> ch;
    if (ch != '(') {
        is.unget();
        return is;
    }
    for (T val; is >> val;) {
        v.push_back(val);
        is >> ch;
        if (ch != '-') break;
    }

    return is;
}

template<typename T>
void read_val(T &v) {
    cin >> v;
}

int main() {
    S<int> si{37};
    S<char> sc{'c'};
    S<double> sd{8.5};
    S<string> s{"khaled"};
    S<vector<int>> sv{vector<int>{1, 1, 2, 3, 5, 8}};

    cout << "S<int> : " << si.get() << '\n'
         << "S<char> : " << sc.get() << '\n'
         << "S<double> : " << sd.get() << '\n'
         << "S<string> : " << s.get() << '\n'
         << "S<vector<int>> : " << sv.get() << '\n';

    sd = 3.14159;
    cout << "S<double> : " << sd.get() << '\n';

    cout << "Reads:\n";

    cout << "Vector<int>: (format: ( first value - second value - third value )) ";
    vector<int> v;
    read_val(v);
    S<vector<int>> svi2{v};

    cout << "S<vector<int>> read: " << svi2.get() << '\n';
}
