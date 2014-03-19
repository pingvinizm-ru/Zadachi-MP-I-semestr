#include <iostream>
#include "list-array.h"

using namespace std;

int main()
{
	list_array<int> a(10), b(200), c(100);
    int t;
	cout << "add to a" << endl;
    for (int i = 0; i < 10; i++)
    {
    	cin >> t;
        a.add_record(t);
        a.print_list();
    }
	cout << "a:" ;
    a.print_list();
	
	cout << "del from a" << endl;
    for (int i = 0; i < 10; i++)
    {
    	cin >> t;
        a.del_record(t);
        a.print_list();
    }
	
	cout << "press any key" << endl;
    cin >> t;
	return 0;
}