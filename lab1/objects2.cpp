#include "std_lib_facilities.h"

int main(){	
	
	int a = 10000;
	char c = a;
	int b = c;
	cout << a << '\n';
	cout << b << '\n';
	string s = "Hello, ";
	string name;
	cin >> name;
	string full_name = s+name;
	cout << full_name << '\n';
	return 0;
}
