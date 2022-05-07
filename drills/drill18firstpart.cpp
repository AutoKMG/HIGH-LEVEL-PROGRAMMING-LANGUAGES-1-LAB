#include <iostream>
using namespace  std;
int ga[10] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
void copy_elements(int ai[], int n)
{
    int la[10] = { };
    for (int i = 0; i < n; ++i) la[i] = ai[i];

    cout << "Local copy\n";
    for (const auto& a : la)
        cout << a << ' ';
    cout << '\n';

    int* p = new int[n];
    for (int i = 0; i < n; ++i) p[i] = ai[i];

    cout << "Pointer to free store\n";
    for (int i = 0; i < n; ++i)
        cout << p[i] << ' ';
    cout << '\n';

    delete[] p;
}

int fact(int n) {
    int res = 1;
    for (int i = 2; i <= n; i++) res = res * i;
    return res;
}
int main()
try {
    // code
    copy_elements(ga, 10);

    int aa[10] = {};
    for (int i = 0; i < 10; ++i)
        aa[i] = fact(i + 1);

    cout << "Printing the factorial array\n";
    copy_elements(aa, 10);
}
catch(std::exception& e) {
    cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch(...) {
    cerr << "Unknown exception\n";
    return 2;
}
