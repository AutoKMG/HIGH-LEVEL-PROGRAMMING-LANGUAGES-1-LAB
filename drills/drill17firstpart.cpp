#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

ostream &print_array(ostream &os, int *arr, int n) {
    for (int i = 0; i < n; ++i) os << arr[i] << '\n';
    return os;
}

ostream &print_vector(ostream &os, vector<int> &v) {
    for (int i = 0; i < v.size(); ++i) os << v[i] << '\n';
    return os;
}

int main()
try {
    // Drill - free-store allocation

    int *arr = new int[20];

    int x = 100;
    for (int i = 0; i < 20; ++i) {
        arr[i] = x++;
    }

    print_array(cout, arr, 20);
    delete[] arr;

    vector<int> v(10);

    int y = 100;
    for (int i = 0; i < v.size(); ++i) {
        v[i] = y++;
    }

    print_vector(cout, v);
}
catch (exception &e) {
    cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Unknown exception\n";
    return 2;
}
