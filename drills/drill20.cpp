#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <list>
#include <array>
using namespace std;

template<typename C>
void displaying_elements(const C &c, const string &s = "") {
 cout << s << '\t';
    for (auto &a: c)
      cout << a << ' ';
    cout << '\n';
}

template<typename C>
void increase_elements(C &c, int n) {
    for (auto &a: c) a += n;
}

template<typename Iter1, typename Iter2>

Iter2 copying_elements(Iter1 f1, Iter1 e1, Iter2 f2) {
    for (Iter1 p = f1; p != e1; ++p)
        *f2++ = *p;
    return f2;
}

int main()
try {
    const int size = 10;

    int arr[size];
    for (int i = 0; i < size; ++i) arr[i] = i;
    displaying_elements(arr, "built-in []: ");

    array<int, size> ai{};
    copy(arr, arr + size, ai.begin());
    displaying_elements(ai, "array: ");

    vector<int> vi(size);
    copy(arr, arr + size, vi.begin());
    displaying_elements(vi, "vector: ");

    list<int> li(size);
    copy(arr, arr + size, li.begin());
    displaying_elements(li, "list: ");

    cout << '\n';

    array<int, size> ai2 = ai;
    vector<int> vi2 = vi;
    list<int> li2 = li;
    displaying_elements(ai2, "array copy: ");
    displaying_elements(vi2, "vector copy: ");
    displaying_elements(li2, "list copy: ");

    cout << '\n';

    increase_elements(ai2, 2);
    increase_elements(vi2, 3);
    increase_elements(li2, 5);
    displaying_elements(ai2, "the increased array: ");
    displaying_elements(vi2, "the increased vector: ");
    displaying_elements(li2, "the increased list: ");

    cout << '\n';

    // copying elements using copying_elements to copy array into vector and list into array
    copying_elements(ai2.begin(), ai2.end(), vi2.begin());
    copying_elements(li2.begin(), li2.end(), ai2.begin());
    displaying_elements(ai2, "the copied array: ");
    displaying_elements(vi2, "the copied vector: ");
    displaying_elements(li2, "the copied list: ");

    // this is code for finding the targeted elements
    vector<int>::iterator vit;
    vit = find(vi2.begin(), vi2.end(), 3);
    if (vit != vi2.end())
        cout << "3 was found at: " << distance(vi2.begin(), vit) << '\n';
    else
        cout << "3 was not found..\n";

    list<int>::iterator lit;
    lit = find(li2.begin(), li2.end(), 27);
    if (lit != li2.end())
        cout << "27 found at: " << distance(li2.begin(), lit) << '\n';
    else
        cout << "27 was not found..\n";
}
catch (exception &e) {
    cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Unknown exception\n";
    return 2;
}
