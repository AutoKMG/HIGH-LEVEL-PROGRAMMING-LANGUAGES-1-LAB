#include <iostream>
#include <vector>

using namespace std;

vector<int> gv {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

void copy_elements(vector<int> vec)
{
    vector<int> lv(10);
    lv = vec;
    for (auto& a : lv)
        cout << a << '\t';
    cout << '\n';

    vector<int> lv2 = vec;
    for (auto& a : lv2)
        cout << a << '\t';
    cout << '\n';
}

int fact(int n) {
    int res = 1;
    for (int i = 2; i <= n; i++) res = res * i;
    return res;
}

int main()
try {
    copy_elements(gv);
    vector<int> vv(10);
    for (int i = 0; i < vv.size(); ++i)
        vv[i] = fact(i + 1);
    copy_elements(vv);
}
catch(exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch(...) {
    cerr << "Unknown exception\n";
    return 2;
}
