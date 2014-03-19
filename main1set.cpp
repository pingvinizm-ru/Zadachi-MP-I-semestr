#include <iostream>
#include "set.h"
using namespace std;

int main()
{
	set a, b;
	char c;
    cout << "add symbols to A.\n"  ;

	for (int i = 0; i < 6; ++i)
	{
		cin >> a;
	}
	//a.print_symbols();
    cout << a;
    cout << "|a| = " << a.get_cardinal_number() << endl;

    cout << "\nadd symbols to B.\n"  ;
	for (int i = 0; i < 6; ++i)
	{
		cin >> b;
	}
    cout << b;

    cout << "a + b:"<<(a + b);
    cout << "a * b:" << (a * b);
    cout << "|a*b| = " << (a * b).get_cardinal_number() << endl;

    cout << "\ndel symbols from A.\n"  ;
    for (int i = 0; i < 3; ++i)
	{
		cin >> c;
		a.del_symbol(c);
	}
	cout << a;
	
	cout << "	press any key" << endl;
    cin >> c;
	return 0;
}