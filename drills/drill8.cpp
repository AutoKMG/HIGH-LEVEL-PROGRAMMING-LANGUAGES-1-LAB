#include "std_lib_facilities.h"

void swap_v(int a, int b) {
    //swapping two integers
    int temp;
    temp = a;
    a = b;
    b = temp;
    cout << "The following line is the result of swap_v\n";
    cout << a << " x||y " << b << endl;
}

void swap_r(int &a, int &b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

//
//void swap_cr(const int &a, const int &b) {
//    int temp;
//    temp = a;
//    a = b;
//    b = temp;
//}


int main() {
    int x = 20;
    int y = 10;
    cout << "The original value of x is " << x << " The original value of y is "<< y << '\n';
    swap_r(x, y);
    cout << "The following line is the result of swap_r\n";
    cout<<x<< " x||y "<<y<<endl;
    swap_v(20, 10);
    const int cx = 7;
    const int cy = 9;
    // can't compile because it's constant value
    // swap_cr(cx, cy);
    double dx = 7.7;
    double dy = 9.9;
    // can't compile because it's double method takes only integer
    // swap_r(dx, dy);
    // swap_r(7.7, 9.9);

    cout<<cx << " cx||cy " << cy<<endl;
}
